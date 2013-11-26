#include "userData.h"

userData *userData::_instance = NULL;

userData::userData()
{
	// CCUserDefault�ν��Ͻ��� �����ɴϴ�.
	// ������ 5���� Ÿ�Կ� ���� �б�/���⸦ �����մϴ�.
	// bool, int, float, double, string

	CCUserDefault *pUserDefault = CCUserDefault::sharedUserDefault();

	// �� �ɼ��� ���¸� �о�ɴϴ�.
	// ���ڰ��� 1:KEY, 2: dEFAULT VALUE�ε�
	// ���� xml���Ͽ� �ش� KEY�� �������� ������, �ι�° ���ڰ��� ���ϵ˴ϴ�.
	BGMONOFF = pUserDefault->getBoolForKey(gOptionKey[BGMSOUND],true);
	EFFECTONOFF = pUserDefault->getBoolForKey(gOptionKey[EFFECTSOUND],true);
	curStage = pUserDefault->getIntegerForKey(gCurKey,10);

	 /*
     * �ٸ� Ÿ�Կ� ���ؼ� ���÷� �߰��մϴ�.
     * string   : pUserDefault->getStringForKey("StringKey", "cozdebrainpower");
     * int      : pUserDefault->getIntegerForKey("IntegerKey", 10);
     * float    : pUserDefault->getFloatForKey("FloatKey", 1.5f);
     * double   : pUserDefault->getDoubleForKey("DoubleKey", 4.5);
     */
}

userData::~userData()
{}

// ����� �ɹ� ���� �ɼǰ��� ���� ���Ͽ� �����մϴ�.
void userData::setOption()
{
	CCUserDefault *pUserDefault = CCUserDefault::sharedUserDefault();

	pUserDefault->setBoolForKey(gOptionKey[BGMSOUND],BGMONOFF);
	pUserDefault->setBoolForKey(gOptionKey[EFFECTSOUND],EFFECTONOFF);
	pUserDefault->setIntegerForKey(gCurKey,curStage);
	// xml file�� ����
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

