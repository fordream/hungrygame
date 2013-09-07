/*
* 2013 08 18
* Joung Daun
* GameScene
*/
#include "stageSelectScene.h"
#include "music.h"
#include "HelloWorldScene.h"
#include "mainScene.h"
#include "gameScene.h"
#include "PauseGameScene.h"
using namespace cocos2d;

enum crashSomething { nothing, CrashWithWall, CrashWithFood, CrashWithItem};
CCScene* gameScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		gameScene *layer = gameScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool gameScene::init()
{

	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		foodSpriteArray = new CCArray; //food sprite array dinamic cast
		foodFollowArray = new CCArray;
		onCheckFoodDisplay = new CCArray;
		tomakeFood = new CCArray;



		CCSize size = CCDirector::sharedDirector()->getWinSize();



		//------------------------- Daun Start -------------------------------//
		/*
		* make background scene
		* Joung Daun
		* http://blog.naver.com/PostView.nhn?blogId=skmzzang7979&logNo=70142661460
		*/
		CCLayer *tileLayer = CCLayer::create();
		this->addChild(tileLayer);

		//		CCTMXTiledMap *tileMap;
		CCTMXObjectGroup *objectgroup;

		// 맵 파일 불러오기

		tileMap = CCTMXTiledMap::create("map/GameMap.tmx");

		//	tileMap->setPosition(size.width * 0.05, size.height * 0.35);
		// -> 위에 줄이 맵 위치 이동시키는거임! 일단은 0,0으로 두는게 좋겠다!
		//	this->addChild(tileMap,1,2);

		// 맵 타일 불러오기

		backgroundLayer = tileMap->layerNamed("wall");

		//---------    eunji for wall    ---------------------

		//metainfo에 준 타일레이어 이름은 Items이지만 벽표시 위한 빨간레이어임.
		// 추후 실제 아이템을 포함 할 수도 있음.
		metainfo = tileMap->layerNamed("Items");
		metainfo->setVisible(false); // 빨간벽을 표시안함.
		//		CCAssert(backgroundLayer != NULL, "backgroundLayer not found");
		tileLayer->addChild(tileMap);

		//--------- end eunji ---------------------------
		
		/*
		* make character
		* Daun..
		*/
		createCharacter();
		//------------------------- Daun End -------------------------------//




		/* pineoc's comments
		links : http://www.raywenderlich.com/40544/cocos2d-x-tile-map-tutorial-part-2
		*/
		CCSize s = tileMap->getContentSize();

		/*
		pineoc's food testing part --------------------------------------------------------------
		*/

		foods = tileMap->objectGroupNamed("foods");
		CCDictionary *food1point = foods->objectNamed("food1");
		CCDictionary *food2point = foods->objectNamed("food2");
		CCDictionary *food3point = foods->objectNamed("food3");
		CCDictionary *food4point = foods->objectNamed("food4");

		//

		int food1X = ((CCString*)food1point->objectForKey("x"))->intValue();
		int food1Y = ((CCString*)food1point->objectForKey("y"))->intValue();
		this->createFood(ccp(food1X,food1Y),"map/p.jpg");

		int food2X = ((CCString*)food2point->objectForKey("x"))->intValue();
		int food2Y = ((CCString*)food2point->objectForKey("y"))->intValue();
		this->createFood(ccp(food2X,food2Y),"map/green_pepper.png");

		int food3X = ((CCString*)food3point->objectForKey("x"))->intValue();
		int food3Y = ((CCString*)food3point->objectForKey("y"))->intValue();
		this->createFood(ccp(food3X,food3Y),"map/bamboo_shoot.png");

		int food4X = ((CCString*)food4point->objectForKey("x"))->intValue();
		int food4Y = ((CCString*)food4point->objectForKey("y"))->intValue();
		this->createFood(ccp(food4X,food4Y),"map/crab_stick.png");

		std::srand(NULL);
		int food5X = tileCoorPosition(ccp(std::rand()%10,std::rand()%20)).x;
		int food5Y = tileCoorPosition(ccp(std::rand()%10,std::rand()%20)).y;
		if(checkDup((CCSprite*)foodSpriteArray->objectAtIndex(3)))
			this->createFood(ccp(food5X,food5Y),"map/Big_welsh_onion.png");

		foodcount = foodSpriteArray->count();

		this->schedule(schedule_selector(gameScene::updateFoodSprte));
		//this->schedule(schedule_selector(gameScene::followCharacter));
		//----------------------------------------------------------------------------------------


		//-------------- obstacle (eunji) --------------------

		CCTMXObjectGroup *obstacle = tileMap->objectGroupNamed("obstacle");
		CCDictionary *obstaclePoint = obstacle->objectNamed("obstaclePoint");

		int obX = ((CCString*)obstaclePoint->objectForKey("x"))->intValue();
		int obY = ((CCString*)obstaclePoint->objectForKey("y"))->intValue();

		obstaclePosition = ccp(obX, obY);
		this->createObstacle();




		//----------------------------------------------------


		//--------------Pause Btn-jiyoon start----------------
		//일시정지 버튼 추가
		CCMenuItemImage *btnPause = CCMenuItemImage::create(
			"img/game/game_btn_pause.png", "img/game/game_btn_pause.png", this, menu_selector(gameScene::doPop));
		CC_BREAK_IF(! btnPause);

		btnPause->setPosition(ccp(size.width*0.5, size.height*0.9));

		PauseMenu = CCMenu::create(btnPause, NULL);
		PauseMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! PauseMenu);

		this->addChild(PauseMenu, 2);

		//snotification 추가
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(gameScene::doNotification),
			"notification", NULL);
		//"notification"이라는 메시지가 오면 해당 함수를 실행한다.
		//-------------jiyoon End-------------------------------


		bRet = true;
	} while (0);

	return bRet;
}

CCPoint gameScene::tileCoorPosition(CCPoint position)
{//general function, for point -> tile point

	int mapSize_h  = tileMap->getMapSize().height;
	int tileSize_h = tileMap->getTileSize().height;
	int tileSize_w = tileMap->getTileSize().width;   

	//    CCLog("%d %d %d", mapSize_h,tileSize_h,tileSize_w);
	int x = position.x /tileSize_w;
	int y = (tileSize_h* mapSize_h -position.y) / tileSize_h;

	return ccp(x,y);
}

void gameScene::createObstacle()
{// 장애물 생성 위함

	CCTexture2D *obTexture = CCTextureCache::sharedTextureCache()->addImage("map/meat.png");

	obstacle = CCSprite::createWithTexture(obTexture,CCRectMake(0, 0, 48, 48)); // 맵에 맞춰 숫자 바꿔야함
	obstacle->setPosition(obstaclePosition);
	this->addChild(obstacle);

}



//------------------------ Daun Start ----------------------------//
/*
* void gameScene::onEnter()
* this function work to use touch.
* 터치를 입력받을 것을 지시하는 함수
* 이게 있어야 터치를 받음
* Daun..
*/
void gameScene::onEnter()
{
	CCLayer::onEnter();

	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

/*
* bool gameScene::ccTouchBegan(CCTouch *, CCEvent *)
* when touch start, this function work
* 화면에 손가락이 닿을때
* Daun..
*/
bool gameScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event)
{
	beforeMoveCharPoint[0] = character->getPosition();
	return true;
}

/*
* void gameScene::ccTouchEnded(CCTouch *, CCEvent *)
* When touch end, this function work
* now character is moved to way w
* 화면에서 손가락이 떼어질때
* 현재에는 캐릭터를 중심으로 화면의 어느 부분이 터치되었느냐에 따라
* 캐릭터가 이동합니다.
* Daun..
*/
void gameScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event)
{
	CCPoint touchLocation = pTouch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);

	CCSprite* checkSpriteFood;//for checkfood

	CCPoint playerPos = character->getPosition();

	int checkCrash = nothing;
	/********************************************************** To EVERYONE *************
	* check character is crash with someting
	* 충돌여부를 판단하는 공간입니다
	* enum crashSomething { nothing, CrashWithWall, CrashWithFood, CrashWithItem};
	* 즉, checkCrash가 0이면 아무것도 안부딫친거, 1이면 벽, 2이면 음식 3이면 아이템이랑 부딫친거임
	*/

	/*
	* 벽과 충돌했는지 확인하는 공간입니다
	* To Eunji
	*/
	
	//이부분은 수정 필요함. 다운코드 수정해서 쓸라그랬는데 잘 안되네..
	/*
	CCPoint diffForWall = ccpSub(touchLocation, playerPos);
	CCPoint newPlayerPos = playerPos;

	if(abs(diffForWall.x) > abs(diffForWall.y))
	{
		if(diffForWall.x > 0)
		{
			newPlayerPos.x += tileMap->getTileSize().width;
		}
		
		else
		{
			newPlayerPos.x -= tileMap->getTileSize().width;
		}

		if(diffForWall.y > 0)
		{
			newPlayerPos.y += tileMap->getTileSize().height;
		}
		
		else
		{
			newPlayerPos.y -= tileMap->getTileSize().height;
		}
	}
	*/

	CCPoint tileCoord = this->tileCoorPosition(touchLocation);

	int tileGidforWall = this->metainfo->tileGIDAt(tileCoord);

	if(tileGidforWall)
	{
		CCDictionary *properties = tileMap->propertiesForGID(tileGidforWall);

		if(properties)
		{
			CCString *wall = (CCString*)properties->objectForKey("Wall");

			if(wall && (wall->compare("YES") == 0))
			{
				checkCrash = CrashWithWall;
			}
		}
	}


	/* End Eunji */



	/* 
	* 음식과 충돌했는지 확인하는 공간입니다
	check collision food and character
	*/
	// code from here
	//if(!checkDup(playerPos))
	//{//using boundingbox to check collision
	/*	for(int i=0;i<foodcount;i++)
	{
	checkSpriteFood = (CCSprite*)foodSpriteArray->objectAtIndex(i);
	CCRect foodbounding = checkSpriteFood->boundingBox();
	CCRect charbounding = character->boundingBox();
	if(foodbounding.intersectsRect(charbounding))
	{
	checkCrash = CrashWithFood;
	break;
	}
	else
	checkCrash = nothing;
	}*/

	//	}
	//updateFood()함수로 대체
	followCharacter(1.0);


	/* End pineoc */




	/*
	* 아이템과 충돌했는지 확인하는 공간입니다
	*/
	// 여기에 코드작성

	/* end blackbell */





	if(checkCrash == nothing)
	{
		// 캐릭터가 충돌하지 않은경우~
		// 마우스 클릭한 방향으로 움직임!
		CCPoint diff = ccpSub(touchLocation, playerPos);

		if (abs(diff.x) > abs(diff.y)) {
			if (diff.x > 0) {
				playerPos.x += tileMap->getTileSize().width;

				// 캐릭터의 방향을 바꾸어준다.
				character->setFlipX(true);
			} else {
				playerPos.x -= tileMap->getTileSize().width;

				// 캐릭터의 방향을 바꾸어준다.
				character->setFlipX(false);
			}
		} else {
			if (diff.y > 0) {
				playerPos.y += tileMap->getTileSize().height;
			} else {
				playerPos.y -= tileMap->getTileSize().height;
			}
		}

		if (playerPos.x <= (tileMap->getMapSize().width * tileMap->getTileSize().width) &&
			playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height) &&
			playerPos.y >= 0 &&
			playerPos.x >= 0 )
		{
			// 캐릭터의 새로운 위치 지정
			character->setPosition( playerPos );
		}

	}
	else if(checkCrash == CrashWithWall)
	{
		// 벽과 충돌한 경우 해야할 일
		character->setPosition(playerPos);
	}
	else if(checkCrash == CrashWithFood)
	{
		// 음식과 충돌한 경우 해야할 일
		delFood(checkSpriteFood);

	}
	else if(checkCrash == CrashWithItem)
	{
		// 아이템과 충돌한 경우 해야할 일
	}
}

void gameScene::createCharacter()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();


	// 타일맵에서 Object라고 지정한 오브젝트 객체들 가져오기
	CCTMXObjectGroup *object = tileMap->objectGroupNamed("object");
	// 속성값 읽어오기 (characterPosition)
	CCDictionary *spawnPoint = object->objectNamed("character");

	int x = ((CCString*)spawnPoint->objectForKey("x"))->intValue();
	int y = ((CCString*)spawnPoint->objectForKey("y"))->intValue();

	CCPoint characterPosition = ccp(x,y);




	// make charcter show in map

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("img/character/character.png");

	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);


	character = CCSprite::createWithTexture(texture, CCRectMake(0,0,35,48));
	character->setAnchorPoint(ccp(0,0));

	// character->setScale(0.05);
	character->setPosition(characterPosition);
	//character->setFlipX(true); // X축 기준으로 반전
	//character->setFlipY(true);	// Y축 기준으로 반전

	CCAnimate *animate = CCAnimate::create(animation);
	CCAction *rep = CCRepeatForever::create(animate);
	character->runAction(rep);

	this->addChild(character,60);
}


// -----------------------Daun End -------------------------------//

//------------------------Pineoc's part---------------------------//
void gameScene::createFood(CCPoint foodpoint,char* foodImageName)
{//collision correct, duplication correct

	CCTexture2D *foodTexture = CCTextureCache::sharedTextureCache()->addImage(foodImageName);
	CCSprite* food = CCSprite::createWithTexture(foodTexture,CCRectMake(0, 0, 48, 48)); // 맵에 맞춰 숫자 바꿔야함
	food->setPosition(foodpoint);
	food->setAnchorPoint(ccp(0,0));
	food->setTag(2);
	foodSpriteArray->addObject(food);
	this->addChild(food);

}

/*
check duplication function
*/
bool gameScene::checkDup(CCSprite* checkfood)
{// if dup, return false
	//it can be useful another object.
	int tileGid = 1;//backgroundLayer->tileGIDAt(location);
	//int foodarrCount = foodSpriteArray->count();
	CCRect checkfoodbounding =  checkfood->boundingBox();
	for(int i=0;i<foodcount;i++)
	{//check the all food object
		CCSprite* check = (CCSprite*)foodSpriteArray->objectAtIndex(i);
		CCRect checkbounding = check->boundingBox();
		if(checkfoodbounding.intersectsRect(checkbounding))
		{
			return false;
		}
	}
	if(tileGid == NULL)
		return true;
	else
		return false;
	//return true;
}
void gameScene::delFood(CCObject* pSender)
{
	CCSprite* del = (CCSprite*)pSender;
	this->removeChild(del);
}

/*
음식 재료를 먹었을때 없어지게 함.
*/
void gameScene::updateFoodSprte(float dt)
{
	CCArray* foodToDelete = new CCArray;
	CCObject* foodobject = NULL;
	CCARRAY_FOREACH(foodSpriteArray,foodobject)
	{
		CCRect characterRect = CCRectMake(character->getPosition().x - (character->getContentSize().width/2),
			character->getPosition().y -(character->getContentSize().height/2),
			character->getContentSize().width,
			character->getContentSize().height);
		CCSprite* foodSprite = dynamic_cast<CCSprite*>(foodobject);
		CCRect foodRect = CCRectMake(foodSprite->getPosition().x - (foodSprite->getContentSize().width/2),
			foodSprite->getPosition().y -(foodSprite->getContentSize().height/2),
			foodSprite->getContentSize().width,
			foodSprite->getContentSize().height);
		if(characterRect.intersectsRect(foodRect))
		{
			foodToDelete->addObject(foodSprite);
			foodFollowArray->addObject(foodSprite);//add foods for following character
			onCheckFoodDisplay->addObject(foodSprite);
		}
	}
	CCARRAY_FOREACH(foodToDelete,foodobject)
	{
		CCSprite* delfood = dynamic_cast<CCSprite*>(foodobject);
		foodFollowArray->addObject(delfood);
		foodSpriteArray->removeObject(delfood);

		//this->removeChild(delfood);
		this->followCharacter(1.0);
	}
	foodToDelete->release();
}
void gameScene::followCharacter(float dt)
{
	CCSprite* tmp= NULL;
	CCObject* object = NULL;
	CCARRAY_FOREACH(foodFollowArray,object)
	{
		CCSprite* followFood = dynamic_cast<CCSprite*>(object);
		CCPoint followPoint = followFood->getPosition();
		followFood->setPosition(beforeMoveCharPoint[0]);
		//foodFollowArray->removeObject(followFood);


	}

}


//-----------------------pineoc End-------------------------------//

//----------------------eunji----------------------------
/*
장애물 부딪혔는지 확인하는 함수
*/
void gameScene::checkPosition(CCPoint position)
{
	CCPoint tileCoord = this->tileCoorPosition(position);

	int tileGid = this->wall->tileGIDAt(tileCoord);

	if(tileGid)
	{
		CCDictionary *properties = tileMap->propertiesForGID(tileGid);

		if(properties)
		{
			CCString *wall = (CCString*)properties->objectForKey("wall");

			if(wall && (wall->compare("Yes") == 0 ))
			{
				checkCrash = CrashWithWall;
				return;
			}

			else
			{
				checkCrash = nothing;
			}
		}
	}
}
//---------------------eunji end -------------------------

//--------------------jiyoon start -----------------------

//pause Scene pop up
void gameScene::doPop(CCObject* pSender)
{
	CCScene* pScene=PauseGameScene::scene();
	this->addChild(pScene,2000,2000);

}
void gameScene::doNotification(CCObject *obj)
{
	//노티피케이션 받기
	CCString *pParam=(CCString*)obj;
	CCLog("notification %s", pParam->getCString());

	if(pParam->intValue()==1)
	{		
		CCLog("noti 11");
		CCDirector::sharedDirector()->resume();   //화면 재시작

		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(PauseMenu, kCCMenuHandlerPriority,true);
		//메뉴 버튼 활성
	}
	else
	{	
		CCArray* childs = this->getChildren();
		CCLog("noti 00");
		CCDirector::sharedDirector()->pause();   //화면 정지

		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(PauseMenu);
		//메뉴버튼 비활성
	}

}
//--------------jiyoon end-----------------------------------------
