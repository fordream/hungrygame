#include "MakerInfoScene_J.h"

using namespace cocos2d;

CCScene* MakerInfoScene_J::scene()
{
	CCScene *scene = CCScene::create();

	MakerInfoScene_J *layer = MakerInfoScene_J::create();

	scene->addChild(layer);

	return scene;
}

bool MakerInfoScene_J::init()
{
	if (!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{ return false; }

	//������ ������
	winSize = CCDirector::sharedDirector()->getWinSize();

	//Infoâ ���̾� �߰�
	pInfo = CCSprite::create("Images/�����ڼҰ�.png");
	pInfo->setPosition(ccp(winSize.width/2,winSize.height/2));
	this->addChild(pInfo);

	//�ݱ��ư
	CCMenuItemImage *pClose = CCMenuItemImage::create(
		"Images/btn_goBack.png","Images/btn_goBack_n.png",this,menu_selector(MakerInfoScene_J::doClose));
	CCMenu* pMenu = CCMenu::create(pClose,NULL);
	pMenu->setPosition(winSize.width/2,10);
	this->addChild(pMenu);

	return true;
}


void MakerInfoScene_J::doClose( CCObject* pSender )
{
	//������
	CCDirector::sharedDirector()->popScene();
}