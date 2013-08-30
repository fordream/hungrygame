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

		// �� ���� �ҷ�����

		tileMap = CCTMXTiledMap::create("map/GameMap.tmx");
		tileMap->setPosition(size.width * 0.05, size.height * 0.35);
	//	this->addChild(tileMap,1,2);

		// �� Ÿ�� �ҷ�����
		
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





		// ���� ĭ�� ���� ���� ����
		int mapWidth = size.width * 0.12;

		// ĳ���Ͱ� �̵��� ������ ���� �� �� ��ǥ
		int map0x = size.width * 0.05 + mapWidth / 2;
		int map0y = size.height * 0.6 + mapWidth /2;

		// ������ �ʱ�ȭ
		int blockCnt = 4;		// ��ֹ��� ���� ����

		// ��ֹ� ���� -> 11�� (1,1)�ڸ�, 34 �� (3,4)�ڸ���� �����ϸ��
		int blockList[] = {11,12,34,35};
		
		for(int i = 0 ; i < blockCnt; i++)
		{
			int blockX = map0x + mapWidth * (blockList[i]/10);
			int blockY = map0y + mapWidth * (blockList[i]%10);

			// blockX�� blockY�� �ش� ��ֹ��� x y ��ǥ��

			// ���⼭ ��ֹ� ����� �ɵ�!
		}









        bRet = true;
    } while (0);

    return bRet;
}

