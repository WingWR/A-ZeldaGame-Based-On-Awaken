#include "SetMap.h"

#define Derivation 243

USING_NS_CC;

Scene* SetMap::createScene() {
    return SetMap::create();
}

bool SetMap::init() {
    if (!Scene::init()) {
        return false;
    }

	this->LoadCameraToScene();    //��ʼ�������
	this->LoadMapToScene();    //���ص�ͼ������
	this->LoadBagToScene();    //���ر���������
	this->LoadPlayerToScene();    //������ҵ�����
	this->LoadMonsterRespawnToScene();    //���ع���ˢ�µ㵽����
	this->LoadNPCToScene();    //����npc������

	//��Ӽ��̼�����������M��С��ͼ
	_eventManager->AddKeyBoardListener(this, CC_CALLBACK_2(SetMap::KeyPressedForRevealMicroMap, this));
	//��Ӽ��̼�����������B�򿪱���
	_eventManager->AddKeyBoardListener(this, CC_CALLBACK_2(SetMap::KeyPressedForBag, this));
	//��Ӽ��̼�����������W/A/S/D��������ƶ�
	_eventManager->AddKeyBoardListener(this,
		CC_CALLBACK_2(SetMap::KeyPressedForPlayerMove, this),
		CC_CALLBACK_2(SetMap::KeyReleasedForPlayerMove, this));
	//��Ӽ��̼�����������I/J/K/L������ҹ���
	_eventManager->AddKeyBoardListener(this, CC_CALLBACK_2(SetMap::KeyPressedForPlayerAttack, this));

	this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���

    return true;
}

/****************************************************************/
	////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
SetMap::SetMap() {
	//��ȡ��Ļ�ߴ�
	VisibleSize = Director::getInstance()->getVisibleSize();

	_eventManager = EventManager::create();  // ��ʼ���¼�������
	_cameraManager = CameraManager::create();  // ��ʼ�������������
	_mapManager = MapManager::create();  // ��ʼ����ͼ������
}

void SetMap::LoadCameraToScene() {
	// ��ʼ������ͼ�������������������������
	_cameraManager->InitialMainCamera(this);

	// ��ʼ��С��ͼ�������������������������
	_cameraManager->InitialMicroCamera(this);
}

void SetMap::LoadMapToScene() {
	//��ͼ�ĳ������Ⱦ�Ϊ50��ÿ��ͼ�����ش�СΪ32�����Ե�ͼ��СΪ1600
	const int MapSize = 1600;

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
}

void SetMap::LoadBagToScene() {
	_bagManager = BagManager::getInstance();
	if (_bagManager->getParent() == nullptr)
	{
		PLAYER->addChild(_bagManager);
	}
}

void SetMap::LoadPlayerToScene() {
	// lq�ӵĵ���С��
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, VisibleSize.width / 2, VisibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 192, 1);

	// ����ҵ����ͼ���˴�Ϊ0����ʾ�������ʼ�����ͼ
	_mapManager->GetTiledMap(0)->addChild(PLAYER);
}

void SetMap::LoadMonsterRespawnToScene() {
	// �ӹ�
	_monsterRespawn = new MonsterRespawn(PLAYER, this);

	// ���ֵ����ɫ
	PLAYER->InitMonster(_monsterRespawn->GetMonster());
}

void SetMap::LoadNPCToScene() {
	// �Ӹ�npc
	npc1 = new NPC("npc1", VisibleSize.width / 2, VisibleSize.height / 2 - 200, 1.0f, this, PLAYER);
	npc1->scheduleUpdate();
}

/****************************************************************/
	////////////////����Ϊ�����������ı��������й��ܺ���/////////////////
void SetMap::CameraFollowController() {
	// ע������¼������ڿ������������
	if (_cameraManager->IsInMicroMap()) {
		this->MicroCameraFollowPlayer();    //ע��С��ͼ�����������ҵĺ���
	}
	else {
		this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���
	}
}

void SetMap::MainCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMainMap = 600.0f;

	//ÿ�ν�������ͼʱ�������������λ������Ϊ���λ��
	Vec2 playPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playPosition, InitCameraZinMainMap);

	//����������¼������ڿ���������߶�
	_eventManager->AddMouseListener(this, [=](EventMouse* event) {
		float ScrollSpeed = 40.0f;
		MouseScrollForCameraZoom(event, _cameraManager->GetMainCamera(), 600.0f, 200.0f, ScrollSpeed);
		});

	// �������������ʵʱ��������
	schedule([=](float dt) {
		float updatedCameraZ = _cameraManager->GetMainCamera()->getPosition3D().z;    //��ȡ������ĸ߶�
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //��ȡ���λ��
		_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, updatedCameraZ);    //���������λ��
		}, "camera_update_key");
}

void SetMap::MicroCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMicroMap = 2000.0f;

	// ÿ�ν���С��ͼʱ����С�������λ����������λ��
	Vec2 centerPosition(1200, 1200);
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), centerPosition, InitCameraZinMicroMap);

	//����������¼������ڿ���������߶�
	_eventManager->AddMouseListener(this, [=](EventMouse* event) {
		float ScrollSpeed = 40.0f;
		MouseScrollForCameraZoom(event, _cameraManager->GetMainCamera(), 3600.0f, 1200.0f, ScrollSpeed);
		});

	// ���ü��̼���������������ƶ�
	_eventManager->AddKeyBoardListener(this, [=](EventKeyboard::KeyCode keyCode, Event* event) {
		float ScrollSpeed = 40.0f;
		KeyPressedForMicroMapMove(keyCode, event, _cameraManager->GetMicroCamera(), 2400.0f, -2400.0f, 2400.0f, -2400.0f, ScrollSpeed * 10);
		});
}

void SetMap::UnlockMapTeleport() {
	// ����������
	if (PLAYER->isTrigger(_mapManager->GetTeleportPosition(_mapManager->GetPlayerInWhichMap()))) {
		_mapManager->SetIsRegionRevealedTrue();
	}
}

void SetMap::TeleportPlayer(int MapID) {
	// �������
	if (_mapManager->GetTeleportPosition(MapID) != Vec2(0, 0)) {
		PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
		this->unscheduleAllCallbacks();  // ֹͣ���ж�ʱ��
		PLAYER->mySprite->setPosition(_mapManager->GetTeleportPosition(MapID));
	}
}

/**********************************************************************/
////////////////����Ϊ�������������������صĻص�����/////////////////
void SetMap::KeyPressedForRevealMicroMap(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		//С��ͼ����ʾ��ɫ��Ч�����ж����鷴ת
		_mapManager->ReverseIsBlackFogVisible();

		// ����С��ͼ�к�ɫ�����ʾ
		_mapManager->SetBlackFogInMicroMap();

		this->CameraFollowController();    //ע�������������ҵĺ���
		/*�˴��л�С��ͼ��ʾ������С��ͼʱ�������س�ʼ��ͼ���˳�С��ͼ֮������ʾ��ʼ��ͼ
		  ������ڽ���С��ͼ֮ǰ����ͣ��Ϸ���˳�С��ͼ֮���ٻָ���Ϸ����ֹ����ڴ򿪵�ͼ��ʱ��������*/
		if (_cameraManager->IsInMicroMap()) {
			//����С��ͼ��ͣ��Ϸ
			Director::getInstance()->pause();     // ��ͣ��Ϸ
			_cameraManager->GetMicroCamera()->setVisible(true);     //��С��ͼ�������ʾ
			_cameraManager->GetMainCamera()->setVisible(false);    //����ʼ���������
		}
		else {
			// �ָ�����ͼ��Ӧ��������߼�
			_cameraManager->GetMicroCamera()->setVisible(false);    //��С��ͼ���������
			_cameraManager->GetMainCamera()->setVisible(true);    //����ʼ�������ʾ
			Director::getInstance()->resume();    //�˳�С��ͼ�ָ���Ϸ
		}
	}
}

void SetMap::KeyPressedForBag(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_B) {
		if (BagManager::getInstance()->isBagVisible())
			// ���ر���
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// �򿪱���
			BagManager::getInstance()->showBag(*PLAYER);
	}
}

void SetMap::KeyPressedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
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
}
void SetMap::KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
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
void SetMap::HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction) {
	Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

	// ���Ŀ��λ���Ƿ���ƶ�
	/*if (IsMoveable(targetPosition))*/ {
		if (!isKeyPressed[keyIndex]) {
			isKeyPressed[keyIndex] = true;
			PLAYER->Move(direction);
			this->schedule([=](float dt) {
				PLAYER->Move(direction);
				}, 0.8f, scheduleKey);
		}
	}
}

void SetMap::KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event) {
	/* ����:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I) {
		PLAYER->Attack(UP, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
		PLAYER->Attack(DOWN, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		PLAYER->Attack(LEFT, _monsterRespawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		PLAYER->Attack(RIGHT, _monsterRespawn->GetMonster());
	}
}

void SetMap::KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event) {
	/* npc���� */
	if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		npc1->Chat();
	}
}

void SetMap::MouseScrollForCameraZoom(EventMouse* event,Camera* camera,float MaxHeight,float MinHeight,float ScrollSpeed) {
	Vec3 cameraPosition = camera->getPosition3D();
	float ScrollY = event->getScrollY();

	//ͨ���������룬����������߶�
	cameraPosition.z += ScrollY * ScrollSpeed;

	// ���� Z ֵ��Χ
	cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // ���߶�
	cameraPosition.z = std::max(cameraPosition.z, MinHeight); // ��С�߶�
	camera->setPosition3D(cameraPosition);
}

void SetMap::KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed) {
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