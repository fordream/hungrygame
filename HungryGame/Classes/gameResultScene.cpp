#include "gameResultScene.h"
#include "gameEndScene.h"

gameResultScene::gameResultScene(int _result,int _stageidx)
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return ;
	
	result = _result;
	stageidx = _stageidx;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* background = CCSprite::create("img\\endResult\\end_bg.png");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);

	//CCSprite *result = CCSprite::create("img\\endResult\\result_image.png");//image for cook dish
	//result->setPosition(ccp(size.width/2, size.height/0.8));
	//this->addChild(result,2);

	CCMenuItemImage *btnEnd = CCMenuItemImage::create(
		"img/endResult/main_btn_endgame.png", "img/endResult/main_btn_endgame_n.png", this, menu_selector(gameResultScene::menu_goEndScene));

	btnEnd->setPosition(ccp(size.width*0.8, size.height*0.1));

	CCMenu* endMenu = CCMenu::create(btnEnd, NULL);
	endMenu->setPosition(CCPointZero);

	this->addChild(endMenu, 2);
	//-------------------------------
	// put the image food ingrediant
	//-------------------------------



}


bool gameResultScene::init()
{
	return true;
}

void gameResultScene::menu_goEndScene(CCObject* pSender)
{
	CCScene *pScene = CCScene::create();
	gameEndScene *layer = new gameEndScene(result,stageidx);
	layer->autorelease();
	pScene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}
