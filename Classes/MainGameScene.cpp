#include "MainGameScene.h"
#include "NPC.h"
#define Derivation 243

USING_NS_CC;

Scene* MainGameScene::createScene() {
	return MainGameScene::create();
}

Scene* MainGameScene::createScene(int _ODorID, int NPC_choice, int Monster_choice) {
	MainGameScene* scene = new MainGameScene(_ODorID, NPC_choice, Monster_choice);
	if (scene && scene->init()) {

	}
	else {
		delete scene;
		scene = nullptr;
	}
	return scene;
}

bool MainGameScene::init() {
	if (!Scene::init()) {
		return false;
	}

	this->LoadMapToScene();       //���ص�ͼ������
	this->LoadCameraToScene();    //��ʼ�������
	this->LoadPlayerToScene();    //������ҵ�����
	this->LoadMonsterRespawnToScene();    //���ع���ˢ�µ㵽����
	this->LoadNPCToScene();    //����npc������
	this->LoadBagToScene();    //���ر���������
	this->LoadBackgroundMusicToScene();    //���ر������ֵ�����

	//��Ӽ��̼������������̻
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(MainGameScene::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(MainGameScene::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

	//�������������������
	_mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseScroll = CC_CALLBACK_1(MainGameScene::MouseScroll, this);
	_mouseListener->onMouseDown = CC_CALLBACK_1(MainGameScene::MouseClicked, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

	this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���

	return true;
}

/****************************************************************/
////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
MainGameScene::MainGameScene(int _ODorID, int NPC_choice, int Monster_choice) {
	// ��ʼ����������
	DoorID = _ODorID;
	_NPC_choice = NPC_choice;
	_Monster_choice = Monster_choice;
	//��ȡ��Ļ�ߴ�
	VisibleSize = Director::getInstance()->getVisibleSize();

	_cameraManager = CameraManager::create();    // ��ʼ�������������
	_mapManager = MapManager::create();    // ��ʼ����ͼ������
	_bagManager = BagManager::getInstance();     // ��ʼ������������
	_musicManager = music::getInstance();    // ��ʼ���������ֹ�����
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
	if (DoorID == 0) {
		this->LoadOutDoorMapToScene();    //�����⾰��ͼ
	}
	else if (DoorID == 1) {
		this->LoadInDoorMapToScene();     //�������ڵ�ͼ
	}
	else if (DoorID == 2) {
		this->LoadFightMapToScene();     //����ս����ͼ
	}

	// ����ͼ��������ӵ�������
	this->addChild(_mapManager);
}
void MainGameScene::LoadOutDoorMapToScene() {
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

	//��ʼ��С��ͼ�к�ɫ�����ʾ
	_mapManager->SetBlackFogInMicroMap();
}
void MainGameScene::LoadInDoorMapToScene() {
	// �����ڵ�ͼ��ӵ�������
	_mapManager->InitialMap("Maps/Indoors/InDoors.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2), this);
}
void MainGameScene::LoadFightMapToScene() {
	// ��ս����ͼ��ӵ�������
	_mapManager->InitialMap("Maps/BossFight/BossRoom.tmx", Vec2(VisibleSize.width / 2, VisibleSize.height / 2), this);
}

void MainGameScene::LoadBagToScene() {
	if (_bagManager->getParent() == nullptr)
	{
		this->addChild(_bagManager);
	}
}

void MainGameScene::LoadPlayerToScene() {
	// ���
	float PlayerX;
	float PlayerY;
	if (DoorID == 0) {
		PlayerX = VisibleSize.width / 2 - 365;
		PlayerY = VisibleSize.height / 2 + 650;
	}
	else if (DoorID == 1) {
		PlayerX = 800;
		PlayerY = 1000;
	}
	else if (DoorID == 2) {
		PlayerX = VisibleSize.width / 2;
		PlayerY = VisibleSize.height / 2;
	}

	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, PlayerX, PlayerY, 0.5f, 100, 50, 30, 300, 10, 192, 1);
	
	this->schedule([=](float dt) {
		for (auto npc : _npcManager->visitNPC()) {
			PLAYER->preventOverlap(PLAYER, npc);
		}
		}, 0.001f, "player_check_collision_scheduler");
	
}

void MainGameScene::LoadMonsterRespawnToScene() {
	// �ӹ�
	_monsterRespawn = new MonsterRespawn(PLAYER, this, _mapManager, _Monster_choice, _bagManager);
	
	// ���ֵ����ɫ
	PLAYER->Init(_monsterRespawn->GetMonster(), _mapManager);
}

void MainGameScene::LoadNPCToScene() {
	// NPC������
	_npcManager = new NPCManager(PLAYER, _bagManager, this, _NPC_choice);
}

void MainGameScene::LoadBackgroundMusicToScene() {
	if (_musicManager->getInstance() == nullptr) {
		this->addChild(_musicManager);
	}

	_musicManager->stopBackgroundMusic();
	if (DoorID == 2)
		_musicManager->playBackgroundMusic("music/fight.mp3");
	else
		_musicManager->playBackgroundMusic("music/peace.mp3");
}
/****************************************************************/
////////////////����Ϊ�����������ı��������й��ܺ���/////////////
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
		_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, updatedCameraZ);    //���������λ��
		_mapManager->PlayerPositionInWhichMap(playerPosition);    //����������ڵ�ͼ
		}, "camera_update_key");
}

void MainGameScene::MicroCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMicroMap = 1200.0f;

	// ÿ�ν���С��ͼʱ����С�������λ���������λ��
	auto PlayerPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMicroCamera(), PlayerPosition, InitCameraZinMicroMap);
}

void MainGameScene::UnlockMapTeleport() {
	// ����������
	if (PLAYER->mySprite->getPosition().distance(_mapManager->GetTeleportPosition(_mapManager->GetPlayerInWhichMap())) < 70.0f
		&& _mapManager->GetIsRegionRevealed(_mapManager->GetPlayerInWhichMap()) == false) {
		_mapManager->SetIsRegionRevealedTrue();
	}
}

void MainGameScene::TeleportPlayer(int MapID) {
	// �������
	if (_mapManager->GetTeleportPosition(MapID) != Vec2(0, 0)) {
		PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
		this->unscheduleAllCallbacks();  // ֹͣ���ж�ʱ��
		Vec2 playerPosition = PLAYER->mySprite->getPosition();
		PLAYER->mySprite->setPosition(_mapManager->GetTeleportPosition(MapID));
		PLAYER->ChangeXY(_mapManager->GetTeleportPosition(MapID) - playerPosition);
	}
}

void MainGameScene::ChangeScene(const int SceneName, const int NPCIndex, const int MonsterIndex) {
	if (DoorID == 0) { // �����л�������
		this->pause();
        auto Transition = TransitionFadeTR::create(0.5f, MainGameScene::createScene(SceneName, NPCIndex, MonsterIndex));
        Director::getInstance()->pushScene(Transition);
    } else { // ������һ������
		// ���ص����ⳡ��
		Director::getInstance()->popScene();

		_musicManager->stopBackgroundMusic();
		_musicManager->playBackgroundMusic("music/peace.mp3");

		// �ָ���һ����������Ϊ
		auto outdoorScene = dynamic_cast<MainGameScene*>(Director::getInstance()->getRunningScene());
		if (outdoorScene) {
			outdoorScene->resume();
		}
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
			_cameraManager->SwitchToMainCamera();    //�л����������
		}
		else {
			//����С��ͼ��ͣ��Ϸ
			_cameraManager->SwitchToMicroCamera();    //�л���С�����
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
	int speed = PLAYER->getSpeed();
	/* �ƶ�:W/S/A/D */
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (PLAYER->canMove) {
			PLAYER->ChangeIsMoving();
			HandlePlayerMove(Vec2(0, speed), 0, "MoveUP", UP);
		}
		
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (PLAYER->canMove) {
			PLAYER->ChangeIsMoving();
			HandlePlayerMove(Vec2(0, -speed), 1, "MoveDOWN", DOWN);
		}
		
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (PLAYER->canMove) {
			PLAYER->ChangeIsMoving();
			HandlePlayerMove(Vec2(-speed, 0), 2, "MoveLEFT", LEFT);
		}
		
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (PLAYER->canMove) {
			PLAYER->ChangeIsMoving();
			HandlePlayerMove(Vec2(speed, 0), 3, "MoveRIGHT", RIGHT);
		}
		
	}

	Vec2 playerPosition = PLAYER->mySprite->getPosition();
	_cameraManager->UpdateCameraPosition(_cameraManager->GetMainCamera(), playerPosition, _cameraManager->GetMainCamera()->getPosition3D().z);
}
void MainGameScene::KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (isKeyPressed[0]) {
			isKeyPressed[0] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			PLAYER->ChangeIsMoving();
			this->unschedule("MoveUP");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (isKeyPressed[1]) {
			isKeyPressed[1] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			PLAYER->ChangeIsMoving();
			this->unschedule("MoveDOWN");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (isKeyPressed[2]) {
			isKeyPressed[2] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			PLAYER->ChangeIsMoving();
			this->unschedule("MoveLEFT");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (isKeyPressed[3]) {
			isKeyPressed[3] = false;
			PLAYER->mySprite->stopAllActions();  // ֹͣ��ǰ�����ж���
			PLAYER->ChangeIsMoving();
			this->unschedule("MoveRIGHT");
		}
	}
}
void MainGameScene::HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction) {
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

void MainGameScene::KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event) {
	static bool canAttack = true;
	
	/* ����:J */
	if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		if (canAttack) {
			canAttack = false; 
			PLAYER->Attack(_monsterRespawn->GetMonster());

			this->scheduleOnce([&](float dt) {
				canAttack = true; // 2���ָ�����״̬
				}, 0.4f, "attack_cooldown_timer");
		}
		else {
		}
	}
	else if(keyCode == EventKeyboard::KeyCode::KEY_K) {
		if (canAttack) {
			canAttack = false;
			PLAYER->Skill(1,_monsterRespawn->GetMonster());

			this->scheduleOnce([&](float dt) {
				canAttack = true; // 2���ָ�����״̬
				}, 3.0f, "attack_cooldown_timer");
		}
		else {
		}
		
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		if (canAttack) {
			canAttack = false;
			PLAYER->Skill(2,_monsterRespawn->GetMonster());

			this->scheduleOnce([&](float dt) {
				canAttack = true; // 2���ָ�����״̬
				}, 3.0f, "attack_cooldown_timer");
		}
		else {
		}
	}
}

void MainGameScene::KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		if (_npcManager->getChattingStates())
			return;

		/* npc���� */
		_npcManager->checkTriggers();
		
	}
}

void MainGameScene::KeyPressedForUnlockTeleport(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		//�������ڴ�����Χ�ڣ������������
		if (_mapManager->IsTeleportUnlockable(PLAYER->mySprite->getPosition())) {
			this->UnlockMapTeleport();
		}
	}
}

void MainGameScene::KeyPressedForChangeScene(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		//�������ڴ�����Χ�ڣ��򴥷�����
		int SceneName = 0, NPCIndex = 0, MonsterIndex = 0;
		if (_mapManager->IsDoorIntoable(PLAYER->mySprite->getPosition(), SceneName, NPCIndex, MonsterIndex)) {
			this->ChangeScene(SceneName, NPCIndex, MonsterIndex);
		}
	}
}

void MainGameScene::KeyPressedForInteraction(EventKeyboard::KeyCode keyCode, Event* event) {

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

	currentPosition.y = std::min(currentPosition.y, MaxHeight);   // ������󳤶�
	currentPosition.y = std::max(currentPosition.y, MinHeight);   // ������С����

	// ���������λ��
	camera->setPosition3D(currentPosition);
}

void MainGameScene::KeyPressedForBackgroundMusic(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		if (_musicManager->isMusicPanelOpen()) {
			_musicManager->closeMusicPanel();
		}
		else {
			_musicManager->openMusicPanel(PLAYER);
		}
	}
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
		if (keyCode == EventKeyboard::KeyCode::KEY_J) {
			KeyPressedForPlayerAttack(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_C) {
			KeyPressedForNPCInteract(keyCode, event);
			KeyPressedForUnlockTeleport(keyCode, event);
			KeyPressedForChangeScene(keyCode, event);
			KeyPressedForInteraction(keyCode, event);
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
			KeyPressedForBackgroundMusic(keyCode,event);
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
	// ��ȡ�����λ��
	Vec2 MousePosition = event->getLocationInView();

	// ת����Ļ���굽��������
	Vec2 ScenePosition = ScreenToScene(MousePosition);

	CCLOG("Scene Position: x = %f, y = %f", ScenePosition.x, ScenePosition.y);

	for (int i = 0; i < 5; i++) {         // ������������ţ�˳����RebirthTemple->volcano->SnowyWinter->DeathDesert->BrightForest
		if (_mapManager->GetTeleportPosition(i).distance(ScenePosition) < 50.0f) {// ������λ���ڴ���������Χ������
			if (_mapManager->GetIsRegionRevealed(i)) {
				// �������
				TeleportPlayer(i);
				break;
			}
			else {
				// ��ʾ��ʾ��
			}
		}
	}
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

Vec2 MainGameScene::ScreenToScene(const Vec2& screenPos) {
	// ��Ļ����תΪ��������
	// ��ȡ��Ļ�ֱ���
	cocos2d::Size screenSize = cocos2d::Director::getInstance()->getWinSize();
	float screenWidth = screenSize.width;
	float screenHeight = screenSize.height;

	// 1. ��Ļ����ת��Ϊ NDC ����
	float ndcX = (2.0f * screenPos.x) / screenWidth - 1.0f;
	float ndcY = (2.0f * screenPos.y) / screenHeight - 1.0f;

	// 2. NDC ת��Ϊ�ü��ռ�����
	cocos2d::Vec4 clipCoords(ndcX, ndcY, -1.0f, 1.0f);

	// 3. �ü��ռ䵽��ͼ�ռ�
	cocos2d::Mat4 invProjectionMatrix = _cameraManager->GetMicroCamera()->getProjectionMatrix();
	invProjectionMatrix.inverse();
	cocos2d::Vec4 viewCoords = invProjectionMatrix * clipCoords;

	// 4. ��һ����ͼ����
	viewCoords = viewCoords / viewCoords.w;

	// 5. ��ͼ�ռ䵽����ռ�
	cocos2d::Mat4 invViewMatrix = _cameraManager->GetMicroCamera()->getViewMatrix();
	invViewMatrix.inverse();
	cocos2d::Vec4 worldCoords = invViewMatrix * viewCoords;

	// 6. ���������ƽ�� (z = 0) ����
	cocos2d::Vec3 rayOrigin = _cameraManager->GetMicroCamera()->getPosition3D();
	cocos2d::Vec3 rayDir(worldCoords.x - rayOrigin.x, worldCoords.y - rayOrigin.y, worldCoords.z - rayOrigin.z);
	rayDir.normalize();

	float t = -rayOrigin.z / rayDir.z; // ƽ�� z = 0
	Vec3 outWorldPos = rayOrigin + rayDir * t;

	return Vec2(outWorldPos.x, outWorldPos.y);
}