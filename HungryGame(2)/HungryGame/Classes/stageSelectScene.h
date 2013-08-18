#ifndef __STAGESELECT_SCENE_H__
#define __STAGESELECT_SCENE_H__
/*
* 2013 08 18
* Joung Daun
* Stage Select
*/
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class stageSelect : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
   
	void stageMenu(CCObject* pSender);

    // implement the "static node()" method manually
	CREATE_FUNC(stageSelect);
};

#endif  // __BUILDING_SCENE_H__