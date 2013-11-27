/*
pineoc@naver.com // ������
game End Scene 
get result for success Scene or fail Scene 
*/

#include "gameEndScene.h"
#include "gameScene.h"
#include "BuildingScene.h"


gameEndScene::gameEndScene(int _result,int _stageidx)
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return ;
	result = _result;
	stageidx = _stageidx;

	//stageidx = 11; // �ӽ÷� ������ ����. ���Ļ���.


	CCSize size = CCDirector::sharedDirector()->getWinSize();

	char stagenum[32];
	sprintf(stagenum,"img\\game\\stageNum\\%d.png",stageidx-9);
	CCSprite* stageNSprite = CCSprite::create(stagenum);
	stageNSprite->setPosition(ccp(size.width*0.32,size.height*0.93));
	this->addChild(stageNSprite,0);

	CCSprite* background = CCSprite::create("img/end/endChk_bg.png");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);

	//makedFoodInit();
	char food_arr[20];
	sprintf(food_arr,"/img/food/%d.png",stageidx);
	CCSprite* foodImage = CCSprite::create(food_arr); //by eunji
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
		CCMenuItemImage *pMenu_backtoStageScene = CCMenuItemImage::create(
		"img/end/end_btn_StageScene.png","img/end/end_btn_StageScene_n.png",
		this,
		menu_selector(gameEndScene::menu_backtoStageScene));
		
		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu_s = CCMenu::create(pMenu_retry,pMenu_nextStage,pMenu_backtoStageScene, NULL);
		pMenu_retry->setScale(0.8);
		pMenu_nextStage->setScale(0.8);

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
		CCMenuItemImage *pMenu_backtoStageScene = CCMenuItemImage::create(
			"img/end/end_btn_StageScene.png","img/end/end_btn_StageScene_n.png",
			this,
			menu_selector(gameEndScene::menu_backtoStageScene));
		pMenu_retry->setScale(0.8);
		pMenu_backtoStageScene->setScale(0.8);
		CCMenu* pMenu_f = CCMenu::create(pMenu_retry,pMenu_backtoStageScene,NULL);
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
	
	//���⼭ ���������� idx�����ͼ� �ٽ� replace �ϴ� ������� �����ҵ�.
	CCScene *pScene = gameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);

}
void gameEndScene::menu_nextStage(CCObject* pSender)
{
	
	//���������� idx�� �����ͼ� idx+1 �Ͽ� ���� ���������� �������Բ� �ؾ��� ��.
	CCScene *pScene = gameScene::scene();
	CCUserDefault::sharedUserDefault()->setIntegerForKey("curStage",stageidx+1);
	CCDirector::sharedDirector()->replaceScene(pScene);
	
}
void gameEndScene::menu_backtoStageScene(CCObject* pSender)
{
	/*
	�������� �����ϴ� Scene���� �Ѿ.
	back to selectstage Scene
	*/
	CCScene *pScene = BuildingScene::scene();

	CCDirector::sharedDirector()->replaceScene(pScene);
}

void gameEndScene::makedFoodInit()
{
	/* eunji */
	for(int i=10; i<50; i++) 
	{
		char *fileName = new char [16];
		sprintf(fileName, "img/food/%d.png", i);
		makedFoodArrayForSprite[i] = fileName;
	}
	
}