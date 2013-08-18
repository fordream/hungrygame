//pineoc@naver.com
//HelpScene.cpp
//도움말창 구현

#include "HelpScene.h"

//HelpScene::HelpScene(std::string _helpType)
//{
//	helpType = _helpType;
//}

CCScene* HelpScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		HelpScene *layer = HelpScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool HelpScene::init()
{
	bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(255, 255, 255, 100)));

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		/*
		기존 배경화면 설정
		*/
		CCSprite* phelpMainScene = CCSprite::create("helpScene_bg.png");
        CC_BREAK_IF(! phelpMainScene);
		phelpMainScene->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(phelpMainScene,0);

		/*
		Go to Scene before helpScene
		도움말 화면 전으로 돌아가는 버튼
		*/
		CCMenuItemImage *pCloseHelpScene = CCMenuItemImage::create(
            "btn_goBack.png",
            "btn_goBack_n.png",
            this,
			menu_selector(HelpScene::menu_closeHelpScene));
        CC_BREAK_IF(! pCloseHelpScene);

        // Place the menu item bottom-right conner.
		pCloseHelpScene->setPosition(ccp(size.width / 1.25 , size.height /14.28 ));
		
		CCMenu* pCloseHelpMenu = CCMenu::create(pCloseHelpScene,NULL);
		pCloseHelpMenu->setPosition(CCPointZero);
		this->addChild(pCloseHelpMenu,1);

        bRet = true;
    } while (0);

	return true;
}

void HelpScene::menu_closeHelpScene(CCObject* pSender)
{ // 도움말창을 닫음
	CCDirector::sharedDirector()->popScene();
	//push, pop Scene을 이용해서 되돌아가기 구현.
}