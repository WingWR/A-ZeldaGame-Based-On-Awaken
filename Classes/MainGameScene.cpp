#include "MainGameScene.h"

#define Derivation 243

USING_NS_CC;

Scene* MainGameScene::createScene() {
    return MainGameScene::create();
}

bool MainGameScene::init() {
    if (!Scene::init()) {
        return false;
    }

	this->LoadMapToScene();    //���ص�ͼ������
	this->LoadCameraToScene();    //��ʼ�������
	this->LoadPlayerToScene();    //������ҵ�����
	this->LoadBagToScene();    //���ر���������
	this->LoadMonsterRespawnToScene();    //���ع���ˢ�µ㵽����
	this->LoadNPCToScene();    //����npc������

	//��Ӽ��̼������������̻
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(MainGameScene::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGameScene::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

	//�������������������
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseUp = CC_CALLBACK_1(MainGameScene::MouseClicked, this);
	_mouseListener->onMouseScroll = CC_CALLBACK_1(MainGameScene::MouseScroll, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���

    return true;
}

/****************************************************************/
////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
MainGameScene::MainGameScene() {
	//��ȡ��Ļ�ߴ�
	VisibleSize = Director::getInstance()->getVisibleSize();

	_cameraManager = CameraManager::create();  // ��ʼ�������������
	_mapManager = MapManager::create();  // ��ʼ����ͼ������
}

void MainGameScene::LoadCameraToScene() {
	// ���������������ӵ�������
	this->addChild(_cameraManager); 

	// ��ʼ������ͼ�������������������������
	_cameraManager->InitialMainCamera(this);

	// ��ʼ��С��ͼ�������������������������
	_cameraManager->InitialMicroCamera(this);
}

void MainGameScene::LoadMapToScene() {
	//��ͼ�ĳ������Ⱦ�Ϊ50��ÿ��ͼ�����ش�СΪ32�����Ե�ͼ��СΪ1600
	const int MapSize = 1600;

	// ����ͼ��������ӵ�������
	this->addChild(_mapManager);

	// �����������ͼ������������
	_mapManager->InitialMap("Maps/RebirthTemple/RebirthTemple.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2), this);

	//����ɽ��ͼ������������
	_mapManager->InitialMap("Maps/volcano/volcano.tmx", Vec2(VisibleSize.width / 2 - MapSize - Derivation, VisibleSize.height / 2 + MapSize + Derivation), this);

	//��ѩ�ص�ͼ������������
	_mapManager->InitialMap("Maps/SnowyWinter/SnowyWinter.tmx", Vec2(VisibleSize.width / 2 + MapSize + Derivation, VisibleSize.height / 2 + MapSize + Derivation), this);

	//��ɳĮ��ͼ������������
	_mapManager->InitialMap("Maps/DeathDesert/DeathDesert.tmx", Vec2(VisibleSize.width / 2 + MapSize + Derivation, VisibleSize.height / 2 - MapSize - Derivation), this);

	//��ɭ�ֵ�ͼ������������
	_mapManager->InitialMap("Maps/BrightForest/BrightForest.tmx", Vec2(VisibleSize.width / 2 - MapSize - Derivation, VisibleSize.height / 2 - MapSize - Derivation), this);

	//����ɽѩ�ر߽������������
	_mapManager->InitialMap("Maps/Vol_Snow_Ecotonal/Vol_Snow_Ecotonal.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2 + MapSize + Derivation), this);

	//����ɽɭ�ֱ߽������������
	_mapManager->InitialMap("Maps/Vol_Forest_Ecotonal/Vol_Forest_Ecotonal.tmx", Vec2(VisibleSize.width / 2 - MapSize - Derivation, VisibleSize.height / 2), this);

	//��ɳĮѩ�ر߽������������
	_mapManager->InitialMap("Maps/Desert_Snow_Ecotonal/Desert_Snow_Ecotonal.tmx", Vec2(VisibleSize.width / 2 + MapSize + Derivation, VisibleSize.height / 2), this);

	//��ɭ��ɳĮ�߽������������
	_mapManager->InitialMap("Maps/Forest_Desert_Ecotonal/Forest_Desert_Ecotonal.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2 - MapSize - Derivation), this);

	//��ʼ��С��ͼ�к�ɫ�����ʾ
	_mapManager->SetBlackFogInMicroMap();    
}

void MainGameScene::LoadBagToScene() {
	_bagManager = BagManager::getInstance();
	if (_bagManager->getParent() == nullptr)
	{
		PLAYER->addChild(_bagManager);
	}
}

void MainGameScene::LoadPlayerToScene() {
	// ���
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, VisibleSize.width / 2, VisibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 192, 1);
}

void MainGameScene::LoadMonsterRespawnToScene() {
	// �ӹ�
	_monsterRespawn = new MonsterRespawn(PLAYER, this);

	// ���ֵ����ɫ
	PLAYER->InitMonster(_monsterRespawn->GetMonster());
}

void MainGameScene::LoadNPCToScene() {
	// NPC������
	_npcManager = new NPCManager(PLAYER, _bagManager);

	// �ڵ�ͼ�м���npc
	_npcManager->addNPC("npc1", VisibleSize.width / 2, VisibleSize.height / 2, 1.0f, this);

	// ���npc�Ƿ�����Ч������Χ��
	this->schedule([=](float dt) {
		for (auto npc : _npcManager->visitNPC()) {
			npc->update();
		}
		}, 0.2f, "npc_check_scheduler");
}

/****************************************************************/
	////////////////����Ϊ�����������ı��������й��ܺ���/////////////////
void MainGameScene::CameraFollowController() {
	// ע������¼������ڿ������������
	if (_cameraManager->IsInMicroMap()) {
		this->MicroCameraFollowPlayer();    //ע��С��ͼ�����������ҵĺ���
	}
	else {
		this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���
	}
}

void MainGameScene::MainCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMainMap = 600.0f;

	//ÿ�ν�������ͼʱ�������������λ������Ϊ���λ��
	Vec2 playPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playPosition, InitCameraZinMainMap);

	// �������������ʵʱ��������
	this->schedule([=](float dt) {
		float updatedCameraZ = _cameraManager->GetMainCamera()->getPosition3D().z;    //��ȡ������ĸ߶�
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //��ȡ���λ��
		_mapManager->PlayerPositionInWhichMap(playerPosition);    //��ȡ������ڵ�ͼ
		_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, updatedCameraZ);    //���������λ��
		CCLOG("Player Position: %f, %f", playerPosition.x, playerPosition.y);
		}, "camera_update_key");
}

void MainGameScene::MicroCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMicroMap = 2000.0f;

	// ÿ�ν���С��ͼʱ����С�������λ����������λ��
	Vec2 centerPosition(1200, 1200);
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMicroCamera(), centerPosition, InitCameraZinMicroMap);
}

void MainGameScene::UnlockMapTeleport() {
	// ����������
	if (PLAYER->isTrigger(_mapManager->GetTeleportPosition(_mapManager->GetPlayerInWhichMap()))) {
		_mapManager->SetIsRegionRevealedTrue();
	}
}

void MainGameScene::TeleportPlayer(int MapID) {
	// �������
	if (_mapManager->GetTeleportPosition(MapID) != Vec2(0, 0)) {
		PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
		this->unscheduleAllCallbacks();  // ֹͣ���ж�ʱ��
		PLAYER->mySprite->setPosition(_mapManager->GetTeleportPosition(MapID));
	}
}

/**********************************************************************/
////////////////����Ϊ�������������������صĻص�����/////////////////
void MainGameScene::KeyPressedForRevealMicroMap(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		//С��ͼ����ʾ��ɫ��Ч�����ж����鷴ת
		_mapManager->ReverseIsBlackFogVisible();
		// ����С��ͼ�к�ɫ�����ʾ
		_mapManager->SetBlackFogInMicroMap();

		/*�˴��л�С��ͼ��ʾ������С��ͼʱ�������س�ʼ��ͼ���˳�С��ͼ֮������ʾ��ʼ��ͼ
		  ������ڽ���С��ͼ֮ǰ����ͣ��Ϸ���˳�С��ͼ֮���ٻָ���Ϸ����ֹ����ڴ򿪵�ͼ��ʱ��������*/
		if (_cameraManager->IsInMicroMap()) {
			// �ָ�����ͼ��Ӧ��������߼�
			Director::getInstance()->resume();    //�˳�С��ͼ�ָ���Ϸ
			_cameraManager->SwitchToMainCamera();    //�л����������
		}
		else {
			//����С��ͼ��ͣ��Ϸ
			_cameraManager->SwitchToMicroCamera();    //�л���С�����
			Director::getInstance()->pause();     // ��ͣ��Ϸ	
		}

		this->CameraFollowController();    //ע�������������ҵĺ���
	}
}

void MainGameScene::KeyPressedForBag(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_B) {
		if (BagManager::getInstance()->isBagVisible())
			// ���ر���
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// �򿪱���
			BagManager::getInstance()->showBag(*PLAYER);
	}
}

void MainGameScene::KeyPressedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
	//int speed = 10;
	int speed = PLAYER->getSpeed();
	/* �ƶ�:W/S/A/D */
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		HandlePlayerMove(Vec2(0, speed), 0, "MoveUP", UP);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		HandlePlayerMove(Vec2(0, -speed), 1, "MoveDOWN", DOWN);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		HandlePlayerMove(Vec2(-speed, 0), 2, "MoveLEFT", LEFT);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		HandlePlayerMove(Vec2(speed, 0), 3, "MoveRIGHT", RIGHT);
	}

	Vec2 playerPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, _cameraManager->GetMainCamera()->getPosition3D().z);
}
void MainGameScene::KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (isKeyPressed[0]) {
			isKeyPressed[0] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			this->unschedule("MoveUP");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (isKeyPressed[1]) {
			isKeyPressed[1] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			this->unschedule("MoveDOWN");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (isKeyPressed[2]) {
			isKeyPressed[2] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			this->unschedule("MoveLEFT");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (isKeyPressed[3]) {
			isKeyPressed[3] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			this->unschedule("MoveRIGHT");
		}
	}
}
void MainGameScene::HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction) {
	Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

	// ���Ŀ��λ���Ƿ���ƶ�
	/*if (IsMoveable(targetPosition))*/ {
		CCLOG("Move  first %d", direction);
		if (!isKeyPressed[keyIndex]) {
			isKeyPressed[keyIndex] = true;
			PLAYER->Move(direction);
			this->schedule([=](float dt) {
				PLAYER->Move(direction);
				}, 0.8f, scheduleKey);
			CCLOG("Move %d", direction);
		}
	}
}

void MainGameScene::KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event) {
	/* ����:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I) {
		PLAYER->Attack(UP, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
		PLAYER->Attack(DOWN, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		CCLOG("into attack");
		PLAYER->Attack(LEFT, _monsterRespawn->GetMonster());
		CCLOG("out attack");
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		PLAYER->Attack(RIGHT, _monsterRespawn->GetMonster());
	}
}

void MainGameScene::KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event) {
	if (_npcManager->getChattingStates())
		return;
	/* npc���� */
	if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		_npcManager->checkTriggers();
	}
}

void MainGameScene::KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed) {
	Vec3 currentPosition = camera->getPosition3D();

	// ���ݷ���������������ƽ��
	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		currentPosition.y += ScrollSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		currentPosition.y -= ScrollSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		currentPosition.x -= ScrollSpeed;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		currentPosition.x += ScrollSpeed;
	}

	// ������������ƶ��߽磨��ֹԽ�磩
	currentPosition.x = std::min(currentPosition.x, MaxWidth);    // ���������
	currentPosition.x = std::max(currentPosition.x, MinWidth);    // ������С���

	currentPosition.y = std::min(currentPosition.y, MaxHeight);    // ������󳤶�
	currentPosition.y = std::max(currentPosition.y, MinHeight);     // ������С����

	// ���������λ��
	camera->setPosition3D(currentPosition);
}

void MainGameScene::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	// ����ͬ�İ���
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		KeyPressedForRevealMicroMap(keyCode, event);
	}
	if (!_cameraManager->IsInMicroMap()) {
		if (keyCode == EventKeyboard::KeyCode::KEY_B) {
			KeyPressedForBag(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W ||
			keyCode == EventKeyboard::KeyCode::KEY_A ||
			keyCode == EventKeyboard::KeyCode::KEY_S ||
			keyCode == EventKeyboard::KeyCode::KEY_D) {
			KeyPressedForPlayerMove(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_I ||
			keyCode == EventKeyboard::KeyCode::KEY_J ||
			keyCode == EventKeyboard::KeyCode::KEY_K ||
			keyCode == EventKeyboard::KeyCode::KEY_L) {
			KeyPressedForPlayerAttack(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_C) {
			KeyPressedForNPCInteract(keyCode, event);
		}
	}
	else {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW ||
			keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
			KeyPressedForMicroMapMove(keyCode, event, _cameraManager->GetMicroCamera(), 2400.0f, -2400.0f, 2400.0f, -2400.0f, 400.0f);
		}
	}
}

void MainGameScene::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	// ��������ƶ�
	if (keyCode == EventKeyboard::KeyCode::KEY_W ||
		keyCode == EventKeyboard::KeyCode::KEY_A ||
		keyCode == EventKeyboard::KeyCode::KEY_S ||
		keyCode == EventKeyboard::KeyCode::KEY_D) {
		KeyReleasedForPlayerMove(keyCode, event);
	}
}

void MainGameScene::MouseScrollForCameraZoom(EventMouse* event, Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed) {
	Vec3 cameraPosition = camera->getPosition3D();
	float ScrollY = event->getScrollY();

	//ͨ���������룬����������߶�
	cameraPosition.z += ScrollY * ScrollSpeed;

	// ���� Z ֵ��Χ
	cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // ���߶�
	cameraPosition.z = std::max(cameraPosition.z, MinHeight); // ��С�߶�
	camera->setPosition3D(cameraPosition);
}

void MainGameScene::MouseClickedForTeleport(EventMouse* event) {
	// ����С��ͼ�еĴ�����

	int MapID = _mapManager->GetPlayerInWhichMap();
			// �������
			TeleportPlayer(MapID);

}

void MainGameScene::MouseScroll(EventMouse* event) {
	if (_cameraManager->IsInMicroMap()) {
		MouseScrollForCameraZoom(event, _cameraManager->GetMicroCamera(), 3600.0f, 1200.0f, 400.0f);
	}
	else {
		MouseScrollForCameraZoom(event, _cameraManager->GetMainCamera(), 600.0f, 200.0f, 40.0f);
	}
}

void MainGameScene::MouseClicked(EventMouse* event) {
	if (_cameraManager->IsInMicroMap()) {
		MouseClickedForTeleport(event);
	}
}