#include "MakerInfoScene.h"

using namespace cocos2d;

CCScene* MakerInfoScene::scene()
{
	CCScene *scene = CCScene::create();

	MakerInfoScene *layer = MakerInfoScene::create();

	scene->addChild(layer);

	return scene;
}

bool MakerInfoScene::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(255,255,255,100)));

		//위도우 사이즈
		winSize = CCDirector::sharedDirector()->getWinSize();

		//Info창 레이어 추가
		pInfo = CCSprite::create("devinfoScene_bg.png");
		CC_BREAK_IF(!pInfo);
		pInfo->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(pInfo);

		//닫기버튼
		CCMenuItemImage *pClose = CCMenuItemImage::create(
			"btn_goBack.png","btn_goBack_n.png",this,menu_selector(MakerInfoScene::doClose));
		CC_BREAK_IF(!pClose);
		pClose->setPosition(ccp(winSize.width / 1.35 , winSize.height /14.23)); 
		CCMenu* pMenu = CCMenu::create(pClose,NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu);

		bRet = true;
	} while (0);
	return true;
}


void MakerInfoScene::doClose( CCObject* pSender )
{
	//장면닫음
	CCDirector::sharedDirector()->popScene();
}