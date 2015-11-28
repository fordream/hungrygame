/**
* 2013 08 18
* Joung Daun
* GameScene
*/
#include "stageSelectScene.h"
#include "music.h"
#include "mainScene.h"
#include "gameScene.h"
#include "PauseGameScene.h"
#include "gameResultScene.h"
#include "userData.h"
using namespace cocos2d;

enum crashSomething { nothing, CrashWithWall, CrashWithFood, CrashWithItem};
enum DIRCTION { UP, DOWN, LEFT, RIGHT};
#define MOVEX 23.2
#define MOVEY 46.5


//gameScene::gameScene(int stageIDX)
//{
//	//////////////////////////////////////////////////////////////////////////
//	// super init first
//	//////////////////////////////////////////////////////////////////////////
//	gStageidx = stageIDX;
//	init();
//}

/*
* ** DESTRUCTURE
* ~gameScene()									destructure about gameScene class
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
gameScene::~gameScene()
{
	delete foodSpriteArray;
	delete foodFollowArray;
	this->onExit();
}
CCScene* gameScene::scene()
{
	CCScene* scene = CCScene::create();

	gameScene *layer = gameScene::create();

	scene->addChild(layer);

	return scene;
}



// on "init" you need to initialize your instance
/*
* ** FUNCTION
* bool init()									when scene made, this function is first called.
* Input											nothing
* Output										True
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun , eunji, jiyoon, pineoc
*/
bool gameScene::init()
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return false;
	gStageidx = CCUserDefault::sharedUserDefault()->getIntegerForKey("curStage");
	//////////////////////////////////////////////////////////////////////////
	// add your codes below...
	//////////////////////////////////////////////////////////////////////////
	foodSpriteArray = new CCArray; //food sprite array dynamic cast
	foodFollowArray = new CCArray;
	result=" ";
	isSuper = false;
	

	//using stageidx for regame
	//set idx end. 
	//gStageidx = stageIDX;
	char map[16];
	sprintf(map, "map/%d.tmx", gStageidx);

	music m;
	m.effectStart("sound\\effect_supermarket.mp3");

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	/* Set background img		: Daun */
	CCSprite* bg = CCSprite::create("img\\game\\game_bg.png");
	bg->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(bg,0);
	char stagenum[32];
	sprintf(stagenum,"img\\game\\stageNum\\%d.png",gStageidx-9);
	CCSprite* stageNSprite = CCSprite::create(stagenum);
	stageNSprite->setPosition(ccp(size.width*0.32,size.height*0.93));
	this->addChild(stageNSprite,0);


	/* Set Tiled Map			: Daun, eunji*/
	CCLayer *tileLayer = CCLayer::create();
	this->addChild(tileLayer);

	tileMap = CCTMXTiledMap::create(map);
	tileMap->setPosition(MOVEX , MOVEY);
	if(tileMap->layerNamed("wall"))
		backgroundLayer = tileMap->layerNamed("wall");

	//metainfo에 준 타일레이어 이름은 Items이지만 벽표시 위한 빨간레이어임.
	// 추후 실제 아이템을 포함 할 수도 있음.
	if(tileMap->layerNamed("Items"))
	{
		metainfo = tileMap->layerNamed("Items");
		metainfo->setVisible(false); // 빨간벽을 표시안함.
	}
	tileLayer->addChild(tileMap);



	/* Make Character			: Daun */
	createCharacter();

	movingSpeed = 0.45;														// set initial character moving speed
	moveDirection = UP;													// set default character moving direction

	this->schedule(schedule_selector(gameScene::moveCharacter),movingSpeed);



	/* set touch enable			: Daun*/
	pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);



	/* make food				: Pineoc */
	
	this->createFood();
	foodcount = foodSpriteArray->count();
	this->createFoodShelf();
	this->schedule(schedule_selector(gameScene::updateFoodSprte));
	this->schedule(schedule_selector(gameScene::check_counter));
	this->schedule(schedule_selector(gameScene::followCharacter));
	this->schedule(schedule_selector(gameScene::checkFollowFoodCollision));


	/* make obstacle			: eunji */
	isPause = false;

	if(tileMap->objectGroupNamed("obstacle"))
	{

		CCTMXObjectGroup *obstacle = tileMap->objectGroupNamed("obstacle");
		CCDictionary *obstaclePoint = obstacle->objectNamed("obstaclePoint");

		obX = ((CCString*)obstaclePoint->objectForKey("x"))->intValue();
		obY = ((CCString*)obstaclePoint->objectForKey("y"))->intValue();

		obstaclePosition = ccp(obX+MOVEX, obY+MOVEY);


		this->createObstacle();

		countNum = 0;
		checkObDirection = false; //false : 오른쪽 true : 왼쪽

		this->schedule(schedule_selector(gameScene::moveObstacleHeight), 1.0f); // 움직이는 장애물 구현
	}



	/* make gauge				: eunji */
	character_XP = 100;

	gaugeBar = CCSprite::create("game_status_bar.png");
	gaugeBar->setPosition(ccp(size.width*0.45, size.height*0.79));

	tileMap->addChild(gaugeBar,2);

	gaugeHeart = CCSprite::create("game_heart.png");
	gaugeHeart->setPosition(ccp(size.width - 30, size.height*0.79));

	tileMap->addChild(gaugeHeart,3);




	/* make pause btn			: jiyoon, daun */
	btnPause = CCSprite::create("img/game/game_btn_pause.png");
	btnPause->setAnchorPoint(ccp(0,0));

	pauseBtnPosition = ccp(size.width*0.8, size.height*0.9);
	btnPause->setPosition(pauseBtnPosition);
	this->addChild(btnPause);


	/* Add notification			: jiyoon */
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(gameScene::doNotification),
		"notification", NULL);
	//"notification"이라는 메시지가 오면 해당 함수를 실행한다.



	/* Add Items				: jiyoon */
	//decide kind of item.
	srand(time(0));	//random
	int kindOfItem = 4;//rand()%4 + 1;	//range : 1~4
	item1 =NULL, item2 = NULL, item3 =NULL, item4=NULL;
	if(tileMap->objectGroupNamed("items"))
	{
		CCTMXObjectGroup *items = tileMap->objectGroupNamed("items");


		//select item decided before
		if (kindOfItem == 1)
		{
			//Add item1
			CCDictionary* item1 = items->objectNamed("item1");

			//Set item's position
			int temX = ((CCString*)item1->objectForKey("x"))->intValue();
			int temY = ((CCString*)item1->objectForKey("y"))->intValue();

			itemPosition = ccp(temX+MOVEX,temY+MOVEY);
			this->createItem1();

		}
		else if (kindOfItem == 2)
		{
			//Add item2
			CCDictionary* item2 = items->objectNamed("item2");

			//Set item's position
			int temX = ((CCString*)item2->objectForKey("x"))->intValue();
			int temY = ((CCString*)item2->objectForKey("y"))->intValue();

			itemPosition = ccp(temX+MOVEX,temY+MOVEY);
			this->createItem2();

		}
		else if (kindOfItem == 3)
		{
			//Add item3
			CCDictionary* item3 = items->objectNamed("item3");

			//Set item's position
			int temX = ((CCString*)item3->objectForKey("x"))->intValue();
			int temY = ((CCString*)item3->objectForKey("y"))->intValue();

			itemPosition = ccp(temX+MOVEX,temY+MOVEY);
			this->createItem3();

		}
		else if (kindOfItem == 4)
		{
			//Add item4
			CCDictionary* item4 = items->objectNamed("item4");

			//Set item's position
			int temX = ((CCString*)item4->objectForKey("x"))->intValue();
			int temY = ((CCString*)item4->objectForKey("y"))->intValue();

			itemPosition = ccp(temX+MOVEX,temY+MOVEY);
			this->createItem4();

		}
	}
	this->schedule(schedule_selector(gameScene::check_item));
	return true;
}
/*
* ** FUNCTION
* CCPoint tileCoorPosition(CCPoint)				??????????????
* Input											position 
* Output										???????
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/


CCPoint gameScene::tileCoorPosition(CCPoint position)
{
	int x = position.x / tileMap->getTileSize().width;
	int y = ((tileMap->getMapSize().height * tileMap->getTileSize().height) - position.y) / tileMap->getTileSize().height;
	return ccp(x, y);
}

/*
* ** FUNCTION
* void createObstacle()							create Obstacle
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/
void gameScene::createObstacle()
{
	CCTexture2D *obTexture = CCTextureCache::sharedTextureCache()->addImage("map/meat.png");

	obstacle = CCSprite::createWithTexture(obTexture,CCRectMake(0, 0, 60, 60)); // 맵에 맞춰 숫자 바꿔야함
	obstacle->setPosition(obstaclePosition);
	obstacle->setAnchorPoint(ccp(0,0));
	this->addChild(obstacle);

}


/*
* ** FUNCTION
* void onEnter()								called when enter this scene.
*												if this function not exist, touch event can not accepted.
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun
*/
void gameScene::onEnter()
{
	CCLayer::onEnter();

}

/*
* ** FUNCTION
* void moveCharacter(float)						make schedule function about moving character to it's own direction.
* Input											float dt for schedule.
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun, eunji, pineoc
*/
void gameScene::moveCharacter(float dt)
{
	CCPoint playerPos = character->getPosition();
	CCPoint originalplayerPos = character->getPosition();
	int checkCrash = nothing;



	/*  check collision food and character						: Pineoc*/
	beforeMoveCharPoint[0] = character->getPosition();
	foodFollowCnt=1;
	CCObject* ob = NULL;
	CCARRAY_FOREACH(foodFollowArray,ob)
	{
		CCSprite* foodFollow = dynamic_cast<CCSprite*>(ob);
		beforeMoveCharPoint[foodFollowCnt] = foodFollow->getPosition();
		foodFollowCnt++;
	}



	if(checkCrash == nothing)
	{
		if      (moveDirection == UP)	 {	playerPos.y += tileMap->getTileSize().height;	}
		else if (moveDirection == DOWN)  {	playerPos.y -= tileMap->getTileSize().height;	}
		else if (moveDirection == LEFT)	 {	playerPos.x -= tileMap->getTileSize().width;	}
		else if (moveDirection == RIGHT) {	playerPos.x += tileMap->getTileSize().width;	}
		else{}
	}

	/* check if character crash with wall						: eunji, Daun */

	if (playerPos.x <= (tileMap->getMapSize().width * tileMap->getTileSize().width)
		&& playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height)
		&& playerPos.y >= 0
		&& playerPos.x >= 0 )
	{
		// 캐릭터가 이동할 위치가 맵 안인경우 벽에 충돌햇는지를 검사합니다 By Daun
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
					character->setPosition(playerPos);
					checkCrash = CrashWithWall;
					moveDirection = (moveDirection + 2 ) % 4;
				}
			}
		}
	}
	else
	{
		// 캐릭터가 이동할 위치가 맵 밖이므로 벽에 충돌한 것과 마찬가지입니다.
		checkCrash = CrashWithWall;
		moveDirection = (moveDirection + 2 ) % 4;
	}



	/* when character crash with wall							: eunji, Daun, jiyun */
	if(checkCrash == CrashWithWall)
	{
		music m;
		m.effectStart("sound\\effect_crash_wall.mp3");

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		if(isSuper==false)
		{
			// 벽과 충돌한 경우 해야할 일
			character->setPosition(originalplayerPos);							// By Daun.. 충돌인 경우 원래 위치로 계쏙 유지
			character_XP -= 10;

			int gaugeSize_part = 441/10;										// 게이지바 사이즈의 10퍼센트 길이
			int gaugeNum = (gaugeSize_part * ((100 - character_XP) / 10));


			decreaseGaugeBar(gaugeNum);
		}

	}
	else
	{
		if (playerPos.x <= (tileMap->getMapSize().width * tileMap->getTileSize().width)
			&& playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height)
			&& playerPos.y >= 0
			&& playerPos.x >= 0 )
		{
			character->setPosition( playerPos );							// 캐릭터의 새로운 위치 지정
		}
	}


	//Sleep(movingSpeed);
}

/*
* ** FUNCTION
* bool ccTouchBegan(CCTouch*, CCEvent*)			when touch is began
* Input											touch position , event
* Output										true
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun
*/
bool gameScene::ccTouchBegan(CCTouch *pTouch, CCEvent* event) {	return true; }


/*
* ** FUNCTION
* void ccTouchEnded(CCTouch *, CCEvent* )		when touch action is ended this function called.
* Input											touch position, event
* Output										true
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun ,jiyoon
*/
void gameScene::ccTouchEnded(CCTouch *pTouch, CCEvent* event)
{
	CCPoint playerPos = character->getPosition();
	CCPoint touchLocation = pTouch->getLocation();
	touchLocation = this->convertToNodeSpace(touchLocation);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	/* check pause btn is pressed or not	: daun */
	CCPoint pauseDiff = ccpSub(touchLocation,pauseBtnPosition);
	float pauseBtnWidth = size.width * 0.1;
	float pauseBtnHeight = size.height * 0.1;

	if((abs(pauseDiff.x) <= pauseBtnWidth) && (abs(pauseDiff.y) <= pauseBtnHeight))
	{
		music m;
		m.effectStart("sound\\effect_btn_click.mp3");
		this->doPop( (CCObject*)gStageidx );
	}

	originPos = character->getPosition();

	/*  set moveDirection					: daun */
	// 캐릭터를 기준으로 어느 위치를 클릭했는지에 따라 캐릭터가 이동할 방향 결정
	CCPoint diff = ccpSub(touchLocation, playerPos);

	if (abs(diff.x) > abs(diff.y))
	{
		if (diff.x > 0) {	if(moveDirection != LEFT) {moveDirection = RIGHT;	character->setFlipX(true);} } 
		else			{	if(moveDirection != RIGHT) {moveDirection = LEFT;	character->setFlipX(false);} }
	} 
	else 
	{
		if (diff.y > 0) {	if(moveDirection != DOWN) moveDirection = UP;	 } 
		else			{	if(moveDirection != UP) moveDirection = DOWN;}
	}
}
/*
* ** FUNCTION
* void createCharacter()						make character on map
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Daun
*/
void gameScene::createCharacter()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();


	CCTMXObjectGroup *object = tileMap->objectGroupNamed("object");
	CCDictionary *spawnPoint = object->objectNamed("character");

	int x = ((CCString*)spawnPoint->objectForKey("x"))->intValue() + 1;
	int y = ((CCString*)spawnPoint->objectForKey("y"))->intValue() + 1;

	CCPoint characterPosition = ccp(x+MOVEX,y+MOVEY);

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

	animate = CCAnimate::create(animation);
	rep = CCRepeatForever::create(animate);
	character->runAction(rep);

	this->addChild(character,60);
}


/*
* ** FUNCTION
* void createFood()								create food
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::createFood()
{//collision correct, duplication correct
	//후에 인자값을 CCArray로 받아서 음식재료를 다 뿌리는것으로 만듬.
	//char* inputdata = NULL;
	//CCString *a=NULL;
	const char* foodarr[10]={"food1","food2","food3","food4","food5","food6","food7","food8","food9","food10"};
	//for sprite food



	//create counter
	CCTMXObjectGroup *counterGroup = tileMap->objectGroupNamed("endPoint");
	CCDictionary *_counterPoint = counterGroup->objectNamed("counter");
	int counterX = ((CCString*)_counterPoint->objectForKey("x"))->intValue();
	int counterY = ((CCString*)_counterPoint->objectForKey("y"))->intValue();
	counterPoint = ccp(counterX+MOVEX,counterY+MOVEY);
	this->createCounter();
	//create counter end


	//
	char food_arr[20];
	sprintf(food_arr,"/img/food/%d_f.png",gStageidx);
	CCTexture2D *foodTexture = CCTextureCache::sharedTextureCache()->addImage(food_arr);
	foods = tileMap->objectGroupNamed("foods");

	for(int i = 0 ; i < 10; i++)
	{
		CCDictionary *dfoodpoint ;
		if(!(dfoodpoint= foods->objectNamed(foodarr[i])))
			break;
		//if does not have food, break
		int foodX = ((CCString*)dfoodpoint->objectForKey("x"))->intValue();
		int foodY = ((CCString*)dfoodpoint->objectForKey("y"))->intValue();
		CCPoint foodpoint = ccp(foodX+MOVEX,foodY+MOVEY);
		CCSprite* food = CCSprite::createWithTexture(foodTexture,CCRectMake(100*(i%5),100*(i/5),100,100));
		food->setPosition(foodpoint);
		food->setScale(0.48);
		food->setTag(i+1);
		food->setAnchorPoint(ccp(0,0));
		foodSpriteArray->addObject(food);
		this->addChild(food);
	}


}


/*
* ** FUNCTION
* bool checkDup(CCSprite*)						check duplication function
* Input											Food we need to check duplication		???
* Output										scene
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
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
* ** FUNCTION
* void updateFoodSprte(float)					when character eat food, make food dissappear.
* Input											float for schedule.
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::updateFoodSprte(float dt)
{
	CCArray* foodToDelete = new CCArray;
	CCObject* foodobject = NULL;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCARRAY_FOREACH(foodSpriteArray,foodobject)
	{
		CCRect characterRect = CCRectMake(character->getPosition().x - (character->getContentSize().width/2),
			character->getPosition().y -(character->getContentSize().height/2),
			character->getContentSize().width,
			character->getContentSize().height);
		CCSprite* foodSprite = dynamic_cast<CCSprite*>(foodobject);
		CCRect foodRect = CCRectMake(foodSprite->getPosition().x - (foodSprite->getContentSize().width/2*foodSprite->getScale()),
			foodSprite->getPosition().y -(foodSprite->getContentSize().height/2*foodSprite->getScale()),
			foodSprite->getContentSize().width*foodSprite->getScale(),
			foodSprite->getContentSize().height*foodSprite->getScale());
		if(characterRect.intersectsRect(foodRect))
		{
			foodToDelete->addObject(foodSprite);
			//foodFollowArray->addObject(foodSprite);//add foods for following character
			//foodSpriteArray->removeObject(foodobject);
		}
	}
	CCARRAY_FOREACH(foodToDelete,foodobject)
	{
		CCSprite* delfood = dynamic_cast<CCSprite*>(foodobject);
		foodFollowArray->addObject(delfood);
		foodSpriteArray->removeObject(delfood);
	}

	foodToDelete->release();
}
/*
* ** FUNCTION
* void checkFollowFoodCollision(float)			check if charcter crash with food
* Input											float for schedule
* Output										scene
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::checkFollowFoodCollision(float dt)
{
	CCObject* foodobject = NULL;
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCARRAY_FOREACH(foodFollowArray,foodobject)
	{
		CCRect characterRect = CCRectMake(character->getPosition().x - (character->getContentSize().width/2),
			character->getPosition().y -(character->getContentSize().height/2),
			character->getContentSize().width,
			character->getContentSize().height);
		CCSprite* foodSprite = dynamic_cast<CCSprite*>(foodobject);
		CCRect foodRect = CCRectMake(foodSprite->getPosition().x - (foodSprite->getContentSize().width/2*foodSprite->getScale()),
			foodSprite->getPosition().y -(foodSprite->getContentSize().height/2*foodSprite->getScale()),
			foodSprite->getContentSize().width*foodSprite->getScale()-20,
			foodSprite->getContentSize().height*foodSprite->getScale()-20);
		if(characterRect.intersectsRect(foodRect) 
			&& foodFollowArray->objectAtIndex(0)!=foodobject 
			&& foodFollowArray->objectAtIndex(1)!=foodobject
			&& foodFollowArray->objectAtIndex(2)!=foodobject)
		{
			this->decreaseGaugeBar(10);
		}

	}
}
/*
* ** FUNCTION
* void followCharacter(float dt)				make food follow the character.
* Input											float for schedule
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::followCharacter(float dt)
{
	CCSprite* tmpSprite= NULL;
	CCObject* object = NULL;
	CCPoint tmp1=beforeMoveCharPoint[0];
	CCPoint tmp2;

	for(int i=1;i<foodFollowArray->count()+1;i++)
	{
		CCSprite* foodf = dynamic_cast<CCSprite*>(foodFollowArray->objectAtIndex(i-1));
		foodf->setPosition(tmp1);
		tmp2=beforeMoveCharPoint[i];
		tmp1=tmp2;	
	}
}
/*
* ** FUNCTION
* void check_counter(float dt)					check if character come to counter
* Input											float for schedule
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
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
		this->go_endResultScene(1);
	}
}

/*
* ** FUNCTION
* void createFoodShelf()						make Sprite to eat food.
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::createFoodShelf()
{// have to : add food count
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	char food_arr[20];
	sprintf(food_arr,"/img/food/%d_f.png",gStageidx);
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(food_arr);
	for(int i=0;i<7;i++)
	{
		CCSprite* foodsprite = CCSprite::createWithTexture(texture,CCRectMake(100*(i%5),100*(i/5),100,100));
		CCPoint position = ccp((size.width*0.12*(i+1)),size.height*0.73);
		foodsprite->setAnchorPoint(ccp(0,0));
		foodsprite->setPosition(position);
		foodsprite->setScale(0.5);
		this->addChild(foodsprite);
	}
}



/*
* ** FUNCTION
* void createCounter()							make counter
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::createCounter()
{
	CCTexture2D *counterTexture = CCTextureCache::sharedTextureCache()->addImage("map/counter.png");
	CCSprite* _counter = CCSprite::createWithTexture(counterTexture,CCRectMake(0, 0,60,60));
	_counter->setPosition(counterPoint);
	_counter->setAnchorPoint(ccp(0,0));
	counter = _counter;
	this->addChild(counter);
}

/*
* ** FUNCTION
* void go_endResultScene()						collision with character, go to gameResultScene
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::go_endResultScene(int chk)
{
	if(chk==1)
		this->checkFoodToEnd();
	else
		result=" ";
	CCScene *pScene = CCScene::create();
	gameResultScene *layer = new gameResultScene(result,gStageidx,foodcount);
	layer->autorelease();
	pScene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(pScene);

}
/*
* ** FUNCTION
* void checkFoodToEnd()							make string about what character eat.
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											Pineoc
*/
void gameScene::checkFoodToEnd()
{//string result = ?
	char c[10]="";
	int count = foodFollowArray->count();
	for(int i=0;i<count;i++)
	{
		CCSprite* a = ((CCSprite*)foodFollowArray->objectAtIndex(i));
		int b = a->getTag();
		sprintf(c,"%d",b);
		result.append((string)c+" ");
	}
}

/*
* ** FUNCTION
* void goMainScene()							go to MainScene
* Input											nothing
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											Pineoc
*/
void gameScene::goMainScene()
{
	this->onExit();
	CCScene *pScene = mainScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
void gameScene::goRegame(int stage)
{
	CCScene *pScene = gameScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
}
/*
* ** FUNCTION
* void doPop(CCObject*)							pop the pause scene
* Input											????
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::doPop(CCObject* pSender)
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);		//set touch enable
	CCUserDefault::sharedUserDefault()->setIntegerForKey("curStage",gStageidx);
	CCScene* pScene=PauseGameScene::scene();
	this->addChild(pScene,2000,2000);

}
/*
* ** FUNCTION
* void doNotification(CCObject *)				get notification		????
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::doNotification(CCObject *obj)
{
	//노티피케이션 받기
	CCString *pParam=(CCString*)obj;
	int flag = pParam->intValue();
	if(flag==1)
	{
		CCDirector::sharedDirector()->resume();														//화면 재시작
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);		// set touch able
	}
	else if(flag==2)
	{
		CCDirector::sharedDirector()->resume();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		this->goMainScene();
	}
	else if(flag>=10 && flag<=48)
	{
		CCDirector::sharedDirector()->resume();
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
		this->goRegame(flag);
	}
	else
	{	
		CCArray* childs = this->getChildren();
		CCDirector::sharedDirector()->pause();													//화면 정지
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(PauseMenu);			//메뉴버튼 비활성
	}

}

void gameScene::onExit()
{
	CCLayer::onExit();
	CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, "notification");
}

/*
* ** FUNCTION
* void createItem1()							create item 1
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem1()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("item1.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item1 = item;
	this->addChild(item1);
}

/*
* ** FUNCTION
* void createItem2()							create item 2
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem2()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("item2.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item2 = item;
	this->addChild(item2);
}

/*
* ** FUNCTION
* void createItem3()							create item 3
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem3()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("item3.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item3 = item;
	this->addChild(item3);
}

/*
* ** FUNCTION
* void createItem4()							create item 4
* Input											nothing
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
void gameScene::createItem4()
{
	CCTexture2D *itemTexture = CCTextureCache::sharedTextureCache()->addImage("item4.png");

	CCSprite* item = CCSprite::createWithTexture(itemTexture,CCRectMake(0, 0, 60, 60));
	item->setPosition(itemPosition);
	item->setAnchorPoint(ccp(0,0));
	item4 = item;
	this->addChild(item4);
}
/*
* ** FUNCTION
* void check_item(float dt)						check if character eat item or not.
* Input											float for schedule
* Output										scene
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											jiyoon
*/
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
		//item effect - gauge up 10%
		character_XP += 10;

		CCActionInterval* gaugeUp = CCMoveBy::create(1,ccp(44.1,0));
		//move by current position. +44.1(10% of the bar)
		gaugeHeart->runAction(gaugeUp);
		this->removeChild(item1);
		item1=NULL;
	}
	if(characterRect.intersectsRect(item2Rect))
	{
		//slow down effect
		movingSpeed = 0.65;
		this->removeChild(item2);
		item2=NULL;
	}
	if(characterRect.intersectsRect(item3Rect))
	{
		//pause obstacle effect
		isPause = true;	//정지 활성화
		count = 0;	//초세기 초기화
		this->removeChild(item3);
		item3=NULL;
	}
	if(characterRect.intersectsRect(item4Rect))
	{
		//superwoman effect
		isSuper = true;	//무적 활성화
		count = 0;	//초세기 초기화
		this->schedule(schedule_selector(gameScene::countTime),1.0f);	//초세기 시작
		this->doParticle();
		this->removeChild(item4);
		item4=NULL;
	}
}

/*
* ** FUNCTION
* void doParticle
* Input											nothing
* Output										nothing
* Date											2013. 11. 24
* Latest										2013. 11. 24
* Made											jiyun
*/
void gameScene::doParticle()
{
	CCParticleSystem* super = CCParticleFire::create();	//explosion particle
	super->retain();
	super->setTexture(CCTextureCache::sharedTextureCache()->addImage("fire.png"));

	if(super != NULL)
	{
		//get current position of heart
		float X = gaugeHeart->getPositionX();
		float Y = gaugeHeart->getPositionY();
		
		super->setScale(1.0);	//scale
		super->setDuration(5.0);	//5sec
		super->setPosition(X,Y);	//heart
		this->addChild(super);
	}
}

/*
* ** FUNCTION
* void stopObstacle
* Input											nothing
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											jiyun
*/
void gameScene::stopObstacle()
{
	CCDirector::sharedDirector()->getScheduler()->pauseTarget(obstacle);
	this->schedule(schedule_selector(gameScene::countTime),1.0f);
}

/*
* ** FUNCTION
* void countTime
* Input											nothing
* Output										nothing
* Date											2013. 11. 22
* Latest										2013. 11. 22
* Made											jiyun
*/
void gameScene::countTime(float d)
{
	if(count == 5)
	{
		if(isPause == true)
		{	resumeObstacle();	}
		if(isSuper == true)
		{  isSuper = false;	}
	}
	else
	{	count++;	}
}


/*
* ** FUNCTION
* void resumObstacle
* Input											nothing
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											jiyun
*/
void gameScene::resumeObstacle()
{
	isPause = false;
	CCDirector::sharedDirector()->getScheduler()->resumeTarget(obstacle);
}

//--------------jiyoon end-----------------------------------------

//------------- eunji move obstacle -------------------------//
/*
* ** FUNCTION
* void moveObstacle(float dt)					make moving obstacle move
* Input											float for schedule
* Output										nothing
* Date											2013. 10. 04
* Latest										2013. 10. 04
* Made											eunji
* Add											jiyun

*/
void gameScene::moveObstacleWidth(float dt)
{
	if(!isPause)
	{
		checkObDirection = !(checkObDirection);

		CCActionInterval* moveRight = CCMoveBy::create(1, ccp(60, 0));
		CCActionInterval* moveLeft = CCMoveBy::create(1, ccp(-60, 0));

		if     (checkObDirection == true)  {	obstacle->runAction(moveRight);}
		else if(checkObDirection == false) {	obstacle->runAction(moveLeft); }
	}

	else
	{
		stopObstacle();
	}
}

void gameScene::moveObstacleHeight(float dt)
{
	if(!isPause)
	{
		checkObDirection = !(checkObDirection);

		CCActionInterval* moveRight = CCMoveBy::create(1, ccp(0, 60));
		CCActionInterval* moveLeft = CCMoveBy::create(1, ccp(0, -60));

		if     (checkObDirection == true)  {	obstacle->runAction(moveRight);}
		else if(checkObDirection == false) {	obstacle->runAction(moveLeft); }
	}

	else
	{
		stopObstacle();
	}
}
/*
* ** FUNCTION
* void doActionMovingObstacleRight(CCObject*)	Make moving obstacle go to right side
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/

void gameScene::doActionMovingObstacleRight(CCObject* pSender)
{
	CCActionInterval* moveRight = CCMoveBy::create(2, ccp(200, 0));

	obstacle->runAction(moveRight);

}
/*
* ** FUNCTION
* void doActionMovingObstacleLeft(CCObject*)	Make moving obstacle go to left side
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/
void gameScene::doActionMovingObstacleLeft(CCObject* pSender)
{
	CCActionInterval* moveLeft = CCMoveBy::create(2, ccp(-80, 0));

	obstacle->runAction(moveLeft);
}
/*
* ** FUNCTION
* void doActionMovingObstaclReverse(CCObject*)	Make moving obstacle do action reversely
* Input											???
* Output										nothing
* Date											2013. 10. 03
* Latest										2013. 10. 03
* Made											eunji
*/
void gameScene::doActionMovingObstacleReverse(CCObject* pSender)
{
	CCActionInterval* moveRight = CCMoveBy::create(2, ccp(80, 0));
	CCActionInterval* moveReverse = moveRight->reverse();

	obstacle->runAction(moveReverse);
}

/*
* ** FUNCTION
* void doActionMovingObstaclReverse(CCObject*)	Dcrease Gauge bar 
* Input											int num
* Output										nothing
* Date											2013. 10. 05
* Latest										2013. 10. 05
* Made											eunji
*/

void gameScene::decreaseGaugeBar(int num)
{
	//x = 20 은 초기상태(에너지가 0인 상태)
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if( character_XP > 0 )
	{
		gaugeHeart->setPositionX(size.width - (20 + num));		// num 값 만큼 감소시킴.	
	}

	else
	{
		//게임을 끝낸다
		gaugeHeart->setPositionX(20);
		this->go_endResultScene(0);
	}
}

/*
* ** FUNCTION
* void doActionMovingObstaclReverse(CCObject*)	Increase Gauge bar 
* Input											int num
* Output										nothing
* Date											2013. 10. 05
* Latest										2013. 10. 05
* Made											eunji
*/

void gameScene::increaseGaugeBar(int num)
{
	//x = 20 은 초기상태(에너지가 0인 상태)
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	if( character_XP < (460 - num) )
	{
		gaugeHeart->setPositionX(size.width - (20 - num));		// num 값 만큼 증가시킴.	
	}

	else
	{
		//게임을 끝낸다
		gaugeHeart->setPositionX(460);
		this->go_endResultScene(0);
	}
}

