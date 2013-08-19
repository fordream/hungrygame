#ifndef _MakerInfoScene_Main_
#define _MakerInfoScene_Main_

#include "cocos2d.h"

class MakerInfoScene_J : public cocos2d::CCLayerColor
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(MakerInfoScene_J);

	//�ݱ�
	void doClose( CCObject* pSender );

	cocos2d::CCSprite* pInfo;	//����â ���̾�
	cocos2d::CCSize winSize;
};


#endif
