#include "gameResultScene.h"
#include "gameEndScene.h"
#include <algorithm>

gameResultScene::gameResultScene(std::string _result,int _stageidx,int _count)
{
	result = _result;
	stageidx = _stageidx;
	count = _count;
	this->init();
}

bool gameResultScene::init()
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return false;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* background = CCSprite::create("img\\endResult\\end_bg.png");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);

	char stagenum[32];
	sprintf(stagenum,"img\\game\\stageNum\\%d.png",stageidx-9);
	CCSprite* stageNSprite = CCSprite::create(stagenum);
	stageNSprite->setPosition(ccp(size.width*0.32,size.height*0.93));
	this->addChild(stageNSprite,0);

	CCMenuItemImage *btnEnd = CCMenuItemImage::create(
		"img/endResult/main_btn_endgame.png", "img/endResult/main_btn_endgame_n.png", this, menu_selector(gameResultScene::menu_goEndScene));

	btnEnd->setPosition(ccp(size.width*0.8, size.height*0.1));
	btnEnd->setScale(0.8);
	CCMenu* endMenu = CCMenu::create(btnEnd, NULL);
	endMenu->setPosition(CCPointZero);

	this->addChild(endMenu, 2);

	parser();

	this->make_foodSprite();
	return true;
}
/**
전달받은 string parsing
*/
void gameResultScene::parser()
{
	for(int i = 0; i < 10; i++){
		check_arr[i] = 0;
	}
	for(int i = 0; i < result.length(); i++){
		if(!(i%2)) {
			char* nowChar = &result.at(i);
			int tmp = atoi(nowChar);
			check_arr[tmp] = 1;
		}
	}
}

void gameResultScene::make_foodSprite()
{//make food sprite using array foodArrayForSprite
	int successCnt = 0;			//성공한 음식 갯수 저장하는곳
	double x=0.2;
	double y=0.65;// for sprite position
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for(int i=0;i<10;i++)
	{		
		if(i==2 || i==4 || i== 6 || i == 8)
		{
			x=0.2;
			y=y-0.15;
		}
		else if(i==1 || i==3 || i==5 || i==7 || i==9)
		{	
			x=0.6;
		}
		
		/**
		Daun
		이미지 뿌리는 부분...
		**/

		CCPoint position = ccp(winSize.width*x,winSize.height*y);
		char food_arr[20];
		sprintf(food_arr,"/img/food/%d_f.png",stageidx);
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(food_arr);
		CCSprite* foodsprite = CCSprite::createWithTexture(texture,CCRectMake(100*(i%5),100*(i/5),100,100));

		foodsprite->setAnchorPoint(ccp(0,0));
		foodsprite->setPosition(position);

		if(check_arr[i+1] == 1) {
			//빨간 동그라미 그리기
			CCSprite* check = CCSprite::create("img/endResult/end_redCircle.png");
			check->setPosition(position);
			check->setAnchorPoint(ccp(0,0));
			this->addChild(check,2);
			successCnt++;
		}

		this->addChild(foodsprite,1);
	}

	if(count == successCnt) {
			/*******************************여기 조건문 고쳐야함.. 스테이지에 몇개 음식인지를 받아와서 하는걸로..*******/
			resultOfStage = 1;
		} else resultOfStage = 0;
}

void gameResultScene::menu_goEndScene(CCObject* pSender)
{
	CCScene *pScene = CCScene::create();
	gameEndScene *layer = new gameEndScene(resultOfStage,stageidx);
	layer->autorelease();
	pScene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}
