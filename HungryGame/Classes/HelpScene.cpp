//pineoc@naver.com
//HelpScene.cpp
//µµ¿ò¸»Ã¢ ±¸Çö

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
		±âÁ¸ ¹è°æÈ­¸é ¼³Á¤
		*/
		CCSprite* phelpMainScene = CCSprite::create("help01.png");
        CC_BREAK_IF(! phelpMainScene);

		//phelpMainScene->setScale(0.85);
		phelpMainScene->setPosition(ccp(240, 1200));

		CCSprite* phelpMainScene2 = CCSprite::create("help02.png");
        CC_BREAK_IF(! phelpMainScene2);

		//phelpMainScene2->setScale(0.85);
		phelpMainScene2->setPosition(ccp(240, 400));

		CCLayerColor *layer = CCLayerColor::create(ccc4(255, 255, 255, 255));
		layer->setAnchorPoint(CCPointZero);
		layer->setPosition(ccp(0, 0));
		layer->setContentSize(CCSizeMake(480, 1600));

		layer->addChild(phelpMainScene);
		layer->addChild(phelpMainScene2);

		scrollView = CCScrollView::create();
		scrollView->retain();
		scrollView->setDirection(kCCScrollViewDirectionVertical);
		scrollView->setViewSize(CCSizeMake(480, 1600));
		scrollView->setContentSize(layer->getContentSize());
		scrollView->setPosition(ccp(0,0));
		scrollView->setContainer(layer);
		scrollView->setDelegate(this);
		scrollView->setContentOffset(ccp(0, -800), false);
		scrollView->setBounceable(true);

		this->addChild(scrollView);

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
{ // µµ¿ò¸»Ã¢À» ´ÝÀ½
	CCDirector::sharedDirector()->popScene();
	//push, pop SceneÀ» ÀÌ¿ëÇØ¼­ µÇµ¹¾Æ°¡±â ±¸Çö.
}

void HelpScene::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector() ->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}
void HelpScene::onExit()
{
	CCLayer::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void HelpScene::scrollViewDidScroll(CCScrollView* view)
{
}

void HelpScene::scrollViewDidZoom(CCScrollView* view)
{
}

bool HelpScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}