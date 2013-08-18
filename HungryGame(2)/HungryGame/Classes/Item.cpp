#include "cocos2d.h"
#include "item.h"

//bool food ::init(){}
//CCScene* food::scene(){}
//void menuCloseCallback(CCObject*);

void Item::setPItem(CCSprite* picture)
{//아이템 이미지
	pItem = picture;
}
CCSprite* Item::getItem()
{// 아이템 이미지 불러오기
	return pItem;
}
void Item::setWidth(int w)
{	TemWidth=w;}
int Item::getWidth()
{	return TemWidth;}
void Item::setHeight(int h)
{	TemHeight=h;}
int Item::getHeight()
{	return TemHeight;}
void Item::setX(float x)
{	temX=x;}
float Item::getX()
{return temX;}
void Item::setY(float y)
{	temY=y;}
float Item::getY()
{	return temY;}
