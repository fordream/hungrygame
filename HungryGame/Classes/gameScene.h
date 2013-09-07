#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__
/*
* 2013 08 18
* Joung Daun
* Game Scene
*/
#include "cocos2d.h"

#include "Box2D/Box2D.h"

#include "SimpleAudioEngine.h"

class gameScene : public cocos2d::CCLayer
{
public:
	//gameScene();
	//~gameScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
   
    // implement the "static node()" method manually
	CREATE_FUNC(gameScene);

	/*
	pineoc's function (general function)
	display point -> tile point function
	*/
	CCPoint tileCoorPosition(CCPoint);
	CCTMXLayer *backgroundLayer;
	void createObstacle(); // ��ֹ� ���� ����
	void checkPosition(CCPoint);
	CCTMXLayer *metainfo; //��������

	CCPoint obstaclePosition;
	CCSprite *obstacle;
	CCTMXLayer *wall;
	// --------------------------------- Daun Start -------------------//

	CCTMXTiledMap *tileMap; // tileMap name to select stage
	void createCharacter();
	void ccTouchEnded(CCTouch *, CCEvent* );
	CCSprite        *character;
	bool ccTouchBegan(CCTouch *, CCEvent* );
	void onEnter();
	int checkCrash;
	// ------------------------------Daun End ----------------------//

	//-------------------------------pineoc's start------------------//
	void createFood(CCPoint,char*); //food create item, (point, imageName)
	void linktochar_food();
	bool checkDup(CCSprite*); // check duplication about tile 
	void delFood(CCObject*);
	void updateFoodSprte(float dt);
	void followCharacter(float);

	CCTMXObjectGroup *foods; // group for foods object
	CCArray* tomakeFood; // �������ϴ� ������� ���, array that have to make food ingrediant list
	CCArray* onCheckFoodDisplay; // ���� ������ �Ծ����� �ȸԾ����� üũ�� �迭,
	// array for check when character eat the food ingrediant
	
	CCArray* foodSpriteArray; // array for save the food sprite
	CCArray* foodFollowArray; // array for follow character
	int foodcount; // for food count
	CCPoint beforeMoveCharPoint[10];

	//CCTMXLayer* foodLayer; // for food object layer
	//-----------------------------------------------------------------//

	//--------------------JIYOON-------------------------------------
	void doPop(CCObject* pSender);	//creat popup
	void doNotification(CCObject *obj);
	CCMenu* PauseMenu;// pause button menu
	//------------------JIYOON END------------------------------------

};

#endif  // __GAME_SCENE_H__