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

		// �� ���� �ҷ�����

		tileMap = CCTMXTiledMap::create("map/GameMap.tmx");
	
		//	tileMap->setPosition(size.width * 0.05, size.height * 0.35);
		// -> ���� ���� �� ��ġ �̵���Ű�°���! �ϴ��� 0,0���� �δ°� ���ڴ�!
		//	this->addChild(tileMap,1,2);

		// �� Ÿ�� �ҷ�����
		
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
{// ��ֹ� ���� ����

	CCTexture2D *obTexture = CCTextureCache::sharedTextureCache()->addImage("map/meat.png");

	obstacle = CCSprite::createWithTexture(obTexture,CCRectMake(0, 0, 48, 48)); // �ʿ� ���� ���� �ٲ����
	obstacle->setPosition(obstaclePosition);
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
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
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
    CCPoint touchLocation = pTouch->getLocation();
    touchLocation = this->convertToNodeSpace(touchLocation);


    CCPoint playerPos = character->getPosition();

    CCPoint diff = ccpSub(touchLocation, playerPos);

    if (abs(diff.x) > abs(diff.y)) {
        if (diff.x > 0) {
            playerPos.x += tileMap->getTileSize().width;
            
            // ĳ������ ������ �ٲپ��ش�.
            character->setFlipX(true);
        } else {
            playerPos.x -= tileMap->getTileSize().width;
            
            // ĳ������ ������ �ٲپ��ش�.
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
        // ĳ������ ���ο� ��ġ ����
        character->setPosition( playerPos );
    }
    

}

void gameScene::createCharacter()
{

	CCSize size = CCDirector::sharedDirector()->getWinSize();


	// Ÿ�ϸʿ��� Object��� ������ ������Ʈ ��ü�� ��������
	CCTMXObjectGroup *object = tileMap->objectGroupNamed("object");
	// �Ӽ��� �о���� (characterPosition)
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
	CCTexture2D *foodTexture = CCTextureCache::sharedTextureCache()->addImage(foodImageName);

	CCSprite* food = CCSprite::createWithTexture(foodTexture,CCRectMake(0, 0, 48, 48)); // �ʿ� ���� ���� �ٲ����
	food->setPosition(foodpoint);
	food->setAnchorPoint(ccp(0,0));
	this->addChild(food);
}


//-----------------------pineoc End-------------------------------//