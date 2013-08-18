#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

class Character : public cocos2d::CCLayer
{
public:

	Character();
	Character(int,int);

	void setPCharacter(CCSprite *PC);
	CCSprite *getPCharacter();

	void setWidth(int CHWIDTH);
	int getWidth();
	void setHeight(int CHHEIGHT);
	int getHeight();

	void setX(float CHX);
	float getX();
	void setY(float CHY);
	float getY();

	bool goUpPosition();
	bool goDownPosition();
	bool goLeftPosition();
	bool goRightPosition();

	void setSpeed(int CHSPEED);
	int getSpeed();

	void setHealth(int CHHEALTH);
	int getHealth();
	

private:
	CCSprite *pCharacter;	// 캐릭터의 이미지
	int chWidth, chHeight;	// 캐릭터의 가로, 세로길이
	float chX, chY;			// 캐릭터의 좌표

	int chSpeed;			// 캐릭터의 스피드
	int chHealth;			// 캐릭터 체력

	int mX ,mY;				// 캐릭터가 한번에 이동할 거리



    // implement the "static node()" method manually
    CREATE_FUNC(Character);
};

#endif  // __CHARACTER_H__