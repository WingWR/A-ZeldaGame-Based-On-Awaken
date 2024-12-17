#include "Indoor.h"

Indoor::Indoor(Player* origin_player) {
	player = origin_player;
}

Scene* Indoor::createScene() {
	return Indoor::create();
}

bool Indoor::init() {
	if (!Scene::init()) {
		return false;
	}

	//��ȡ��Ļ�ߴ�
	visibleSize = Director::getInstance()->getVisibleSize();

	//��ʼ�����ڵ�ͼ
	this->LoadMap();

	//��ʼ�����λ��
	player->setPosition(0, 0);


	//��������������
	this->MainCameraFollowPlayer();

	return true;
}

void Indoor::LoadMap() {
	auto IndoorMap = TMXTiledMap::create("Maps/Indoors/InDoors.tmx");
	IndoorMap->setScale(1.0f);
	IndoorMap->setAnchorPoint(Vec2(0.5f, 0.5f));
	InitialObstacle(IndoorMap);

	this->addChild(IndoorMap);
}

void Indoor::InitialCamera() {
	camera = getDefaultCamera();    //��ȡĬ�����
}