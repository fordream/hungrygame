/*
* 2013 08 18
* Joung Daun
* Stage Select
*/
#include "stageSelectScene.h"
#include "music.h"
#include "mainScene.h"
#include "BuildingScene.h"
#include "stageSelectScene.h"
#include "gameScene.h"

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
		CCSprite* pStageBg = CCSprite::create("img\\stageSelect\\stage_bg.png");
        CC_BREAK_IF(! pStageBg);

        // Place the sprite on the center of the screen
        pStageBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pStageBg, 0);




		// 버튼 생성
		CCMenuItemImage *s1 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_1.png","img\\stageSelect\\stage_btn_1_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s1);

		s1->setPosition(ccp(size.width * 0.2, size.height * 0.8));
		s1->setTag(1);
		
		CCMenuItemImage *s2 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_2.png","img\\stageSelect\\stage_btn_2_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s2);

		s2->setPosition(ccp(size.width * 0.5, size.height * 0.8));
		s2->setTag(2);

		CCMenuItemImage *s3 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_3.png","img\\stageSelect\\stage_btn_3_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s3);

		s3->setPosition(ccp(size.width * 0.8, size.height * 0.8));
		s3->setTag(3);

		CCMenuItemImage *s4 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_4.png","img\\stageSelect\\stage_btn_4_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s4);

		s4->setPosition(ccp(size.width * 0.2, size.height * 0.62));
		s4->setTag(4);

		CCMenuItemImage *s5 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_5.png","img\\stageSelect\\stage_btn_5_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s5);

		s5->setPosition(ccp(size.width * 0.5, size.height * 0.62));
		s5->setTag(5);

		CCMenuItemImage *s6 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_6.png","img\\stageSelect\\stage_btn_6_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s6);

		s6->setPosition(ccp(size.width * 0.8, size.height * 0.62));
		s6->setTag(6);

		CCMenuItemImage *s7 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_7.png","img\\stageSelect\\stage_btn_7_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s7);

		s7->setPosition(ccp(size.width * 0.2, size.height * 0.45));
		s7->setTag(7);

		CCMenuItemImage *s8 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_8.png","img\\stageSelect\\stage_btn_8_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s8);

		s8->setPosition(ccp(size.width * 0.5, size.height * 0.45));
		s8->setTag(8);

		CCMenuItemImage *s9 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_9.png","img\\stageSelect\\stage_btn_9_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s9);

		s9->setPosition(ccp(size.width * 0.8, size.height * 0.45));
		s9->setTag(9);

		CCMenuItemImage *s10 = CCMenuItemImage::create(
			"img\\stageSelect\\stage_btn_bonus.png","img\\stageSelect\\stage_btn_bonus_n.png",this,menu_selector(stageSelect::stageMenu));
		CC_BREAK_IF(!s10);

		s10->setPosition(ccp(size.width * 0.5, size.height * 0.25));
		s10->setTag(10);


		CCMenu *stageMenu = CCMenu::create(s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,NULL);
		stageMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!stageMenu);

		this->addChild(stageMenu,1);


		//되돌아가기 버튼
        CCMenuItemImage *pGoBack = CCMenuItemImage::create(
            "btn_goBack.png",
            "btn_goBack_n.png",
            this,
			menu_selector(stageSelect::menuGoBackCallback));
        CC_BREAK_IF(! pGoBack);

        // Place the menu item bottom-right conner.
		pGoBack->setPosition(ccp(size.width/1.25, size.height/14.28));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pGoBackMenu = CCMenu::create(pGoBack, NULL);
        pGoBackMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pGoBackMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pGoBackMenu, 1);




        bRet = true;
    } while (0);

    return bRet;
}


void stageSelect::stageMenu(CCObject* pSender)
{
	music m;
	m.effectStart("sound\\effect_btn_click.mp3");
	/***
	 여기에 게임 화면으로 전환하는거 들어감!!
	****/
	CCMenuItem *pGet = (CCMenuItem *)pSender;

	CCScene *pScene = gameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	/*

	switch(pGet->getTag())
	{
	case 1:
		
//		break;
	case 2:
//		break;
	case 3:
//		break;
	case 4:
//		break;
	case 5:
//		break;
	case 6:
//		break;
	case 7:
//		break;
	case 8:
//		break;
	case 9:
//		break;
	case 10:

		break;
	}
	*/
}

//되돌아가기
void stageSelect::menuGoBackCallback(CCObject* pSender)
{
	CCScene *pScene = Building::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

