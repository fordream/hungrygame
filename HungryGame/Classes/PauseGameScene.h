/*지윤 - 게임 중 일시정지 창
게임 도중 일시정지
메인으로
새게임
도움말
이어하기*/
#pragma once
#ifndef _PauseGameScene_
#define _PauseGameScene_

#include "cocos2d.h"

class PauseGameScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();
	CREATE_FUNC(PauseGameScene);
	cocos2d::CCSize winSize;

	CCLayerColor* backLayer;
	CCLayerColor* popUpLayer;

	int pStageidx;// integer for regame 

	//메뉴 4가지
	void goMain( CCObject* pSender );	//메인으로
	void newGame( CCObject* pSender );	//새게임
	void goHelp ( CCObject* pSender );	//도움말
	void doClose( CCObject* pSender );	//이어하기
	
	void setStageIdx(int num); // set stage index 
	
	void menuPauseCallback (CCObject* pSender);	//콜백
};

#endif