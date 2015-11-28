/*
* 2013 08 27
* option scene
* Daun
*/

#include "OptionScene.h"


enum musicOnOffList{ bgOn, bgOff, effectOn, effectOff};
CCScene* OptionScene::scene()
{
	CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
		OptionScene *layer = OptionScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

bool OptionScene::init()
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
		background img
		*/
		CCSprite* phelpMainScene = CCSprite::create("img\\option\\option_bg.png");
        CC_BREAK_IF(! phelpMainScene);
		phelpMainScene->setPosition(ccp(size.width/2,size.height/2));
		this->addChild(phelpMainScene,0);


		/*
		* Add Buttons
		*/

		CCMenuItemImage *pBGON = CCMenuItemImage::create(
			"img\\option\\option_btn_on.png",
			"img\\option\\option_btn_on_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));
		CC_BREAK_IF(!pBGON);

		pBGON->setPosition(ccp(size.width * 0.6, size.height * 0.6));
		pBGON->setTag(bgOn);

		CCMenuItemImage *pBGOFF = CCMenuItemImage::create(
			"img\\option\\option_btn_off.png",
			"img\\option\\option_btn_off_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));
		CC_BREAK_IF(!pBGOFF);

		pBGOFF->setPosition(ccp(size.width * 0.8, size.height * 0.6));
		pBGOFF->setTag(bgOff);



		CCMenuItemImage *pEffectOn = CCMenuItemImage::create(
			"img\\option\\option_btn_on.png",
			"img\\option\\option_btn_on_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));
		CC_BREAK_IF(!pEffectOn);

		pEffectOn->setPosition(ccp(size.width * 0.6, size.height * 0.4));
		pEffectOn->setTag(effectOn);

		CCMenuItemImage *pEffectOff = CCMenuItemImage::create(
			"img\\option\\option_btn_off.png",
			"img\\option\\option_btn_off_n.png",
			this,
			menu_selector(OptionScene::OnOffMenu));
		CC_BREAK_IF(!pEffectOff);

		pEffectOff->setPosition(ccp(size.width * 0.8, size.height * 0.4));
		pEffectOff->setTag(effectOff);


		CCMenu *pONOFFMenu = CCMenu::create(pBGON, pBGOFF, pEffectOn, pEffectOff,NULL);
		pONOFFMenu->setPosition(CCPointZero);
		this->addChild(pONOFFMenu,1);

		/*
		Goback btn
		*/
		CCMenuItemImage *pCloseScene = CCMenuItemImage::create(
            "btn_goBack.png",
            "btn_goBack_n.png",
            this,
			menu_selector(OptionScene::goBackMenu));
        CC_BREAK_IF(! pCloseScene);

        // Place the menu item bottom-right conner.
		pCloseScene->setPosition(ccp(size.width / 1.25 , size.height /14.28 ));
		
		CCMenu* pCloseMenu = CCMenu::create(pCloseScene,NULL);
		pCloseMenu->setPosition(CCPointZero);
		this->addChild(pCloseMenu,1);

        bRet = true;
    } while (0);

	return true;
}

void OptionScene::goBackMenu(CCObject* pSender)
{ // 도움말창을 닫음
	CCScene *pScene = mainScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	
}

void OptionScene::OnOffMenu(CCObject* pSender)
{
	// set fuction to on off buttons
	CCMenuItem *pGet = (CCMenuItem *)pSender;
	music m;
	switch(pGet->getTag())
	{
	case bgOn:
		userData::sharedInstance()->setBGM(true);
		m.bgStart("temp");
		break;
	case bgOff:
		userData::sharedInstance()->setBGM(false);
		m.bgStop();
		break;
	case effectOn:
		userData::sharedInstance()->setEFFECT(true);
		break;
	case effectOff:
		userData::sharedInstance()->setEFFECT(false);
		break;
	}

}