#include "mainScene.h"
#include "music.h"
#include "HelpScene.h"
#include "BuildingScene.h"
#include "MakerInfoScene.h"
#include "optionScene.h"

using namespace cocos2d;

CCScene* mainScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		mainScene *layer = mainScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool mainScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(255, 255, 255, 100)));

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		//화면 전체 크기
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		music mu;
		mu.bgStart("background.mp3");
        // 1. Add a menu item with "X" image, which is clicked to quit the program.

		// 메인화면 배경 이미지 생성
		CCSprite *pMainBg = CCSprite::create("main_bg.png");

		pMainBg->setPosition(ccp(size.width/2, size.height/2));

		this->addChild(pMainBg, 1);


        // 게임종료 버튼
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "main_btn_endgame.png",
            "main_btn_endgame_n.png",
            this,
			menu_selector(mainScene::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(size.width / 2 , size.height / 14.2));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 2);



		//개발자 버튼

		CCMenuItemImage *pDevItem = CCMenuItemImage::create(
            "main_btn_info.png",
            "main_btn_info_n.png",
            this,
			menu_selector(mainScene::menuDevCallback));
        CC_BREAK_IF(! pDevItem);

        // Place the menu item bottom-right conner.
		pDevItem->setPosition(ccp(size.width /2 , size.height /5.26 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pDevMenu = CCMenu::create(pDevItem, NULL);
        pDevMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pDevMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pDevMenu, 2);



		//옵션 버튼

		CCMenuItemImage *pOptionItem = CCMenuItemImage::create(
            "main_btn_option.png",
            "main_btn_option_c.png",
            this,
			menu_selector(mainScene::menuOptionCallback));
        CC_BREAK_IF(! pOptionItem);

        // Place the menu item bottom-right conner.
		pOptionItem->setPosition(ccp(size.width /2 , size.height /2.32 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pOptionMenu = CCMenu::create(pOptionItem, NULL);
        pOptionMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pOptionMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pOptionMenu, 2);

		
		
		//도움말 버튼

		CCMenuItemImage *pHelpItem = CCMenuItemImage::create(
            "main_btn_help.png",
            "main_btn_help_n.png",
            this,
			menu_selector(mainScene::menuHelpCallback));
        CC_BREAK_IF(! pHelpItem);

        // Place the menu item bottom-right conner.
		pHelpItem->setPosition(ccp(size.width / 2 , size.height /3.22 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pHelpMenu = CCMenu::create(pHelpItem, NULL);
        pHelpMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pHelpMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pHelpMenu, 2);




		//게임시작 버튼

		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
            "main_btn_gamestart.png",
            "main_btn_gamestart_c.png",
            this,
			menu_selector(mainScene::menuStartCallback));
        CC_BREAK_IF(! pStartItem);

        // Place the menu item bottom-right conner.
		pStartItem->setPosition(ccp(size.width /2 , size.height /1.81 ));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pStartMenu = CCMenu::create(pStartItem, NULL);
        pStartMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pStartMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pStartMenu, 2);


        bRet = true;
    } while (0);

    return bRet;
}

void mainScene::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
	music m;
	m.effectStart("sound\\effect_btn_click.mp3");
    CCDirector::sharedDirector()->end();
}

void mainScene::menuOptionCallback(CCObject* pSender)
{
	music m;
	m.effectStart("sound\\effect_btn_click.mp3");
	CCScene *pScene = OptionScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
}

void mainScene::menuHelpCallback(CCObject* pSender)
{// pineoc's help 구현. HelpScene클래스 사용.
	music m;
	m.effectStart("sound\\effect_btn_click.mp3");
	CCScene *pScene = HelpScene::scene();

	CCDirector::sharedDirector()->pushScene(pScene);

	/*
	CCScene* pScene = CCScene::create();
	HelpScene *pLayer = new HelpScene("main");
	pLayer->autorelease();
	pScene->addChild(pLayer);
	CCDirector::sharedDirector()->pushScene(pScene);
	*/
	
}

void mainScene::menuStartCallback(CCObject* pSender)
{
	music m;
	m.effectStart("sound\\effect_btn_click.mp3");
	CCScene *pScene = BuildingScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
}

void mainScene::menuDevCallback(CCObject* pSender)
{
	music m;
	m.effectStart("sound\\effect_btn_click.mp3");
	CCScene *pScene = MakerInfoScene::scene();

	CCDirector::sharedDirector()->pushScene(pScene);
}