#include "BackgroundMusic.h"

// ��������
void music::playBackgroundMusic(string musicName)
{
	//audioId = cocos2d::experimental::AudioEngine::play2d(musicName, true);
	audioId = cocos2d::AudioEngine::play2d(musicName, true);
}

// ����ʵ����Ϊ��ָ��
music* music:: _instance = nullptr;

// ��ȡ����ʵ�� 
music* music::getInstance()
{
	// ���ʵ�������ڣ�����һ���µ�ʵ��
	if (_instance == nullptr)
		_instance = new music();  
	return _instance;
}

// �����ֿ������
void music::openMusicPanel(Player* player)
{
	is_open = true;
	// �������ֱ������
	volumeBackground = Sprite::create("music/volumeBackground.png");
	volumeBackground->setAnchorPoint(Vec2(0.5, 0.5));
	volumeBackground->setPosition(Vec2(0, 0));
	player->mySprite->addChild(volumeBackground);

	// ����һ��Slider����������
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
			volume = percent / 100.0f;  // ����ֵ
			//cocos2d::experimental::AudioEngine::setVolume(audioId, volume);  // ��������
			cocos2d::AudioEngine::setVolume(audioId, volume);  // ��������
		}
		});
	volumeBackground->addChild(volumeSlider);

	// �������ͼ��
	auto soundSprite = Sprite::create("music/sound.png");
	soundSprite->setPosition(Vec2(volumeBackground->getContentSize().width / 2 - 175, volumeBackground->getContentSize().height / 2));
	volumeBackground->addChild(soundSprite);

	// �������
	auto musicBackgroundLabel=Label::createWithTTF("Set Background Music", "fonts/arial.ttf", 32);
	musicBackgroundLabel->setTextColor(Color4B(255, 215, 0, 255));
	musicBackgroundLabel->setAnchorPoint(Vec2(0.5, 0.5));
	musicBackgroundLabel->setPosition(Vec2(volumeBackground->getContentSize().width / 2, volumeBackground->getContentSize().height / 2 + 50));
	volumeBackground->addChild(musicBackgroundLabel);
}

// �ر����ֿ������
void music::closeMusicPanel()
{
	// �����ֿ����������Ϊ���ɼ�
	is_open = false;
	// ɾ���ӽڵ�
	volumeBackground->removeFromParent();
	volumeBackground = nullptr;
	volumeSlider = nullptr;
}

void music::switchBackgroundMusic(string musicName)
{
	//cocos2d::experimental::AudioEngine::pause(audioId);
	cocos2d::AudioEngine::pause(audioId);
	playBackgroundMusic(musicName);
}