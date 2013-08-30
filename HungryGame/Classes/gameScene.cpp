/*
* 2013 08 18
* Joung Daun
* Stage Select
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
		
//		backgroundLayer = tileMap->layerNamed("wall");
//		CCAssert(backgroundLayer != NULL, "backgroundLayer not found");
		tileLayer->addChild(tileMap);

		/* pineoc's comments
		in example,
		CCMTXObjectGroup *objectgroup = tileMap->objectGroupNamed("objects");
		//it can change object generally like objects..
		//in object, can contain spawnArea, wall, so on..
		*/
		CCSize s = tileMap->getContentSize();





		// 맵의 칸들 사이 간격 지정
		int mapWidth = size.width * 0.12;

		// 캐릭터가 이동할 공간의 왼쪽 맨 위 좌표
		int map0x = size.width * 0.05 + mapWidth / 2;
		int map0y = size.height * 0.6 + mapWidth /2;

		// 데이터 초기화
		int blockCnt = 4;		// 장애물의 갯수 지정

		// 장애물 생성 -> 11은 (1,1)자리, 34 는 (3,4)자리라고 생각하면됨
		int blockList[] = {11,12,34,35};
		
		for(int i = 0 ; i < blockCnt; i++)
		{
			int blockX = map0x + mapWidth * (blockList[i]/10);
			int blockY = map0y + mapWidth * (blockList[i]%10);

			// blockX와 blockY는 해당 장애물의 x y 좌표임

			// 여기서 장애물 만들면 될듯!
		}









        bRet = true;
    } while (0);

    return bRet;
}

