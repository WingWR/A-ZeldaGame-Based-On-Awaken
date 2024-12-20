#pragma once
#ifndef __BACKGROUNDMUSIC_H__
#define __BACKGROUNDMUSIC_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"
#include "string"
#include "Player.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;
using namespace std;


class music : public cocos2d::Node
{
private:
	// �����������
	cocos2d::Sprite* volumeBackground;  

	// ����������
	cocos2d::ui::Slider* volumeSlider;  

	// ��Ƶ ID
	int audioId;  

	// ���캯��
	music() : volumeBackground(nullptr), volumeSlider(nullptr), audioId(-1)
	{
		is_open = false;
		volumeBackground = nullptr;
		volumeSlider = nullptr;
		volume = 1;
	} 

	// ��̬��Ա���������ڴ洢����ʵ��
	static music* _instance;

	// ���ֿ�������Ƿ��
	bool is_open;

	// ����
	float volume;
public:
	// ��������
	void playBackgroundMusic(string musicName); 

	// ��ȡ����ʵ�� 
	static music* getInstance(); 

	// �����ֿ������
	void openMusicPanel(Player* player);

	// �ر����ֿ������
	void closeMusicPanel();

	// �ж���������Ƿ��
	bool isMusicPanelOpen() { return is_open; }

	// �л���������
	void switchBackgroundMusic(string musicName);
};
#endif