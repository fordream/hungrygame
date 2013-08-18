#pragma once
#include "cocos2d.h"
#include <string>
using std::string;
USING_NS_CC;

class Item
{
private :
	CCSprite *pItem; //아이템의 이미지
	int TemWidth, TemHeight; //아이템의 가로, 세로 길이
	float temX, temY; //아이템의 좌표

public :
	//아이템 출현
	void setPItem(CCSprite*);
	CCSprite *getItem();

	//크기 결정
	void setWidth(int);
	int getWidth();
	void setHeight(int);
	int getHeight();

	//위치 결정
	void setX(float);
	float getX();
	void setY(float);
	float getY();


	//기능발현?
	void func();
};
