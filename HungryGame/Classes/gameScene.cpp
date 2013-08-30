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

		
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		/*
		* make background scene
		* Joung Daun
		* http://blog.naver.com/PostView.nhn?blogId=skmzzang7979&logNo=70142661460
		*/
		CCLayer *tileLayer = CCLayer::create();
		this->addChild(tileLayer);

		
		CCTMXTiledMap *tileMap;
		CCTMXLayer *backgroundLayer;
		CCTMXObjectGroup *objectgroup;

		// 맵 파일 불러오기

		tileMap = CCTMXTiledMap::create("map/GameMap.tmx");
		tileMap->setPosition(size.width * 0.05, size.height * 0.35);
	//	this->addChild(tileMap,1,2);

		// 맵 타일 불러오기
		
		backgroundLayer = tileMap->layerNamed("wall");
//		CCAssert(backgroundLayer != NULL, "backgroundLayer not found");
		tileLayer->addChild(tileMap);

		/* pineoc's comments
		in example,
		CCMTXObjectGroup *objectgroup = tileMap->objectGroupNamed("objects");
		//it can change object generally like objects..
		//in object, can contain spawnArea, wall, so on..
		*/
		CCSize s = tileMap->getContentSize();










        bRet = true;
    } while (0);

    return bRet;
}

