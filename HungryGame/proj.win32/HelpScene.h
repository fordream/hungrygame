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

	void menu_helpGameplay(CCObject*);// ���� �÷��� ����
	void menu_helpItem(CCObject*); // ���� ������ ����
	void menu_helpObstacle(CCObject*); // ���� ��ֹ� ����
	void menu_backScene(CCObject*); //����â �� ȭ������
	void menu_closeHelpScene(CCObject*); // ����â�� ����

	CREATE_FUNC(HelpScene);
};

