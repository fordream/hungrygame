//pineoc@naver.com
//HelpScene.h
//����â ����

#pragma once
#include "cocos2d.h"
USING_NS_CC;

class HelpScene : public CCLayerColor
{
public:
	//Scene���� �Ķ���͸� �ѱ�� ���ؼ�.
	//HelpScene(std::string);
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	void menu_closeHelpScene(CCObject*); // ����â�� ����

	CREATE_FUNC(HelpScene);

	std::string helpType;
};

