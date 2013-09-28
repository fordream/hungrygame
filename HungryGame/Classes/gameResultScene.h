#pragma once
#include "cocos2d.h"
USING_NS_CC;
class gameResultScene : public CCLayerColor
{
public:
	gameResultScene(std::string,int);

	virtual bool init();

	void menu_goEndScene(CCObject*);

	std::string result;
	int stageidx;
};

