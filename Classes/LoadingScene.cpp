#include "LoadingScene.h"
#include "ui/CocosGUI.h"
#include "MainGameScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene() {
	LoadingScene* scene = new LoadingScene();
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
			auto ToChangeScene = MainGameScene::createScene();
			Director::getInstance()->replaceScene(ToChangeScene);
		}
        }, 0.1f, "check_loading_complete");

	return true;
}

void LoadingScene::CreateUI() {
	//��Ӽ��ر���ͼ��������
	LoadingBackground = Sprite::create("UI/Loading.jpg");
	LoadingBackground->setPosition(VisibleSize.width / 2, VisibleSize.height / 2);
	this->addChild(LoadingBackground);
}