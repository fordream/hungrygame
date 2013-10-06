/*
pineoc@naver.com // ������
game End Scene 
get result for success Scene or fail Scene 
*/


#pragma once
#include "cocos2d.h"
USING_NS_CC;
class gameEndScene : public CCLayerColor
{
public:
	gameEndScene(int,int);
	//~gameEndScene(void);

	virtual bool init();

	//static cocos2d::CCScene* scene();
	//CREATE_FUNC(gameEndScene);

	void menu_retry(CCObject*);// retry game
	void menu_backtoStageScene(CCObject*);//back to stageScene
	void menu_nextStage(CCObject*);//go to next stage
	void check_point_star(CCObject*);//check the point to make star

	int result; // game result, success or fail, success = 1, fail = 0
	int stageidx;// stage index

	/* 
	
	by eunji

	makedFoodArrayForSprite�� �� ������������ �ϼ��� ���� �׸� ��������Ʈ�� ������ ����.
	�ε����� ���� 1������ 3��° ���������� 13. �� makedFoodArrayForSprite[13]

	11~19
	21~29
	31~39
	41~49

	�̷��� �� 36���� ���������׸��� ����. 

	img/food/�ε�����.png �� �����.


	�ε������� stageidx�� �����ϰ� ������µ� ���࿡ ������ �ʰ� ������ ����� �ٸ��� �ٲ㵵 �������.

	���� ���� �������� 11.png �� 22.png �ΰ��� �׸��� ����.
	
	*/
	char* makedFoodArrayForSprite[50]; // 4 part * 9 stage = 36 (�߰�, 0�ε��� ����.)
	void makedFoodInit();
};