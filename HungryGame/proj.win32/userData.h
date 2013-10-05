/** userData
*	this class is saving setting data
*	���� ������� ���� ���� ���� �����ϴ� Ŭ���� �Դϴ�.
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
CCUserDefault�� �����ϱ� ���ؼ��� Ű�� �ʿ��մϴ�.

xml(Key:Value)�� ����˴ϴ�.
�ɼ��� Ű�� ���� ���ڿ��Դϴ�.
*/
static const char gOptionKey[OPTIONCNT][32]=
{
	"BGMOption","EffectOption"
};




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

	// �ɼ��� �����ϴ� �޼ҵ��Դϴ�.
	void setOption(void);

	void setBGM(bool);
	void setEFFECT(bool);

	bool getBGM();
	bool getEFFECT();


private:
	static userData *_instance;
	bool BGMONOFF;
	bool EFFECTONOFF;
};


#endif