/** userData
*	this class is saving setting data
*	음악 배경음악 사운드 설정 등을 저장하는 클래스 입니다.
* Date											2013. 10. 06
* Latest										2013. 10. 06
* Made											Daun
* http://cozycoz.egloos.com/11046044
*/

#ifndef User_data_h
#define User_Data_h

#include "cocos2d.h"

using namespace cocos2d;

enum SETTINGSET
{
	BGMSOUND, EFFECTSOUND, OPTIONCNT
};
enum ONOFF
{
	OFF,ON
};
/*
CCUserDefault로 저장하기 위해서는 키가 필요합니다.

xml(Key:Value)로 저장됩니다.
옵션의 키로 사용될 문자열입니다.
*/
static const char gOptionKey[OPTIONCNT][32]=
{
	"BGMOption","EffectOption"
};

static const char* gCurKey=" ";



class userData
{
public:
	userData();
	~userData();

	

	static userData* sharedInstance(void)
	{
		if(_instance == NULL)
			_instance = new userData();
		return _instance;
	}

	static void release(void)
	{
		if(_instance != NULL)
			delete _instance;
		_instance = NULL;
	}

	// 옵션을 세팅하는 메소드입니다.
	void setOption(void);

	void setBGM(bool);
	void setEFFECT(bool);

	bool getBGM();
	bool getEFFECT();

	void setCurStage(int);
	int getCurStage();


private:
	static userData *_instance;
	bool BGMONOFF;
	bool EFFECTONOFF;
	int curStage;
};


#endif