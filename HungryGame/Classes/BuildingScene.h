#ifndef __BUILDING_SCENE_H__
#define __BUILDING_SCENE_H__

#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class BuildingScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuBuild1Callback(CCObject* pSender);
	void menuBuild2Callback(CCObject* pSender);
	void menuBuild3Callback(CCObject* pSender);
	void menuBuild4Callback(CCObject* pSender);
	void menuGoBackCallback(CCObject* pSender);

	int buildingNum;

    // implement the "static node()" method manually
	CREATE_FUNC(BuildingScene);
};

#endif  // __BUILDING_SCENE_H__