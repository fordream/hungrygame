/*���� - ���� �� �Ͻ����� â
���� ���� �Ͻ�����
��������
������
����
�̾��ϱ�*/
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

	//�޴� 4����
	void goMain( CCObject* pSender );	//��������
	void newGame( CCObject* pSender );	//������
	void goHelp ( CCObject* pSender );	//����
	void doClose( CCObject* pSender );	//�̾��ϱ�
	
	void setStageIdx(int num); // set stage index 
	
	void menuPauseCallback (CCObject* pSender);	//�ݹ�
};

#endif