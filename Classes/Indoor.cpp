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

	return true;
}
