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
	CCTMXLayer *backgroundLayer;
	void createObstacle(); // 장애물 생성 위함
	CCTMXLayer *metainfo; //은지만듬
	CCPoint originPos;

	CCPoint obstaclePosition;
	CCSprite *obstacle;
	CCTMXLayer *wall;

	//------------------------eunji gauge----------------------------//

	CCSprite *gaugeBar;
	CCSprite *gaugeHeart;

	int character_XP;

	//------------------------eunji end------------------------------//

	//----------------------- eunji moving obstacle ----------------//

	void moveObstacle(float); // 장애물 움직임 구현
	int countNum; // 프레임 수.
	bool checkObDirection;

	//----------------------- eunji end ----------------------------//

	// --------------------------------- Daun Start -------------------//

	CCTMXTiledMap *tileMap; // tileMap name to select stage
	void createCharacter();
	void ccTouchEnded(CCTouch *, CCEvent* );
	CCSprite        *character;
	bool ccTouchBegan(CCTouch *, CCEvent* );
	void onEnter();
	int checkCrash;
	void moveCharacter(float);
	CCDirector* pDirector;
	int moveDirection;
	CCPoint pauseBtnPosition;
	CCSprite *btnPause;
	// ------------------------------Daun End ----------------------//

	//-------------------------------pineoc's start------------------//
	void createFood(CCPoint,char*); //food create item, (point, imageName)
	bool checkDup(CCSprite*); // check duplication about tile 
	void updateFoodSprte(float dt);
	void followCharacter(float);
	void check_counter(float);
	void createCounter();
	void go_endResultScene();
	void createFoodShelf();
	CCTMXObjectGroup *foods; // group for foods object
	CCArray* tomakeFood; // 만들어야하는 음식재료 목록, array that have to make food ingrediant list
	CCArray* onCheckFoodDisplay; // 위에 음식을 먹었는지 안먹었는지 체크할 배열,
	// array for check when character eat the food ingrediant
	
	CCArray* foodSpriteArray; // array for save the food sprite
	CCArray* foodFollowArray; // array for follow character
	int foodcount; // for food count
	int foodFollowCnt;
	CCPoint beforeMoveCharPoint[10];
	CCSprite* counter;
	CCPoint counterPoint;

	int result;
	int stageidx;
	//-----------------------------------------------------------------//

	//--------------------JIYOON-------------------------------------
	void doPop(CCObject* pSender);	//creat popup
	void doNotification(CCObject *obj);
	CCMenu* PauseMenu;// pause button menu

	CCPoint itemPosition;
	CCSprite * item1,*item2, *item3, *item4;
	void createItem1();
	void createItem2();
	void createItem3();
	void createItem4();


	void check_item(float dt);	//check collision between item and character
	//------------------JIYOON END------------------------------------

};

#endif  // __GAME_SCENE_H__