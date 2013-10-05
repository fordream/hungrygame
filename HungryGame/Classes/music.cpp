/*
* volume 에 관한 정보를 가지고 있는 클래스입니다.
* 배경 음악 크기와 효과음 크기를 가집니다.

   This is class about volume size.
   It has background volume size and effect volume size.

   volume size is from 0 to 6.
*/

#include "music.h"
#include "userData.h"
/*
	constructor

	set background volume level and effect volume level to 3 as a default.
*/
music::music()
{
	setBgSoundVolume(3);
	setEffectSoundVolume(3);
}
/*
	Constructor
	volume(background sound level , effect sound level)

	set background volume level and effect volume level
*/
music::music(int BG, int EFFECT)
{
	setBgSoundVolume(BG);
	setEffectSoundVolume(EFFECT);
}

/*
	start background music
*/
void music::bgStart(char *musicName)
{
	if(userData::sharedInstance()->getBGM())
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
			musicName,	// 재생할 사운드 파일 이름
			true);			// 반복재생여부
}

/*
	stop background music
*/
void music::bgStop()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

/*
	pause background music
*/
void music::bgPause()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

/*
	restart background music
*/
void music::bgRestart()
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}


// effect sound start
void music::effectStart(char *effectName)
{
	if(userData::sharedInstance()->getEFFECT())
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
			effectName,	
			false);	

	// true로 설정하면 반복함
}




/*
	setEffectSoundVolume( effect volume level)

	set effect volume level.
*/
void music::setEffectSoundVolume(int EFFECT)
{
	effectSoundVolume = EFFECT;
}
/*
	getEffectSoundVolume()

	return now effect volume level.
*/
int music::getEffectSoundVolume()
{
	return effectSoundVolume;
}



void music::setBgSoundVolume(int BG)
{
	bgSoundVolume = BG;
}
int music::getBgSoundVolume()
{
	return bgSoundVolume;
}

bool music::effectSoundVolumeUp()
{
	effectSoundVolume ++;
	return true;
}
bool music::effectSoundVolumeDown()
{
	effectSoundVolume--;
	return true;
}

bool music::bgSoundVolumeUp()
{
	bgSoundVolume++;
	return true;
}
bool music::bgSoundVolumeDown()
{
	bgSoundVolume--;
	return true;
}