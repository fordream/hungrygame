#pragma once
#include "cocos2d.h"
USING_NS_CC;
class gameResultScene : public CCLayerColor
{
public:
	gameResultScene(std::string,int);

	virtual bool init();

	void check_food();
	void make_foodSprite();

	void menu_goEndScene(CCObject*);

	std::string result;
	int stageidx;
	int resultOfStage;
	int check_arr[10];// check for food array
	char* foodArrayForSprite[10];// for making food sprite
};

