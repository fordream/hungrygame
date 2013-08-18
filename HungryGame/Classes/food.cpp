#include "cocos2d.h"
#include "food.h"

food::food(void)
{
}
food::~food(void)
{
}

//bool food ::init(){}
//CCScene* food::scene(){}
//void menuCloseCallback(CCObject*);

void food::setPFood(CCSprite* picture)
{// 음식의 사진 설정
	pFood = picture;
}
CCSprite* food::getPFood()
{// 음식의 사진 불러오기
	return pFood;
}
void food::setWidth(int w)
{	foodWidth=w;}
int food::getWidth()
{	return foodWidth;}
void food::setHeight(int h)
{	foodHeight=h;}
int food::getHeight()
{	return foodHeight;}
void food::setX(float x)
{	foodX=x;}
float food::getX()
{return foodX;}
void food::setY(float y)
{	foodY=y;}
float food::getY()
{	return foodY;}
