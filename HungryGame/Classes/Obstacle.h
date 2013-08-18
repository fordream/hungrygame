#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

#include "cocos2d.h"

using namespace cocos2d;

class Obstacle : public cocos2d::CCLayer
{
public:

	Obstacle();

	void setPObstacle(CCSprite* p);
	//CCSprite* getPObstacle();

	void setWidth(int width);
	int getWidth();
	void setHeight(int height);
	int getHeight();

	void setX(int x);
	int getX();
	void setY(int y);
	int getY();

	bool goUp();
	bool goDown();
	bool goRight();
	bool goLeft();

	void setSpeed(int speed);
	int getSpeed();



private:
	
	CCSprite* pObstacle;	//장애물의 이미지
	int obWidth, obHeight;	//장애물의 가로, 세로 길이
	float obX, obY;			//장애물의 좌표

	int obSpeed;			//장애물 스피드


	CREATE_FUNC(Obstacle);
	
};

#endif  // __OBSTACLE_SCENE_H__