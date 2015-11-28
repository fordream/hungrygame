/*
* 2013 08 27
* option scene
* Daun
*/

#ifndef __OPTION_SCENE_H__
#define __OPTION_SCENE_H__

#include "cocos2d.h"
#include "mainScene.h"
#include "music.h"
#include "userData.h"


class OptionScene : public CCLayerColor
{
public:
	
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

	void goBackMenu(CCObject*); // go back to menu

	void OnOffMenu(CCObject*);	// set Music ON or OFF


	CREATE_FUNC(OptionScene);

	std::string helpType;
};

#endif  // __OPTION_SCENE_H__