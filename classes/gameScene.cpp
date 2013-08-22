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



			//��� �̹��� ����
		CCSprite* pStageBg = CCSprite::create("img\\game\\game_bg.png");
        CC_BREAK_IF(! pStageBg);

        // Place the sprite on the center of the screen
        pStageBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pStageBg, 0);



		// �ش� �������� ��ȣ�� �Է¹��� (0�� stage 1�μ�)
		// �ϴ��� 0 (�� stage 1�� �� -> ���߿� �������� ��ȣ �޾ƿ��°ŷ� ��ġ��!)
		int stageNum = 0;		

		// ���� ĭ�� ���� ���� ����
		int mapWidth = size.width * 0.12;

		// ĳ���Ͱ� �̵��� ������ ���� �� �� ��ǥ
		int map0x = size.width * 0.05 + mapWidth / 2;
		int map0y = size.height * 0.6 + mapWidth /2;

		// ������ �ʱ�ȭ
		int blockCnt = 4;		// ��ֹ��� ���� ����

		// ������ֹ� ���� -> 11�� (1,1)�ڸ�, 34 �� (3,4)�ڸ���� �����ϸ��
		// -1�� �ش� ����Ʈ�� ����Ǿ����� ��Ÿ���� ��
		int blockList[][] = {{11,12,34,35,-1}};
		

		


		// ĳ���� ����
		// ĳ���ʹ� ���� �ϳ����̴ϱ� �׳� ������������ �޴°� ����..
		int characterList[] ={12,23};

		int characterX = map0x + mapWidth * (characterList[stageNum]/10);
		int characterY = map0y + mapWidth * (characterList[stageNum]%10);

		// ���⼭ ĳ���͸� �����ϸ� �ɵ�!



        bRet = true;
    } while (0);

    return bRet;
}

