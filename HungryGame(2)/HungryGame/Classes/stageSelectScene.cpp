/*
* 2013 08 18
* Joung Daun
* Stage Select
*/
#include "stageSelectScene.h"
#include "music.h"
#include "HelloWorldScene.h"
#include "mainScene.h"
#include "BuildingScene.h"

using namespace cocos2d;

CCScene* stageSelect::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		stageSelect *layer = stageSelect::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool stageSelect::init()
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
		CCSprite* pStageBg = CCSprite::create("stage_bg.png");
        CC_BREAK_IF(! pStageBg);

        // Place the sprite on the center of the screen
        pStageBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pStageBg, 0);

		CCMenuItemImage *s1 = CCMenuItemImage::create(
			"stage_btn_1.png","stage_btn_1_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s1);

		s1->setPosition(ccp(size.width, size.height));


		CCMenu *stageMenu = CCMenu::create(s1,NULL);
		stageMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!stageMenu);


        bRet = true;
    } while (0);

    return bRet;
}
