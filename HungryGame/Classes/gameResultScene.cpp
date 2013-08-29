#include "gameResultScene.h"
#include "gameEndScene.h"

gameResultScene::gameResultScene(int _result,int _stageidx)
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return ;
	
	result = _result;
	stageidx = _stageidx;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* background = CCSprite::create("gameResultScene_bg.png");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);

	CCSprite *success = CCSprite::create("result_image.png");//image for cook dish
	success->setPosition(ccp(size.width/2, size.height/0.8));
	this->addChild(success,2);

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
