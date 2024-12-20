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
	// 音量背景面板
	cocos2d::Sprite* volumeBackground;  

	// 音量滑动条
	cocos2d::ui::Slider* volumeSlider;  

	// 音频 ID
	int audioId;  

	// 构造函数
	music() : volumeBackground(nullptr), volumeSlider(nullptr), audioId(-1)
	{
		is_open = false;
		volumeBackground = nullptr;
		volumeSlider = nullptr;
		volume = 1;
	} 

	// 静态成员变量，用于存储单例实例
	static music* _instance;

	// 音乐控制面板是否打开
	bool is_open;

	// 音量
	float volume;
public:
	// 播放音乐
	void playBackgroundMusic(string musicName); 

	// 获取单例实例 
	static music* getInstance(); 

	// 打开音乐控制面板
	void openMusicPanel(Player* player);

	// 关闭音乐控制面板
	void closeMusicPanel();

	// 判断音乐面板是否打开
	bool isMusicPanelOpen() { return is_open; }

	// 切换背景音乐
	void switchBackgroundMusic(string musicName);
};
#endif