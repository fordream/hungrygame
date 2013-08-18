#pragma once
#include "cocos2d.h"
#include <string>
using std::string;
USING_NS_CC;
class food
{
public:
	food(void);
	~food(void);

	//밑에 init과 scene 두개의 함수 같은 경우는 한 장면을 구성하는데 쓰이는 함수들로 보여서
	//순수 오브젝트에는 맞지 않아 보임.
	//virtual bool init();

	//static cocos2d::CCScene* scene();//필요 없을거 같아 보임.

	//void menuCloseCallback(CCObject*);
	//위의 메뉴 버튼은 순수 음식 오브젝트에는 맞지 않은것으로 보임.

	void setPFood(CCSprite*); // 음식의 사진 설정
	CCSprite* getPFood(); // 음식의 사진 불러오기

	void setWidth(int);
	int getWidth();
	void setHeight(int);
	int getHeight();

	void setX(float);
	float getX();
	void setY(float);
	float getY();

private:
	CCSprite *pFood; // 음식의 이미지
	int foodWidth, foodHeight; // 음식의 가로, 세로크기
	float foodX, foodY; // 음식의 좌표

	int foodIdx; //음식의 숫자(index)
	string foodName; // 음식이름


};