#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

USING_NS_CC;
USING_NS_CC_EXT;

class HelpScene : public CCLayerColor, public CCScrollViewDelegate
{
public:
	
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	void menu_closeHelpScene(CCObject*); // µµ¿ò¸»Ã¢À» ´ÝÀ½

	CREATE_FUNC(HelpScene);

	std::string helpType;

public:
	virtual void onEnter();
	virtual void onExit();

	void scrollViewDidScroll(CCScrollView* view);
	void scrollViewDidZoom(CCScrollView* view);
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

	CCScrollView *scrollView;
};

#endif //__HELP_SCENE_H__
