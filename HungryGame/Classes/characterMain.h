#ifndef __CHARACTER_MAIN_H__
#define __CHARACTER_MAIN_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"
#include "character.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;
class CharacterMain : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void selectMenu(CCObject* pSender);
	CCSprite* pDaun;
	Character *Daun;
    // implement the "static node()" method manually
    CREATE_FUNC(CharacterMain);
};

#endif  // __CHARACTER_MAIN_H__