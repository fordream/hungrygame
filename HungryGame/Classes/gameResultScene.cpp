#include "gameResultScene.h"
#include "gameEndScene.h"
#include <algorithm>

gameResultScene::gameResultScene(std::string _result,int _stageidx)
{
	if(!CCLayerColor::initWithColor(ccc4(255,255,255,255)))
		return ;
	
	result = _result;
	stageidx = _stageidx;
	for(int i=0;i<10;i++)
		foodArrayForSprite[i]=" ";
	//check for result
	check_arr[0]=1;check_arr[1]=2;
	check_arr[2]=1000;check_arr[3]=1000;
	check_arr[4]=1000;check_arr[5]=1000;check_arr[6]=1000;check_arr[7]=1000;check_arr[8]=1000;check_arr[9]=1000;
	foodArraySpritecolor = new CCArray();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCSprite* background = CCSprite::create("img\\endResult\\end_bg.png");
	background->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(background,0);

	CCMenuItemImage *btnEnd = CCMenuItemImage::create(
		"img/endResult/main_btn_endgame.png", "img/endResult/main_btn_endgame_n.png", this, menu_selector(gameResultScene::menu_goEndScene));

	btnEnd->setPosition(ccp(size.width*0.8, size.height*0.1));

	CCMenu* endMenu = CCMenu::create(btnEnd, NULL);
	endMenu->setPosition(CCPointZero);

	this->addChild(endMenu, 2);
	//-------------------------------
	// put the image food ingrediant
	//-------------------------------
	foodArrayForSprite[0]="map/1.jpg";
	foodArrayForSprite[1]="map/2.png";
	foodArrayForSprite[2]="map/3.png";
	foodArrayForSprite[3]="map/4.png";

	this->make_foodSprite();
	this->check_food();

}


bool gameResultScene::init()
{
	return true;
}

void gameResultScene::check_food()
{
	int result_arr[10]={0,1000,1000,1000,1000,1000,1000,1000,1000,1000};
	//char* c=""; 
	//strcpy(c,result.c_str());
	//parsing
	std::string tokenkey = " ";
	result.erase(0,result.find(tokenkey)+tokenkey.length());// delete first space
	for(int i=0;i<10;i++)
	{
		size_t pos = result.find(tokenkey);
		result_arr[i] = atoi(result.substr(0,pos).c_str());
		result.erase(0,pos+tokenkey.length());
		if(atoi(result.c_str())==0)
			break;
	}
	selectionSort(result_arr,10);
	bool result = checkSame(check_arr,result_arr);
	
	if(result)
		resultOfStage=1;
	else
		resultOfStage=0;
}

void gameResultScene::make_foodSprite()
{//make food sprite using array foodArrayForSprite
	double x=0.3;
	double y=0.65;// for sprite position
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	for(int i=0;i<4;i++)
	{
		if(i==2 || i==4 || i== 6)
		{
			x=0.3;
			y=y-0.15;
		}
		else if(i==1 || i==3 || i==5)
		{	
			x=0.7;
		}
		CCSprite* foodsprite = CCSprite::create(foodArrayForSprite[i]);
		foodsprite->setAnchorPoint(ccp(0,0));
		foodsprite->setPosition(ccp(winSize.width*x,winSize.height*y));
		foodArraySpritecolor->addObject(foodsprite);
		//CCPoint fp = foodsprite->getPosition();
		this->addChild(foodsprite,1);
	}
}

void gameResultScene::menu_goEndScene(CCObject* pSender)
{
	CCScene *pScene = CCScene::create();
	gameEndScene *layer = new gameEndScene(resultOfStage,stageidx);
	layer->autorelease();
	pScene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(pScene);
}
//for sorting
void gameResultScene::selectionSort(int *list, int n)
{
    int i, j, indexMin, temp;
 
    for (i = 0; i < n - 1; i++)
    {
        indexMin = i;
        for (j = i + 1; j < n; j++)
        {
            if (list[j] < list[indexMin])
            {
                indexMin = j;
            }
        }
        temp = list[indexMin];
        list[indexMin] = list[i];
        list[i] = temp;
    }
}
//arr1 = have to eat, arr2 = eat
bool gameResultScene::checkSame(int *arr1,int *arr2)
{
	int count=0;
	for(int i=0;arr1[i]!=1000;i++)
	{
		if(arr1[i]==arr2[i])
		{
			CCPoint tmp = ((CCSprite*)(foodArraySpritecolor->objectAtIndex(i)))->getPosition();
			CCSprite* check = CCSprite::create("img/endResult/end_redCircle.png");
			check->setPosition(tmp);
			this->addChild(check);
		}
		else
		{
			count++;
		}
	}
	if(count==0) // if all matching, Success
		return true;
	else
		return false;
}