#include "BackgroundMusic.h"

// 播放音乐
void music::playBackgroundMusic(string musicName)
{
	audioId = cocos2d::AudioEngine::play2d(musicName, true);
}

// 单例实例置为空指针
music* music:: _instance = nullptr;

// 获取单例实例 
music* music::getInstance()
{
	// 如果实例不存在，创建一个新的实例
	if (_instance == nullptr)
		_instance = new music();  
	return _instance;
}

// 打开音乐控制面板
void music::openMusicPanel(Player* player)
{
	is_open = true;
	// 创建音乐背景面板
	volumeBackground = Sprite::create("music/volumeBackground.png");
	volumeBackground->setAnchorPoint(Vec2(0.5, 0.5));
	volumeBackground->setPosition(Vec2(0, 0));
	player->mySprite->addChild(volumeBackground);

	// 创建一个Slider来控制音量
	volumeSlider = ui::Slider::create();
	volumeSlider->loadBarTexture("music/slider_bg.png");
	volumeSlider->loadSlidBallTextures("music/slider_ball_normal.png", "music/slider_ball_pressed.png", "");
	volumeSlider->loadProgressBarTexture("music/slider_progress.png");
	volumeSlider->setAnchorPoint(Vec2(0.5, 0.5));
	volumeSlider->setPosition(Vec2(volumeBackground->getContentSize().width / 2, volumeBackground->getContentSize().height / 2));
	volumeSlider->setPercent(volume * 100);
	volumeSlider->addEventListener([=](Ref* sender, ui::Slider::EventType type) {
		if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
			int percent = volumeSlider->getPercent();
			volume = percent / 100.0f;  // 音量值
			cocos2d::AudioEngine::setVolume(audioId, volume);  // 设置音量
		}
		});
	volumeBackground->addChild(volumeSlider);

	// 添加音乐图标
	auto soundSprite = Sprite::create("music/sound.png");
	soundSprite->setPosition(Vec2(volumeBackground->getContentSize().width / 2 - 175, volumeBackground->getContentSize().height / 2));
	volumeBackground->addChild(soundSprite);

	// 添加文字
	auto musicBackgroundLabel=Label::createWithTTF("Set Background Music", "fonts/arial.ttf", 32);
	musicBackgroundLabel->setTextColor(Color4B(255, 215, 0, 255));
	musicBackgroundLabel->setAnchorPoint(Vec2(0.5, 0.5));
	musicBackgroundLabel->setPosition(Vec2(volumeBackground->getContentSize().width / 2, volumeBackground->getContentSize().height / 2 + 50));
	volumeBackground->addChild(musicBackgroundLabel);
}

// 关闭音乐控制面板
void music::closeMusicPanel()
{
	// 将音乐控制面板设置为不可见
	is_open = false;
	// 删除子节点
	volumeBackground->removeFromParent();
	volumeBackground = nullptr;
	volumeSlider = nullptr;
}

void music::switchBackgroundMusic(string musicName)
{
	cocos2d::AudioEngine::pause(audioId);
	playBackgroundMusic(musicName);
}