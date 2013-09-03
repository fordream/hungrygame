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

using namespace cocos2d;

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
		foods = new CCArray; // in food array dinamic cast
		
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
		CCTMXLayer *backgroundLayer;
		CCTMXObjectGroup *objectgroup;

		// 맵 파일 불러오기

		tileMap = CCTMXTiledMap::create("map/GameMap.tmx");
	
		//	tileMap->setPosition(size.width * 0.05, size.height * 0.35);
		// -> 위에 줄이 맵 위치 이동시키는거임! 일단은 0,0으로 두는게 좋겠다!
		//	this->addChild(tileMap,1,2);

		// 맵 타일 불러오기
		
		backgroundLayer = tileMap->layerNamed("wall");
//		CCAssert(backgroundLayer != NULL, "backgroundLayer not found");
		tileLayer->addChild(tileMap);


		/*
		* make character
		* Daun..
		*/
		createCharacter();
		//------------------------- Daun End -------------------------------//




		/* pineoc's comments
		in example,
		CCMTXObjectGroup *objectgroup = tileMap->objectGroupNamed("objects");
		it can change object generally like objects..
		in object, can contain spawnArea, wall, so on..
		use example
		links : http://www.raywenderlich.com/40544/cocos2d-x-tile-map-tutorial-part-2
		*/
		CCSize s = tileMap->getContentSize();

		/*
		pineoc's food testing part --------------------------------------------------------------
		*/

		CCTMXObjectGroup *objects = tileMap->objectGroupNamed("foods");
		CCDictionary *food1point = objects->objectNamed("food1");
		//in this time, CCDictionary has debug error, but if ignore it twice -> food will appear

		int foodX = ((CCString*)food1point->objectForKey("x"))->intValue();
		int foodY = ((CCString*)food1point->objectForKey("y"))->intValue();
		
		this->createFood(ccp(foodX,foodY),"map/p.jpg");
		//----------------------------------------------------------------------------------------


		//-------------- obstacle (eunji) --------------------

		CCTMXObjectGroup *obstacle = tileMap->objectGroupNamed("obstacle");
		CCDictionary *obstaclePoint = obstacle->objectNamed("obstaclePoint");

		int obX = ((CCString*)obstaclePoint->objectForKey("x"))->intValue();
		int obY = ((CCString*)obstaclePoint->objectForKey("y"))->intValue();

		obstaclePosition = ccp(obX, obY);
		this->createObstacle();

		


		//----------------------------------------------------
		

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


    CCPoint playerPos = character->getPosition();

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
	this->addChild(food);
}


//-----------------------pineoc End-------------------------------//