#pragma once
#include "cocos2d.h"
USING_NS_CC;
class gameResultScene : public CCLayerColor
{
public:
	gameResultScene(int,int);

	virtual bool init();

	void menu_goEndScene(CCObject*);

	int result;
	int stageidx;
};

