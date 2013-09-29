#include "gameResultScene.h"
#include "gameEndScene.h"

gameResultScene::gameResultScene(std::string _result,int _stageidx)
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
	foodArrayForSprite[0]="map/1.jpg";
	foodArrayForSprite[1]="map/2.png";
	foodArrayForSprite[2]="map/3,png";
	foodArrayForSprite[3]="map/4.png";

	this->make_foodSprite();
	this->check_food();

}


bool gameResultScene::init()
{
	return true;
}

void gameResultScene::check_food()
{
	resultOfStage=1;
}

void gameResultScene::make_foodSprite()
{//make food sprite using array foodArrayForSprite
	int x,y=0.8;// for sprite position
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for(int i=0;foodArrayForSprite[i]==0;i++)
	{
		if(i%2==0)
			x=0.35;
		else
		{
			y=y-0.15;
			x=0.65;
		}
		CCSprite* foodsprite = CCSprite::create(foodArrayForSprite[i]);
		foodsprite->setAnchorPoint(ccp(0,0));
		foodsprite->setPosition(ccp(winSize.width*x,winSize.height*y));
		this->addChild(foodsprite);
	}
}

void gameResultScene::menu_goEndScene(CCObject* pSender)
{
	CCScene *pScene = CCScene::create();
	gameEndScene *layer = new gameEndScene(resultOfStage,stageidx);
	layer->autorelease();
	pScene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}
