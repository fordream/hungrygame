#pragma once
#include "cocos2d.h"
USING_NS_CC;

class HelpScene : public CCLayerColor
{
public:
	HelpScene(void);
	~HelpScene(void);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	void menu_helpGameplay(CCObject*);// 게임 플레이 설명
	void menu_helpItem(CCObject*); // 게임 아이템 설명
	void menu_helpObstacle(CCObject*); // 게임 장애물 설명
	void menu_backScene(CCObject*); //도움말창 전 화면으로
	void menu_closeHelpScene(CCObject*); // 도움말창을 닫음

	CREATE_FUNC(HelpScene);
};

