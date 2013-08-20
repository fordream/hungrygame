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



			//배경 이미지 생성
		CCSprite* pStageBg = CCSprite::create("img\\game\\game_bg.png");
        CC_BREAK_IF(! pStageBg);

        // Place the sprite on the center of the screen
        pStageBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pStageBg, 0);



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

