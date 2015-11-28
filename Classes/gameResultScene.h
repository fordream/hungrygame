#pragma once
#include "cocos2d.h"
USING_NS_CC;
class gameResultScene : public CCLayerColor
{
public:
	gameResultScene(std::string,int,int);
	//~gameResultScene();

	virtual bool init();

//	void check_food();
	void make_foodSprite();

	void menu_goEndScene(CCObject*);

//	void selectionSort(int*,int);
//	bool checkSame(int*,int*);
	void parser();

	std::string result;
	int stageidx;
	int resultOfStage;
	int check_arr[10];// check for food array 0: À½½Ä¾È¸ÔÀ½ 1: À½½Ä¸ÔÀ½
	int count;
//	char* foodArrayForSprite[11];// for making food sprite
//	CCArray* foodArraySpritecolor;
	
};

