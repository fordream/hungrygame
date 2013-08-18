#include "character.h"

using namespace cocos2d;


Character::Character()
{
	pCharacter = NULL;	// 캐릭터의 이미지
	
	chWidth = 0;
	chHeight = 0;
	
	chX = 0;
	chY = 0;			// 캐릭터의 좌표

	chSpeed = 0;			// 캐릭터의 스피드
	chHealth = 0;			// 캐릭터 체력

	mX = 0;
	mY = 0;				// 캐릭터가 한번에 이동할 거리

}
Character::Character(int MX, int MY)
{
	pCharacter = NULL;	// 캐릭터의 이미지
	
	chWidth = 0;
	chHeight = 0;
	
	chX = 0;
	chY = 0;			// 캐릭터의 좌표

	chSpeed = 0;			// 캐릭터의 스피드
	chHealth = 0;			// 캐릭터 체력

	mX = MX;
	mY = MY;				// 캐릭터가 한번에 이동할 거리

}

void Character::setPCharacter(CCSprite *PC)
{ pCharacter = PC;}
CCSprite *Character::getPCharacter() { return pCharacter; }

void Character::setWidth(int CHWIDTH){ chWidth = CHWIDTH; }
int Character::getWidth(){ return chWidth; }
void Character::setHeight(int CHHEIGHT){ chHeight = CHHEIGHT; }
int Character::getHeight(){ return chHeight;}

void Character::setX(float CHX){ chX = CHX; }
float Character::getX(){ return chX; }
void Character::setY(float CHY){ chY = CHY; }
float Character::getY(){ return chY; }

bool Character::goUpPosition()
{ 

	chY += mY; 
    CCActionInterval*  actionTo = CCMoveTo::create(chSpeed, ccp(chX, chY));

    pCharacter->runAction( actionTo);

	return true;
}
bool Character::goDownPosition()
{
	chY -= mY; 
	CCActionInterval* actionTo = CCMoveTo::create(chSpeed, ccp(chX,chY));

	pCharacter->runAction(actionTo);
	return true;
}
bool Character::goLeftPosition()
{
	chX -= mX; 
	CCActionInterval*  actionTo = CCMoveTo::create(chSpeed, ccp(chX, chY));

    pCharacter->runAction( actionTo);

	return true;}
bool Character::goRightPosition(){
	chX += mX; 
	CCActionInterval*  actionTo = CCMoveTo::create(chSpeed, ccp(chX, chY));

    pCharacter->runAction( actionTo);

	return true;
}

void Character::setSpeed(int CHSPEED){ chSpeed = CHSPEED; }
int Character::getSpeed(){ return chSpeed; }

void Character::setHealth(int CHHEALTH){ chHealth = CHHEALTH; }
int Character::getHealth(){ return chHealth; }
