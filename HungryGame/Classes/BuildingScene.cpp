/*
	빌딩선택창
*/

#include "BuildingScene.h"
#include "music.h"
#include "HelloWorldScene.h"
#include "mainScene.h"
#include "stageSelectScene.h"

using namespace cocos2d;

CCScene* Building::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		Building *layer = Building::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Building::init()
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
		CCSprite* pBuildingBg = CCSprite::create("buildingSelect_bg.png");
        CC_BREAK_IF(! pBuildingBg);

        // Place the sprite on the center of the screen
        pBuildingBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pBuildingBg, 0);


		//첫번째 건물버튼
        CCMenuItemImage *pBuilding_1 = CCMenuItemImage::create(
            "buildingSelect_btn_b1.png",
            "buildingSelect_btn_b1_n.png",
            this,
			menu_selector(Building::menuBuild1Callback));
        CC_BREAK_IF(! pBuilding_1);

        // Place the menu item bottom-right conner.
		pBuilding_1->setPosition(ccp(size.width/3.33, size.height/1.53));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu1 = CCMenu::create(pBuilding_1, NULL);
        pMenu1->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu1);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu1, 1);


		//두번째 건물버튼
        CCMenuItemImage *pBuilding_2 = CCMenuItemImage::create(
            "buildingSelect_btn_b2.png",
            "buildingSelect_btn_b2_n.png",
            this,
			menu_selector(Building::menuBuild2Callback));
        CC_BREAK_IF(! pBuilding_2);

        // Place the menu item bottom-right conner.
		pBuilding_2->setPosition(ccp(size.width/1.42, size.height/1.53));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu2 = CCMenu::create(pBuilding_2, NULL);
        pMenu2->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu2);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu2, 1);


		//세번째 건물버튼
        CCMenuItemImage *pBuilding_3 = CCMenuItemImage::create(
            "buildingSelect_btn_b3.png",
            "buildingSelect_btn_b3_n.png",
            this,
			menu_selector(Building::menuBuild3Callback));
        CC_BREAK_IF(! pBuilding_3);

        // Place the menu item bottom-right conner.
		pBuilding_3->setPosition(ccp(size.width/3.33, size.height/3.33));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu3 = CCMenu::create(pBuilding_3, NULL);
        pMenu3->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu3);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu3, 1);


		//네번째 건물버튼
        CCMenuItemImage *pBuilding_4 = CCMenuItemImage::create(
            "buildingSelect_btn_b4.png",
            "buildingSelect_btn_b4_n.png",
            this,
			menu_selector(Building::menuBuild4Callback));
        CC_BREAK_IF(! pBuilding_4);

        // Place the menu item bottom-right conner.
		pBuilding_4->setPosition(ccp(size.width/1.42, size.height/3.33));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu4 = CCMenu::create(pBuilding_4, NULL);
        pMenu4->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu4);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu4, 1);


		//되돌아가기 버튼
        CCMenuItemImage *pGoBack = CCMenuItemImage::create(
            "btn_goBack.png",
            "btn_goBack_n.png",
            this,
			menu_selector(Building::menuGoBackCallback));
        CC_BREAK_IF(! pGoBack);

        // Place the menu item bottom-right conner.
		pGoBack->setPosition(ccp(size.width/1.25, size.height/14.28));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu5 = CCMenu::create(pGoBack, NULL);
        pMenu5->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu5);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu5, 1);


        bRet = true;
    } while (0);

    return bRet;
}

// 첫번째 빌딩
void Building::menuBuild1Callback(CCObject* pSender)
{
	CCScene *pScene = stageSelect::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

//두번째 빌딩
void Building::menuBuild2Callback(CCObject* pSender)
{
	CCScene *pScene = stageSelect::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

//세번째 빌딩
void Building::menuBuild3Callback(CCObject* pSender)
{
	CCScene *pScene = stageSelect::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

//네번째 빌딩
void Building::menuBuild4Callback(CCObject* pSender)
{
	CCScene *pScene = stageSelect::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

//되돌아가기
void Building::menuGoBackCallback(CCObject* pSender)
{
	CCScene *pScene = Main::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

