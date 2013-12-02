#include "PauseGameScene.h"
#include "mainScene.h"
#include "HelpScene.h"

using namespace cocos2d;

CCScene* PauseGameScene::scene()
{
	CCScene* scene = CCScene::create();

	PauseGameScene *layer = PauseGameScene::create();

	scene->addChild(layer);

	return scene;
}

bool PauseGameScene::init()
{
	if( !CCLayerColor::initWithColor(ccc4(0,0,0,0)))
	{ return false; }
	pStageidx=CCUserDefault::sharedUserDefault()->getIntegerForKey("curStage");


	CCString* popParam=CCString::create("0");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기

	winSize=CCDirector::sharedDirector()->getWinSize();

	CCSprite *bg = CCSprite::create("img\\pause\\pause_bg.png");
	bg->setScale(0.5);
	bg->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(bg,0);
	
	//메뉴추가
	CCMenuItemImage* pMain = CCMenuItemImage::create(
		"img\\pause\\pause_btn_goMain.png","img\\pause\\pause_btn_goMain_n.png", this, menu_selector(PauseGameScene::goMain));
	pMain->setScale(0.5);
	CCMenuItemImage* pHelp = CCMenuItemImage::create(
		"img\\pause\\pause_btn_help.png","img\\pause\\pause_btn_help_n.png",this,menu_selector(PauseGameScene::goHelp));
	pHelp->setScale(0.5);
	CCMenuItemImage* pGame = CCMenuItemImage::create(
		"img\\pause\\pause_btn_restart.png","img\\pause\\pause_btn_restart_n.png", this, menu_selector(PauseGameScene::newGame));
	pGame->setScale(0.5);
	CCMenuItemImage* pClose = CCMenuItemImage::create(
		"img\\pause\\pause_btn_continue.png","img\\pause\\pause_btn_continue.png", this, menu_selector(PauseGameScene::doClose));
	pClose->setScale(0.5);

	//메뉴생성
	CCMenu* pauseMenu=CCMenu::create(pMain, pGame, pHelp, pClose, NULL);
	pauseMenu->setPosition(ccp(240, 450));
	pauseMenu->alignItemsVertically();
	this->addChild(pauseMenu,10);

	//backLayer추가
	backLayer=CCLayerColor::create(ccc4(0,0,0,0), winSize.width, winSize.height);
	backLayer->setAnchorPoint(ccp(0,0));
	backLayer->setPosition(ccp(0,0));
	this->addChild(backLayer);

	//popUpLayer추가
	popUpLayer=CCLayerColor::create(ccc4(0,0,0,0), 250,150);
	popUpLayer->setAnchorPoint(ccp(0,0));
	popUpLayer->setPosition(ccp((winSize.width-popUpLayer->getContentSize().width)/2, 
				(winSize.height-popUpLayer->getContentSize().height)/2   )  );
	this->addChild(popUpLayer);

    return true;
}


void PauseGameScene::goMain( CCObject* pSender )
{
	//처음 메인화면으로
	/*CCScene *pScene = Main::scene();

	CCDirector::sharedDirector()->pushScene(pScene);*/
	CCString* popParam=CCString::create("2");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기
	this->removeFromParentAndCleanup(true);
}

void PauseGameScene::goHelp( CCObject* pSender )
{
	//도움말 화면으로
	CCScene *pScene = HelpScene::scene();

	CCDirector::sharedDirector()->pushScene(pScene);
	
}

void PauseGameScene::newGame( CCObject* pSender )
{
	//게임화면 초기화
	char buf[16];
	string a;
	sprintf(buf,"%d",pStageidx);
	a = string(buf);
	CCString* popParam=CCString::create(a);
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기
	this->removeFromParentAndCleanup(true);

}

void PauseGameScene::doClose(CCObject* pSender)
{
	//팝업창 닫고 게임 이어하기
	CCString* popParam=CCString::create("1");
	CCNotificationCenter::sharedNotificationCenter()->postNotification("notification", popParam);         //노티피케이션 보내기
	this->removeFromParentAndCleanup(true);		//팝업창 제거

}

void PauseGameScene::setStageIdx(int num)
{
	pStageidx = num;
}