#ifndef _MakerInfoScene_H
#define _MakerInfoScene_H

#include "cocos2d.h"

class MakerInfoScene : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	//�ݱ�
	void doClose( CCObject* );

	CREATE_FUNC(MakerInfoScene);

	cocos2d::CCSprite* pInfo;	//����â ���̾�
	cocos2d::CCSize winSize;
};

#endif