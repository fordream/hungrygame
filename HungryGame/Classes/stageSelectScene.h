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

class stageSelectScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
   
	void stageMenu(CCObject* pSender);
	void menuGoBackCallback(CCObject* pSender);
	void onExit();
	void goStageScene();
	void doMsgRecv(CCObject* obj);
	int sStageNum; // for stage of each building
	int buildingNum;
    // implement the "static node()" method manually
	CREATE_FUNC(stageSelectScene);
};

#endif  // __BUILDING_SCENE_H__