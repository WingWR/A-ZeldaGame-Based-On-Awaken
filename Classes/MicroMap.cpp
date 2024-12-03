#include "MicroMap.h"

USING_NS_CC;

bool MicroMap::init() {
	if (!Layer::init()) {
		return false;
	}

	// ��ȡ��Ļ�ߴ�
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//�������ͼ����
	auto WorldMap= Sprite::create("Maps/MicroMap/WorldMap.png");

	//���ô��ͼ�����λ�úʹ�С
	WorldMap->setPosition(visibleSize/2);
	WorldMap->setScale(3.0f);
		
	//��Ӵ��ͼ���鵽��
	this->addChild(WorldMap);

	Director::getInstance()->resume();

	return true;
}

void MicroMap::UpdatePlayerPos(Vec2& pos) {
	// ���������С��ͼ�ϵ�λ��
	PlayerPos = pos;

	// ɾ����һ�δ��������ͼ�꣨����еĻ���
	if (PlayerSprite) {
		PlayerSprite->removeFromParent();
	}

	// �����µ����ͼ��
	PlayerSprite = Sprite::create("Maps/MicroMap/PlayerMark.png");
	PlayerSprite->setPosition(PlayerPos);
	PlayerSprite->setScale(0.8f);

	//�����ͼ����ӵ���
	this->addChild(PlayerSprite);
}