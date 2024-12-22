#include "LoadingScene.h"
#include "ui/CocosGUI.h"
#include "MainGameScene.h"
#include "LearningScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene(int SceneChoice) {
	LoadingScene* scene = new LoadingScene(SceneChoice);
	if (scene && scene->init()) {
		
	}
	return scene;

}

bool LoadingScene::init() {
	if (!Scene::init()) {
		return false;
	}

	//��ȡ��Ļ��С
	VisibleSize = Director::getInstance()->getVisibleSize();

	// ����UI����
	this->CreateUI();

	//��ʼ��������Դ����
	int LoadedResourceCount = 0;
	int TotalResourceCount = Resources.size();

	//��Ӽ��ؽ�������������
	auto LoadingBar = ui::LoadingBar::create("UI/LoadingBar.png");
	LoadingBar->setPercent(0);    //��ʼ������Ϊ0
	LoadingBar->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height / 2 + 500));
	this->addChild(LoadingBar);

	// ���������
	this->schedule([this, LoadingBar](float delta) {
		LoadingBar->setPercent(i);
		i += 5.0f;
		if (i == 100) {
			if (_SceneChoice == 1) {
				auto ToChangeScene = MainGameScene::createScene();
				Director::getInstance()->replaceScene(ToChangeScene);
			}
			else if (_SceneChoice == 0) {
				auto LearningScene = LearningScene::createScene();
				Director::getInstance()->replaceScene(LearningScene);
			}
		}
        }, 0.1f, "check_loading_complete");

	return true;
}

LoadingScene::LoadingScene(int SceneChoice) {
	//��ʼ������ѡ��
	_SceneChoice = SceneChoice;
}

void LoadingScene::CreateUI() {
	//��Ӽ��ر���ͼ��������
	auto LoadingBackground = Sprite::create("UI/Loading.jpg");
	LoadingBackground->setPosition(VisibleSize.width / 2, VisibleSize.height / 2);
	this->addChild(LoadingBackground);
}