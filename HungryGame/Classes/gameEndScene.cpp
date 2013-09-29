/*
pineoc@naver.com // 이윤석
game End Scene 
get result for success Scene or fail Scene 
*/

#include "gameEndScene.h"
#include "gameScene.h"
#include "stageSelectScene.h"

gameEndScene::gameEndScene(int _result,int _stageidx)
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return ;
	result = _result;
	stageidx = _stageidx;

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* background = CCSprite::create("img/end/endChk_bg.png");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);

	CCSprite* foodImage = CCSprite::create("img/end/fish_cultlet.png");
	foodImage->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(foodImage,1);

	/*
	use result, make menu button 
	*/
	if(result == 1) // success the game
	{// menu button : retry , next stage, back to select building(stage)
		//success image 
		CCSprite *success = CCSprite::create("img/end/endChk_success.png");
		success->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(success,2);

		//retry button
		CCMenuItemImage *pMenu_retry = CCMenuItemImage::create(
			"img/end/endChk_btn_again.png","img/end/endChk_btn_again_n.png",
			this,
			menu_selector(gameEndScene::menu_retry));

		//go to nextstage button
		CCMenuItemImage *pMenu_nextStage = CCMenuItemImage::create(
			"img/end/endChk_btn_next.png","img/end/endChk_btn_next_n.png",
			this,
			menu_selector(gameEndScene::menu_nextStage));

		//go to stageScene
		/*CCMenuItemImage *pMenu_backtoStageScene = CCMenuItemImage::create(
		"end_btn_backtoStageScene.png","end_btn_backtoStageScene_n.png",
		this,
		menu_selector(gameEndScene::menu_backtoStageScene));
		*/
		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu_s = CCMenu::create(pMenu_retry,pMenu_nextStage, NULL);
		pMenu_s->alignItemsHorizontally();
		pMenu_s->setPosition(ccp(size.width/2,size.height*0.2));

		//// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu_s, 2);

	}
	else // result == 0 , fail the game
	{//menu button : retry, back to select building(stage)

		CCSprite *fail = CCSprite::create("img/end/endChk_fail.png");
		fail->setPosition(ccp(size.width/2, size.height/2));
		this->addChild(fail,2);


		CCMenuItemImage *pMenu_retry = CCMenuItemImage::create(
			"img/end/endChk_btn_again.png","img/end/endChk_btn_again_n.png",
			this,
			menu_selector(gameEndScene::menu_retry));

		//CCMenuItemImage *pMenu_backtoStageScene = CCMenuItemImage::create(
		//	"end_btn_backtoStage.png","end_btn_backtoStage_n.png",
		//	this,
		//	menu_selector(gameEndScene::menu_backtoStageScene));

		CCMenu* pMenu_f = CCMenu::create(pMenu_retry,NULL);
		pMenu_f->alignItemsHorizontally();
		pMenu_f->setPosition(ccp(size.width/2,size.height*0.2));

		this->addChild(pMenu_f,2);
	}

}
bool gameEndScene::init()
{
	CCLog("init");
	return true;
}
void gameEndScene::menu_retry(CCObject* pSender)
{
	
	//여기서 스테이지의 idx가져와서 다시 replace 하는 방식으로 가야할듯.
	CCScene *pScene = gameScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
	
	
}
void gameEndScene::menu_nextStage(CCObject* pSender)
{
	
	//스테이지의 idx를 가져와서 idx+1 하여 다음 스테이지를 가져오게끔 해야할 듯.
	CCScene *pScene = gameScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
	
}
void gameEndScene::menu_backtoStageScene(CCObject* pSender)
{
	/*
	스테이지 선택하는 Scene으로 넘어감.
	back to selectstage Scene
	*/
	CCScene *pScene = stageSelect::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
}