#include "userData.h"

userData *userData::_instance = NULL;

userData::userData()
{
	// CCUserDefault인스턴스를 업더옵니다.
	// 다음의 5가지 타입에 대해 읽기/쓰기를 지원합니다.
	// bool, int, float, double, string

	CCUserDefault *pUserDefault = CCUserDefault::sharedUserDefault();

	// 각 옵션의 상태를 읽어옵니다.
	// 인자값은 1:KEY, 2: dEFAULT VALUE인데
	// 설정 xml파일에 해당 KEY가 존재하지 않으면, 두번째 인자값이 리턴됩니다.
	BGMONOFF = pUserDefault->getBoolForKey(gOptionKey[BGMSOUND],true);
	EFFECTONOFF = pUserDefault->getBoolForKey(gOptionKey[EFFECTSOUND],true);
	curStage = pUserDefault->getIntegerForKey(gCurKey,10);

	 /*
     * 다른 타입에 대해서 예시로 추가합니다.
     * string   : pUserDefault->getStringForKey("StringKey", "cozdebrainpower");
     * int      : pUserDefault->getIntegerForKey("IntegerKey", 10);
     * float    : pUserDefault->getFloatForKey("FloatKey", 1.5f);
     * double   : pUserDefault->getDoubleForKey("DoubleKey", 4.5);
     */
}

userData::~userData()
{}

// 변경된 맴버 변수 옵션값을 설정 파일에 저장합니다.
void userData::setOption()
{
	CCUserDefault *pUserDefault = CCUserDefault::sharedUserDefault();

	pUserDefault->setBoolForKey(gOptionKey[BGMSOUND],BGMONOFF);
	pUserDefault->setBoolForKey(gOptionKey[EFFECTSOUND],EFFECTONOFF);
	pUserDefault->setIntegerForKey(gCurKey,curStage);
	// xml file에 저장
	pUserDefault->flush();
}

void userData::setBGM(bool chk){this->BGMONOFF = chk; }
void userData::setEFFECT(bool chk){ this->EFFECTONOFF = chk;}

bool userData::getBGM() { return BGMONOFF; }
bool userData::getEFFECT(){ return EFFECTONOFF; }

void userData::setCurStage(int idx)
{
	this->curStage = idx;
}
int userData::getCurStage()
{
	return curStage;
}

