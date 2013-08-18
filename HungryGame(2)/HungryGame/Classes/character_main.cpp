#include "characterMain.h"
#include "character.h"

using namespace cocos2d;

CCScene* CharacterMain::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        CharacterMain *layer = CharacterMain::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterMain::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////


		CCMenuItemImage *pUp = CCMenuItemImage::create(
			"up.png","up_click.png",
			this,menu_selector(CharacterMain::selectMenu));
		pUp->setTag(0);
		CC_BREAK_IF(!pUp);
		CCMenuItemImage *pDown = CCMenuItemImage::create(
			"down.png", "down_click.png",
			this, menu_selector(CharacterMain::selectMenu));
		pDown->setTag(1);
		CC_BREAK_IF(!pDown);
		CCMenuItemImage *pLeft = CCMenuItemImage::create(
			"left.png", "left_click.png",
			this, menu_selector(CharacterMain::selectMenu));
		pLeft->setTag(2);
		CC_BREAK_IF(!pLeft);
		CCMenuItemImage *pRight = CCMenuItemImage::create(
			"right.png", "right_click.png",
			this, menu_selector(CharacterMain::selectMenu));
		pRight->setTag(3);
		CC_BREAK_IF(!pRight);


		pUp->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2 , 
			CCDirector::sharedDirector()->getWinSize().height/2));
		pDown->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2,
			CCDirector::sharedDirector()->getWinSize().height/2 - 50 ));
		pLeft->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2- 50,
			CCDirector::sharedDirector()->getWinSize().height/2 - 25));
		pRight->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width / 2 + 50,
			CCDirector::sharedDirector()->getWinSize().height/2 - 25));


		CCMenu *pDirectionMenu = CCMenu::create(pUp,pDown,pLeft,pRight,NULL);
		pDirectionMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pDirectionMenu);

		this->addChild(pDirectionMenu,3);



		pDaun = CCSprite::create("dog.png");
        CC_BREAK_IF(! pDaun);

        

		Daun = new Character(20,20);
		Daun->setPCharacter(pDaun);
		Daun->setX(40);
		Daun->setY(40);
		Daun->setSpeed(1);			// 움직일 시간
		// Place the sprite on the center of the screen
        pDaun->setPosition(ccp(Daun->getX(), Daun->getY()));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pDaun, 2);


		
   

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(CharacterMain::menuCloseCallback));
		
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("I'm Hungry!", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to HelloWorld layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSprite = CCSprite::create("HelloWorld.png");
        CC_BREAK_IF(! pSprite);

        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, 0);






        bRet = true;
    } while (0);

    return bRet;
}

void CharacterMain::selectMenu(CCObject* pSender)
{
	CCMenuItem *item = (CCMenuItem *)pSender;
	switch(item->getTag())
	{
	case 0:
		Daun->goUpPosition();
		break;
	case 1:
		Daun->goDownPosition();
		break;
	case 2:
		Daun->goLeftPosition();
		break;
	case 3:
		Daun->goRightPosition();
		break;
	}
}


void CharacterMain::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

