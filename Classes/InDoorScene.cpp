#include "InDoorScene.h"

USING_NS_CC;

Scene* InDoorScene::createScene(Player* origin_player) {
	return InDoorScene::create();
}

bool InDoorScene::init() {
	if (!Scene::init()) {
		return false;
	}

	this->LoadMapToScene();    //���ص�ͼ������
	this->LoadCameraToScene();    //��ʼ�������
	this->LoadPlayerToScene();    //������ҵ�����
	this->LoadMonsterRespawnToScene();    //���ع���ˢ�µ㵽����
	this->LoadNPCToScene();    //����npc������
	this->LoadBagToScene();    //���ر���������
	this->LoadBackgroundMusicToScene();    //���ر������ֵ�����

	//��Ӽ��̼������������̻
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(InDoorScene::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(InDoorScene::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

	//�������������������
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseScroll = CC_CALLBACK_1(InDoorScene::MouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���

	return true;
}

/****************************************************************/
////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
InDoorScene::InDoorScene(Player* origin_player, string mapName, Vec2 playerPos) {
	//��ȡ��Ļ�ߴ�
	VisibleSize = Director::getInstance()->getVisibleSize();

	PLAYER = origin_player;    //�������ʵ��
	_mapName = mapName;    //�����ͼ����
	_playerPos = playerPos;    //������ҳ�ʼλ��

	_cameraManager = CameraManager::create();    // ��ʼ�������������
	_mapManager = MapManager::create();    // ��ʼ����ͼ������
	_bagManager = BagManager::getInstance();     // ��ʼ������������
	_musicManager = music::getInstance();    // ��ʼ���������ֹ�����
}

void InDoorScene::LoadMapToScene() {
	// ����ͼ��������ӵ�������
	this->addChild(_mapManager);

	// ��ʼ�����ڵ�ͼ������ӵ�ͼ��������
	_mapManager->InitialMap(_mapName, Vec2(VisibleSize.width / 2, VisibleSize.height / 2), this);
}

void InDoorScene::LoadPlayerToScene() {
	// ��������ӵ�������
	this->addChild(PLAYER);

	// ���������ʼλ��
	PLAYER->setPosition(_playerPos);
}

void InDoorScene::LoadMonsterRespawnToScene() {
	// �ӹ�
	_monsterRespawn = new MonsterRespawn(PLAYER, this);

	// ���ֵ����ɫ
	PLAYER->Init(_monsterRespawn->GetMonster(), _mapManager);
}

void InDoorScene::LoadNPCToScene() {
	// NPC������
	_npcManager = new NPCManager(PLAYER, _bagManager);

	// ���npc�Ƿ�����Ч������Χ��
	this->schedule([=](float dt) {
		for (auto npc : _npcManager->visitNPC()) {
			npc->update();
		}
		}, 0.2f, "npc_check_scheduler");
}