/*
pineoc@naver.com // 이윤석
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

	makedFoodArrayForSprite는 각 스테이지마다 완성된 음식 그림 스프라이트를 저장할 변수.
	인덱스는 만약 1빌딩의 3번째 스테이지면 13. 즉 makedFoodArrayForSprite[13]

	11~19
	21~29
	31~39
	41~49

	이렇게 총 36개의 스테이지그림이 있음. 

	img/food/인덱스값.png 로 저장됨.


	인덱스값을 stageidx로 생각하고 만들었는데 만약에 윤석이 너가 생각한 방법과 다르면 바꿔도 상관없음.

	지금 현재 폴더에는 11.png 과 22.png 두개의 그림만 있음.
	
	*/
	char* makedFoodArrayForSprite[50]; // 4 part * 9 stage = 36 (추가, 0인덱스 없앰.)
	void makedFoodInit();
};