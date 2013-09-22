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
#include "gameResultScene.h"
using namespace cocos2d;

enum crashSomething { nothing, CrashWithWall, CrashWithFood, CrashWithItem};
enum DIRCTION { UP, DOWN, LEFT, RIGHT};
gameScene::~gameScene()
{
	delete foodSpriteArray;
	delete foodFollowArray;
	delete onCheckFoodDisplay;
	delete tomakeFood;
}
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
		foodSpriteArray = new CCArray; //food sprite array dynamic cast
		foodFollowArray = new CCArray;
		onCheckFoodDisplay = new CCArray;
		tomakeFood = new CCArray;



		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* bg = CCSprite::create("img\\game\\game_bg.png");
		bg->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(bg,0);


		//------------------------- Daun Start -------------------------------//
		/*
		* make background scene
		* Joung Daun
		* http://blog.naver.com/PostView.nhn?blogId=skmzzang7979&logNo=70142661460
		*/
		CCLayer *tileLayer = CCLayer::create();
		this->addChild(tileLayer);


		// �� ���� �ҷ�����

		tileMap = CCTMXTiledMap::create("map/GameMap.tmx");

		//tileMap->setPosition(size.width * 0.05, size.height * 0.06);
		// -> ���� ���� �� ��ġ �̵���Ű�°���! �ϴ��� 0,0���� �δ°� ���ڴ�!
		//	this->addChild(tileMap,1,2);

		// �� Ÿ�� �ҷ�����

		backgroundLayer = tileMap->layerNamed("wall");

		//---------    eunji for wall    ---------------------

		//metainfo�� �� Ÿ�Ϸ��̾� �̸��� Items������ ��ǥ�� ���� �������̾���.
		// ���� ���� �������� ���� �� ���� ����.
		metainfo = tileMap->layerNamed("Items");
		metainfo->setVisible(false); // �������� ǥ�þ���.
		//		CCAssert(backgroundLayer != NULL, "backgroundLayer not found");
		tileLayer->addChild(tileMap);

		//--------- end eunji ---------------------------

		/*
		* make character
		* Daun..
		*/
		createCharacter();

		moveDirection = UP;

		/*********************************
		* ��ġ �̺�Ʈ�� �޵��� ��
		* Set touch able
		*********************************/
		pDirector = CCDirector::sharedDirector();
		pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);

		this->schedule(schedule_selector(gameScene::moveCharacter));
		//------------------------- Daun End -------------------------------//




		/* pineoc's comments
		links : http://www.raywenderlich.com/40544/cocos2d-x-tile-map-tutorial-part-2
		*/
		CCSize s = tileMap->getContentSize();

		/*
		pineoc's food testing part --------------------------------------------------------------
		*/
		//foods
		this->createFoodShelf();


		foods = tileMap->objectGroupNamed("foods");
		CCDictionary *food1point = foods->objectNamed("food1");
		CCDictionary *food2point = foods->objectNamed("food2");
		CCDictionary *food3point = foods->objectNamed("food3");
		CCDictionary *food4point = foods->objectNamed("food4");
		//
		//counter
		CCTMXObjectGroup *counterGroup = tileMap->objectGroupNamed("endPoint");
		CCDictionary *_counterPoint = counterGroup->objectNamed("counter");
		int counterX = ((CCString*)_counterPoint->objectForKey("x"))->intValue();
		int counterY = ((CCString*)_counterPoint->objectForKey("y"))->intValue();
		counterPoint = ccp(counterX,counterY);
		this->createCounter();

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
		this->schedule(schedule_selector(gameScene::check_counter));
		this->schedule(schedule_selector(gameScene::followCharacter));
		//this->schedule(schedule_selector(gameScene::followCharacter));
		//----------------------------------------------------------------------------------------


		//-------------- obstacle (eunji) --------------------

		CCTMXObjectGroup *obstacle = tileMap->objectGroupNamed("obstacle");
		CCDictionary *obstaclePoint = obstacle->objectNamed("obstaclePoint");

		int obX = ((CCString*)obstaclePoint->objectForKey("x"))->intValue();
		int obY = ((CCString*)obstaclePoint->objectForKey("y"))->intValue();

		obstaclePosition = ccp(obX, obY);
		this->createObstacle();

		countNum = 0;
		checkObDirection = false; //false : ������ true : ����

		this->schedule(schedule_selector(gameScene::moveObstacle), 2.0f); // �����̴� ��ֹ� ����




		//----------------------------------------------------

		//----------------eunji add gauge --------------------//

		character_XP = 100;

		gaugeBar = CCSprite::create("game_status_bar.png");
		gaugeBar->setPosition(ccp(size.width/2, size.height*0.75));

		tileMap->addChild(gaugeBar,2);

		gaugeHeart = CCSprite::create("game_heart.png");
		gaugeHeart->setPosition(ccp(size.width - 20, size.height*0.75));

		tileMap->addChild(gaugeHeart,3);


		//----------------eunji end --------------------------//


		//--------------jiyoon start----------------
		//-------Pause btn-------------------
		CCMenuItemImage *btnPause = CCMenuItemImage::create(
			"img/game/game_btn_pause.png", "img/game/game_btn_pause.png", this, menu_selector(gameScene::doPop));
		CC_BREAK_IF(! btnPause);

		btnPause->setPosition(ccp(size.width*0.8, size.height*0.9));

		PauseMenu = CCMenu::create(btnPause, NULL);
		PauseMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! PauseMenu);

		this->addChild(PauseMenu, 2);

		//notification �߰�
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
			callfuncO_selector(gameScene::doNotification),
			"notification", NULL);
		//"notification"�̶�� �޽����� ���� �ش� �Լ��� �����Ѵ�.

		//---------Items--------------

		//decide kind of item.
		srand(time(0));	//random
		int kindOfItem = rand()%4 + 1;	//range : 1~4
		item1 =NULL, item2 = NULL, item3 =NULL, item4=NULL;
		CCTMXObjectGroup *items = tileMap->objectGroupNamed("items");


		//select item decided before
		if (kindOfItem == 1)
		{
			//Add item1
			CCDictionary* item1 = items->objectNamed("item1");

			//Set item's position
			int temX = ((CCString*)item1->objectForKey("x"))->intValue();
			int temY = ((CCString*)item1->objectForKey("y"))->intValue();

			itemPosition = ccp(temX,temY);
			this->createItem1();

		}
		else if (kindOfItem == 2)
		{
			//Add item2
			CCDictionary* item2 = items->objectNamed("item2");

			//Set item's position
			int temX = ((CCString*)item2->objectForKey("x"))->intValue();
			int temY = ((CCString*)item2->objectForKey("y"))->intValue();

			itemPosition = ccp(temX,temY);
			this->createItem2();

		}
		else if (kindOfItem == 3)
		{
			//Add item3
			CCDictionary* item3 = items->objectNamed("item3");

			//Set item's position
			int temX = ((CCString*)item3->objectForKey("x"))->intValue();
			int temY = ((CCString*)item3->objectForKey("y"))->intValue();

			itemPosition = ccp(temX,temY);
			this->createItem3();

		}
		else if (kindOfItem == 4)
		{
			//Add item4
			CCDictionary* item4 = items->objectNamed("item4");

			//Set item's position
			int temX = ((CCString*)item4->objectForKey("x"))->intValue();
			int temY = ((CCString*)item4->objectForKey("y"))->intValue();

			itemPosition = ccp(temX,temY);
			this->createItem4();

		}

		this->schedule(schedule_selector(gameScene::check_item));

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
{// ��ֹ� ���� ����

	CCTexture2D *obTexture = CCTextureCache::sharedTextureCache()->addImage("map/meat.png");

	obstacle = CCSprite::createWithTexture(obTexture,CCRectMake(0, 0, 48, 48)); // �ʿ� ���� ���� �ٲ����
	obstacle->setPosition(obstaclePosition);
	obstacle->setAnchorPoint(ccp(0,0));
	this->addChild(obstacle);

}



//------------------------ Daun Start ----------------------------//
/*
* void gameScene::onEnter()
* this function work to use touch.
* ��ġ�� �Է¹��� ���� �����ϴ� �Լ�
* �̰� �־�� ��ġ�� ����
* Daun..
*/
void gameScene::onEnter()
{
	CCLayer::onEnter();

}
/*
*	ĳ���� �̵���Ű�� �Լ�
*
*/
void gameScene::moveCharacter(float dt)
{
	// HAVETODO
	// ĳ���� �̵���Ŵ!!
	

	CCPoint playerPos = character->getPosition();

	int checkCrash = nothing;
	/********************************************************** To EVERYONE *************
	* check character is crash with someting
	* �浹���θ� �Ǵ��ϴ� �����Դϴ�
	* enum crashSomething { nothing, CrashWithWall, CrashWithFood, CrashWithItem};
	* ��, checkCrash�� 0�̸� �ƹ��͵� �Ⱥ΋Hģ��, 1�̸� ��, 2�̸� ���� 3�̸� �������̶� �΋Hģ����
	*/

	/*
	* ���� �浹�ߴ��� Ȯ���ϴ� �����Դϴ�
	* To Eunji
	*/

	//�̺κ��� ���� �ʿ���. �ٿ��ڵ� �����ؼ� ����׷��µ� �� �ȵǳ�..
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

	CCPoint tileCoord = this->tileCoorPosition(playerPos);

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
	* ���İ� �浹�ߴ��� Ȯ���ϴ� �����Դϴ�
	check collision food and character
	*/
	beforeMoveCharPoint[0] = character->getPosition();
	foodFollowCnt=1;
	CCObject* ob = NULL;
	CCARRAY_FOREACH(foodFollowArray,ob)
	{
		CCSprite* foodFollow = dynamic_cast<CCSprite*>(ob);
		beforeMoveCharPoint[foodFollowCnt] = foodFollow->getPosition();
		foodFollowCnt++;
	}


	/* End pineoc */




	/*
	* �����۰� �浹�ߴ��� Ȯ���ϴ� �����Դϴ�
	*/
	// ���⿡ �ڵ��ۼ�

	/* end blackbell */





	if(checkCrash == nothing)
	{
		if(moveDirection == UP)
		{
			playerPos.y += tileMap->getTileSize().height;
		}
		else if (moveDirection == DOWN)
		{
			playerPos.y -= tileMap->getTileSize().height;
		}
		else if (moveDirection == LEFT)
		{
			playerPos.x -= tileMap->getTileSize().width;
		}
		else if (moveDirection == RIGHT)
		{
			playerPos.x += tileMap->getTileSize().width;
		}
		else
		{
		}
		

	}
	else if(checkCrash == CrashWithWall)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		// ���� �浹�� ��� �ؾ��� ��
		character->setPosition(originPos);

		character_XP -= 10;

		int gaugeSize_part = 441/10; // �������� �������� 10�ۼ�Ʈ ����
		int gaugeNum = (gaugeSize_part * ((100 - character_XP) / 10));

		if( character_XP > 0 )
		{
			gaugeHeart->setPositionX(size.width - (20 + gaugeNum)); // 10�ۼ�Ʈ�� ��Ʈ�� �ű�.
		}

		else
		{
			//������ ������
			gaugeHeart->setPositionX(20);
			this->go_endResultScene();
		}
	}
	else if(checkCrash == CrashWithFood)
	{
		// ���İ� �浹�� ��� �ؾ��� ��

	}
	else if(checkCrash == CrashWithItem)
	{
		// �����۰� �浹�� ��� �ؾ��� ��
	}

	if (playerPos.x <= (tileMap->getMapSize().width * tileMap->getTileSize().width) &&
			playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height) &&
			playerPos.y >= 0 &&
			playerPos.x >= 0 )
		{
			// ĳ������ ���ο� ��ġ ����
			character->setPosition( playerPos );
		}
	Sleep(1000);

}
/*
* bool gameScene::ccTouchBegan(CCTouch *, CCEvent *)
* when touch start, this function work
* ȭ�鿡 �հ����� ������
* Daun..
*/
bool gameScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event)
{

	return true;
}

/*
* void gameScene::ccTouchEnded(CCTouch *, CCEvent *)
* When touch end, this function work
* now character is moved to way w
* ȭ�鿡�� �հ����� ��������
* ���翡�� ĳ���͸� �߽����� ȭ���� ��� �κ��� ��ġ�Ǿ����Ŀ� ����
* ĳ���Ͱ� �̵��մϴ�.
* Daun..
*/
void gameScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event)
{
	CCPoint playerPos = character->getPosition();
	CCPoint touchLocation = pTouch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);

	originPos = character->getPosition();
		// ĳ���Ͱ� �浹���� �������~
		// ���콺 Ŭ���� �������� ������!
		CCPoint diff = ccpSub(touchLocation, playerPos);

		if (abs(diff.x) > abs(diff.y)) {
			if (diff.x > 0) {
				
				moveDirection = RIGHT;
				// ĳ������ ������ �ٲپ��ش�.
				character->setFlipX(true);
			} else {
				
				moveDirection = LEFT;
				// ĳ������ ������ �ٲپ��ش�.
				character->setFlipX(false);
			}
		} else {
			if (diff.y > 0) {
				
				moveDirection = UP;
			} else {
				
				moveDirection = DOWN;
			}
		}

		
}

void gameScene::createCharacter()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();


	// Ÿ�ϸʿ��� Object��� ������ ������Ʈ ��ü�� ��������
	CCTMXObjectGroup *object = tileMap->objectGroupNamed("object");
	// �Ӽ��� �о���� (characterPosition)
	CCDictionary *spawnPoint = object->objectNamed("character");

	int x = ((CCString*)spawnPoint->objectForKey("x"))->intValue() + 1;
	int y = ((CCString*)spawnPoint->objectForKey("y"))->intValue() + 1;

	CCPoint characterPosition = ccp(x,y);




	// make charcter show in map

	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("img/character/character.png");

	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);


	character = CCSprite::createWithTexture(texture, CCRectMake(0,0,35,48));
	character->setAnchorPoint(ccp(0,0));

	// character->setScale(0.05);
	character->setPosition(characterPosition);
	//character->setFlipX(true); // X�� �������� ����
	//character->setFlipY(true);	// Y�� �������� ����

	CCAnimate *animate = CCAnimate::create(animation);
	CCAction *rep = CCRepeatForever::create(animate);
	character->runAction(rep);

	this->addChild(character,60);
}


// -----------------------Daun End -------------------------------//

//------------------------Pineoc's part---------------------------//
void gameScene::createFood(CCPoint foodpoint,char* foodImageName)
{//collision correct, duplication correct
	//�Ŀ� ���ڰ��� CCArray�� �޾Ƽ� ������Ḧ �� �Ѹ��°����� ����.
	CCTexture2D *foodTexture = CCTextureCache::sharedTextureCache()->addImage(foodImageName);
	CCSprite* food = CCSprite::createWithTexture(foodTexture,CCRectMake(0, 0, 48, 48)); // �ʿ� ���� ���� �ٲ����
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

/*
���� ��Ḧ �Ծ����� �������� ��.
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
	CCSprite* tmpSprite= NULL;
	CCObject* object = NULL;
	CCPoint tmp1=beforeMoveCharPoint[0];
	CCPoint tmp2;

	for(int i=1;i<foodFollowArray->count();i++)
	{
		CCSprite* foodf = dynamic_cast<CCSprite*>(foodFollowArray->objectAtIndex(i));
		foodf->setPosition(tmp1);
		tmp2=beforeMoveCharPoint[i];
		tmp1=tmp2;	
	}
}
void gameScene::check_counter(float dt)
{// check counter if crash with character and counter
	CCRect characterRect = CCRectMake(character->getPosition().x - (character->getContentSize().width/2),
		character->getPosition().y -(character->getContentSize().height/2),
		character->getContentSize().width,
		character->getContentSize().height);
	CCRect counterRect = CCRectMake(counter->getPosition().x - (counter->getContentSize().width/2),
		counter->getPosition().y -(counter->getContentSize().height/2),
		counter->getContentSize().width,
		counter->getContentSize().height);
	if(characterRect.intersectsRect(counterRect))
	{// call gameResultScene
		this->go_endResultScene();
	}
}
//make Sprite to eat food.
void gameScene::createFoodShelf()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//for(){}
	
	CCSprite* foodShelf1 = CCSprite::create("map/carrot.png");
	CCSprite* foodShelf2 = CCSprite::create("map/meat.png");
	foodShelf1->setPosition(ccp(size.width*0.12+10,size.height*0.74));
	foodShelf2->setPosition(ccp(size.width*0.24+10,size.height*0.74));//0.1+0.11( or 0.12)
	this->addChild(foodShelf1);
	this->addChild(foodShelf2);
}


//make counter
void gameScene::createCounter()
{
	CCTexture2D *counterTexture = CCTextureCache::sharedTextureCache()->addImage("map/counter.jpg");
	CCSprite* _counter = CCSprite::createWithTexture(counterTexture,CCRectMake(0, 0, 48, 48));
	_counter->setPosition(counterPoint);
	_counter->setAnchorPoint(ccp(0,0));
	counter = _counter;
	this->addChild(counter);
}

//collision with character, go to gameResultScene
void gameScene::go_endResultScene()
{
	CCScene *pScene = CCScene::create();
	gameResultScene *layer = new gameResultScene(result,stageidx);
	layer->autorelease();
	pScene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(pScene);

}


//-----------------------pineoc End-------------------------------//




//--------------------jiyoon start -----------------------

//pause Scene pop up
void gameScene::doPop(CCObject* pSender)
{

	/*********************************
	* ��ġ�� ���� �ʵ��� ��
	* Set touch enable
	* Daun
	*********************************/	
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	/***********  Daun End ********/

	CCScene* pScene=PauseGameScene::scene();
	this->addChild(pScene,2000,2000);

}
void gameScene::doNotification(CCObject *obj)
{
	//��Ƽ�����̼� �ޱ�
	CCString *pParam=(CCString*)obj;
	CCLog("notification %s", pParam->getCString());

	if(pParam->intValue()==1)
	{		
		CCLog("noti 11");
		CCDirector::sharedDirector()->resume();   //ȭ�� �����

		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(PauseMenu, kCCMenuHandlerPriority,true);
		//�޴� ��ư Ȱ��


		/********************************
		* Set Touch able
		* Daun..
		*********************************/
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		/****** Daun End ********************/

	}
	else
	{	
		CCArray* childs = this->getChildren();
		CCLog("noti 00");
		CCDirector::sharedDirector()->pause();   //ȭ�� ����
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(PauseMenu);
		//�޴���ư ��Ȱ��
	}

}


//Create item 4 kinds
//Item1 - 
void gameScene::createItem1()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("down.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 48, 48));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item1 = item;
	this->addChild(item1);
}

//Item2 -
void gameScene::createItem2()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("left.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 48, 48));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item2 = item;
	this->addChild(item2);
}

//Item3 -
void gameScene::createItem3()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("right.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 48, 48));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item3 = item;
	this->addChild(item3);
}

//Item4
void gameScene::createItem4()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("dog.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 48, 48));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item4 = item;
	this->addChild(item4);
}

void gameScene::check_item(float dt)
{
	//check collision - item, character
	CCRect characterRect = CCRectMake(character->getPosition().x - (character->getContentSize().width/2),
		character->getPosition().y - (character->getContentSize().height/2),
		character->getContentSize().width, character->getContentSize().height);
	
	CCRect item1Rect;
	CCRect item2Rect;
	CCRect item3Rect;
	CCRect item4Rect;
	if(item1 !=NULL)
	{
		item1Rect = CCRectMake(item1->getPosition().x - (item1->getContentSize().width/2),
			item1->getPosition().y - (item1->getContentSize().height/2),
			item1->getContentSize().width, item1->getContentSize().height);
	}
	if(item2 !=NULL)
	{
		item2Rect = CCRectMake(item2->getPosition().x - (item2->getContentSize().width/2),
			item2->getPosition().y - (item2->getContentSize().height/2),
			item2->getContentSize().width, item2->getContentSize().height);
	}
	if(item3 !=NULL)
	{
		item3Rect = CCRectMake(item3->getPosition().x - (item3->getContentSize().width/2),
			item3->getPosition().y - (item3->getContentSize().height/2),
			item3->getContentSize().width, item3->getContentSize().height);
	}
	if(item4 !=NULL)
	{
		item4Rect = CCRectMake(item4->getPosition().x - (item4->getContentSize().width/2),
			item4->getPosition().y - (item4->getContentSize().height/2),
			item4->getContentSize().width, item4->getContentSize().height);
	}

	if(characterRect.intersectsRect(item1Rect))
	{
		//slow down effect
		this->removeChild(item1);
		item1=NULL;
	}
	if(characterRect.intersectsRect(item2Rect))
	{
		//superpower effect
		this->removeChild(item2);
		item2=NULL;
	}
	if(characterRect.intersectsRect(item3Rect))
	{
		//energy up effect
		this->removeChild(item3);
		item3=NULL;
	}
	if(characterRect.intersectsRect(item4Rect))
	{
		//?? effect
		this->removeChild(item4);
		item4=NULL;
	}
}
//--------------jiyoon end-----------------------------------------

//------------- eunji move obstacle -------------------------//

void gameScene::moveObstacle(float dt)
{/*
	countNum++;
	if(countNum > 60)
	{
		countNum = 1; */
		checkObDirection = !(checkObDirection);
	//}

	if(checkObDirection == true)
	{
		obstacle->setPositionX(obstacle->getPositionX() + 80);
	}

	else if(checkObDirection == false)
	{
		obstacle->setPositionX(obstacle->getPositionX() - 80);
	}
}

//------------- eunji end ---------------------------------//
