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
	~gameScene();
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
	void createObstacle(); // ��ֹ� ���� ����

	CCTMXLayer *					backgroundLayer;
	CCTMXLayer *					metainfo; //��������
	CCPoint							originPos;

	CCPoint							obstaclePosition;
	CCSprite *						obstacle;
	CCTMXLayer *					wall;



	/* gauge										: eunji */
	CCSprite *						gaugeBar;
	CCSprite *						gaugeHeart;
	int								character_XP;

	/* ,moving obstacle								: eunji */
	int								countNum;							// ������ ��.
	int								obX, obY;
	bool checkObDirection;
	void doActionMovingObstacleRight(CCObject* pSender);
	void doActionMovingObstacleLeft(CCObject* pSender);
	void moveObstacle(float);										// ��ֹ� ������ ����
	void doActionMovingObstacleReverse(CCObject* pSender);

	void decreaseGaugeBar(int num);
	void gameScene::increaseGaugeBar(int num);





	/* tiled map									: Daun */
	CCTMXTiledMap *tileMap; // tileMap name to select stage

	/* character									: Daun */
	int								movingSpeed;						// ĳ������ �̵� �ӵ�
	int								moveDirection;						// ĳ���Ͱ� ���� �̵��ϰ� �ִ� ������ ������
	int								beforeMoveDirection;				// �̰� ������ ���� �浹�ΰ�� ���� ������ ������
	CCSprite*						character;
	void moveCharacter(float);
	void createCharacter();

	/* touch										: Daun */
	void ccTouchEnded(CCTouch *, CCEvent* );
	bool ccTouchBegan(CCTouch *, CCEvent* );
	void onEnter();

	/* pause										: Daun */
	CCPoint							pauseBtnPosition;					// �Ͻ����� ��ư�� ��ġ
	CCSprite *						btnPause;							// �Ͻ����� �̹���

	/* etc											: Daun */
	int								checkCrash;							// ĳ������ �浹 ���� �Ǵ�
	CCDirector*						pDirector;




	/*												: pineoc */
	CCTMXObjectGroup *				foods;							// group for foods object
	CCArray*						tomakeFood;						// �������ϴ� ������� ���, array that have to make food ingrediant list
	CCArray*						onCheckFoodDisplay;				// ���� ������ �Ծ����� �ȸԾ����� üũ�� �迭,	
	void createFood();												//food create item, (point, imageName)
	bool checkDup(CCSprite*);										// check duplication about tile 
	void updateFoodSprte(float dt);
	void followCharacter(float);
	void check_counter(float);
	void createCounter();
	void go_endResultScene();
	void createFoodShelf();
	void checkFoodToEnd();											// check food for ending
	void checkFollowFoodCollision(float);
	void goMainScene();
	
	// array for check when character eat the food ingrediant
	CCArray*						foodSpriteArray;				// array for save the food sprite
	CCArray*						foodFollowArray;				// array for follow character
	int								foodcount;						// for food count
	int								foodFollowCnt;
	CCPoint							beforeMoveCharPoint[10];
	CCSprite*						counter;
	CCPoint							counterPoint;

	std::string						result;
	int								stageidx;





	/*												: jiyoon*/
	CCMenu*							PauseMenu;						// pause button menu
	CCPoint							itemPosition;
	CCSprite*						item1,
			*						item2, 
			*						item3, 
			*						item4;
	CCAnimate*						animate;
	CCAction *						rep;
	
	void doPop(CCObject* pSender);									//creat popup
	void doNotification(CCObject *obj);
	
	void createItem1();
	void createItem2();
	void createItem3();
	void createItem4();
	
	void check_item(float dt);										//check collision between item and character

	bool isPause;													//status of movingObstacle

	void stopObstacle();											//pauseObstacle
	void resumeObstacle();											//resume Obstacle
};

#endif  // __GAME_SCENE_H__