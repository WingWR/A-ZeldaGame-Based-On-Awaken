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

    PlayerInWhichMap = 0;     //��ʼ�����λ���ڳ�ʼ����

    IsMicroMapVisible = false;    //��ʼ��С��ͼ״̬����

    //��Ӽ��̼�����������M��С��ͼ
    auto KeyListener = EventListenerKeyboard::create();
    KeyListener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressedForMicroMap, this);
	KeyListener->onKeyReleased = CC_CALLBACK_2(SetMap::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

	//��ȡ��Ļ�ߴ�
	visibleSize = Director::getInstance()->getVisibleSize();

    /*��ʼ������ͼ�������С��ͼ�����*/
	this->InitialCamera();

    /*���س�ʼ��ͼ*/
    this->LoadMap();
  
	// lq�ӵĵ���С��
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 192, 1);
	// �ӹ�
	monster_respawn = new MonsterRespawn(PLAYER, this);
	// ���ֵ����ɫ
	PLAYER->InitMonster(monster_respawn->GetMonster());

	// �Ӹ�npc
	npc1 = new NPC("npc1", visibleSize.width / 2, visibleSize.height / 2 - 200, 1.0f, this, PLAYER);
	
	// ����
	BagManager* bagManager = BagManager::getInstance();
	if (bagManager->getParent() == nullptr)
		this->addChild(bagManager);
	///////////////////////

	this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���

    return true;
}

void SetMap::InitialCamera() {
	//��������ͼ�����
	camera = getDefaultCamera();

	//����С��ͼ�����
	camera_in_micro_map = Camera::createPerspective(60.0f,visibleSize.width / visibleSize.height, 100.0f, 4000.0f);

	// ��С��ͼ��������������
	camera_in_micro_map->setVisible(false);    //��ʼ����С��ͼ�����
	this->addChild(camera_in_micro_map);
}

void SetMap::createKeyboardListenerForCamera(Camera* camera, float MaxWidth, float MinWidth, float MaxHeigth, float MinHeigth, float moveSpeed) {
	auto keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		Vec3 currentPosition = camera->getPosition3D();

		// ����WASD�����������ƽ��
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			currentPosition.y += moveSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			currentPosition.y -= moveSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			currentPosition.x -= moveSpeed;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			currentPosition.x += moveSpeed;
			break;
		default:
			break;
		}

		// ������������ƶ��߽磨��ֹԽ�磩
		currentPosition.x = std::min(currentPosition.x, MaxWidth);    // ���������
		currentPosition.x = std::max(currentPosition.x, MinWidth);    // ������С���

		currentPosition.y = std::min(currentPosition.y, MaxHeigth);    // ������󳤶�
		currentPosition.y = std::max(currentPosition.y, MinHeigth);     // ������С����

		// ���������λ��
		camera->setPosition3D(currentPosition);
		};

	// ����������ӵ��¼�������
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

EventListenerMouse* SetMap::createMouseListenerForCameraScroll(Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed) {
	auto listener = EventListenerMouse::create();
	listener->onMouseScroll = [=](EventMouse* event) {
		Vec3 cameraPosition = camera->getPosition3D();
		float ScrollY = event->getScrollY();

		//ͨ���������룬����������߶�
		cameraPosition.z += ScrollY * ScrollSpeed;
        
		// ���� Z ֵ��Χ
		cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // ���߶�
		cameraPosition.z = std::max(cameraPosition.z, MinHeight); // ��С�߶�
		camera->setPosition3D(cameraPosition);
		};
	return listener;
}

void SetMap::UpdateCameraPosition(Camera* camera, Vec2& TargetPos, float Height) {
	camera->setPosition3D(Vec3(TargetPos.x, TargetPos.y, Height));
}

void SetMap::CameraFollowController() {
	// ������м�����
	if (mainMapListener) {
		_eventDispatcher->removeEventListener(mainMapListener);
		mainMapListener = nullptr;
	}
	if (microMapListener) {
		_eventDispatcher->removeEventListener(microMapListener);
		microMapListener = nullptr;
	}

	if (IsMicroMapVisible) {
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
	UpdateCameraPosition(camera, playPosition, InitCameraZinMainMap);
	// �򴴽���������ͼ������
	mainMapListener = createMouseListenerForCameraScroll(camera, 600.0f, 200.0f, ScrollSpeed);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mainMapListener, this);    // ��ȡ�¼�����������Ӽ�����

	// �������������ʵʱ��������
	schedule([=](float dt) {
		float updatedCameraZ = camera->getPosition3D().z;    //��ȡ������ĸ߶�
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //��ȡ���λ��
		this->UpdateCameraPosition(camera, playerPosition, updatedCameraZ);    //���������λ��
		}, "camera_update_key");
}

//�����Ļ��������ת������======================================================================================================
void SetMap::onMouseUp(cocos2d::EventMouse* event) {

	// ������¼�
	auto mouseEvent = static_cast<cocos2d::EventMouse*>(event);
	// ��ȡ���������λ��
	cocos2d::Vec2 TestclickPos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());
	// ��ȡ�����λ�ã���������ϵ��
	cocos2d::Vec2 clickPos = mouseEvent->getLocation();
	// ��ȡ���λ�ã���������ϵ��
	Vec2 playerPosition = PLAYER->mySprite->getPosition();
	// ������λ�ã���������ϵ��
	Vec2 playerPositionInWorld = convertToWorldSpace(playerPosition);
	// ������λ�ã���������ϵ��
	Vec2 playerPositionInWindow = convertToWindowSpace(playerPositionInWorld);
	// �������λ��ת��Ϊ��������ϵ
	//Vec2 clickPosInScene = this->camera->convertToNodeSpace(TestclickPos);
	CCLOG("TestMouse click position (window coordinates): (%f, %f)", TestclickPos.x, TestclickPos.y);
	CCLOG("Mouse click position (window coordinates): (%f, %f)", clickPos.x, clickPos.y);
	CCLOG("Player position (scene coordinates): (%f, %f)", playerPosition.x, playerPosition.y);
	CCLOG("Player position (window coordinates): (%f, %f)", playerPositionInWindow.x, playerPositionInWindow.y);
	//CCLOG("Mouse click position (scene coordinates): (%f, %f)", clickPosInScene.x, clickPosInScene.y);
	CCLOG("Player position (world coordinates): (%f, %f)", playerPositionInWorld.x, playerPositionInWorld.y);

}
//=======================================================================================================

void SetMap::MicroCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMicroMap = 2000.0f;

	// ÿ�ν���С��ͼʱ����С�������λ����������λ��
	Vec2 centerPosition(1200, 1200);
	UpdateCameraPosition(camera_in_micro_map, centerPosition, InitCameraZinMicroMap);

	// �򴴽�����С��ͼ������
	microMapListener = createMouseListenerForCameraScroll(camera_in_micro_map, 3600.0f, 1200.0f, ScrollSpeed );
	_eventDispatcher->addEventListenerWithSceneGraphPriority(microMapListener, camera_in_micro_map);    	// ��ȡ�¼�����������Ӽ�����

	//==========================================================================

	// ע��������¼�
	auto listener = cocos2d::EventListenerMouse::create();
	listener->onMouseUp = CC_CALLBACK_1(SetMap::onMouseUp, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//================================================================================

	// ���ü��̼���������������ƶ�
	createKeyboardListenerForCamera(camera_in_micro_map, 2400.0f, -2400.0f, 2400.0f, -2400.0f, ScrollSpeed * 10);
}

void SetMap::KeyPressedForMicroMap(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
		// �л�С��ͼ��ʾ״̬
		IsMicroMapVisible = !IsMicroMapVisible;

		//С��ͼ����ʾ��ɫ��Ч�����ж����鷴ת
		for (int i = 0; i < IsBlackFogVisible.size(); i++) {
			IsBlackFogVisible[i] = !IsBlackFogVisible[i];         
		}
		// ����С��ͼ�к�ɫ�����ʾ
		SetBlackFogInMicroMap();

		CameraFollowController();    //ע�������������ҵĺ���
		/*�˴��л�С��ͼ��ʾ������С��ͼʱ�������س�ʼ��ͼ���˳�С��ͼ֮������ʾ��ʼ��ͼ
		  ������ڽ���С��ͼ֮ǰ����ͣ��Ϸ���˳�С��ͼ֮���ٻָ���Ϸ����ֹ����ڴ򿪵�ͼ��ʱ��������*/
		if (IsMicroMapVisible) {
			//����С��ͼ��ͣ��Ϸ
			Director::getInstance()->pause();     // ��ͣ��Ϸ
			camera_in_micro_map->setVisible(true);     //��С��ͼ�������ʾ
			camera->setVisible(false);    //����ʼ���������

			// MicroMap->setVisible(IsMicroMapVisible);    //�л���ʾС��ͼ
		}
		else {
			//MicroMap->setVisible(IsMicroMapVisible);    //�л���ʾС��ͼ

			// �ָ�����ͼ��Ӧ��������߼�
			camera_in_micro_map->setVisible(false);    //��С��ͼ���������
			camera->setVisible(true);    //����ʼ�������ʾ
			Director::getInstance()->resume();    //�˳�С��ͼ�ָ���Ϸ
		}
	}

	//int speed = 10;
	int speed = PLAYER->getSpeed();
	/* ����:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I) {
		PLAYER->Attack(UP, monster_respawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
		PLAYER->Attack(DOWN, monster_respawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
		PLAYER->Attack(LEFT, monster_respawn->GetMonster());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
		PLAYER->Attack(RIGHT, monster_respawn->GetMonster());
	}
	/* �ƶ�:W/S/A/D */
	else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
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
	/* npc���� */
	else if (keyCode == EventKeyboard::KeyCode::KEY_C) {
		npc1->Chat();
	}
	/* ����ϵͳ */
	else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
		if (BagManager::getInstance()->isBagVisible())
			// ���ر���
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// �򿪱���
			BagManager::getInstance()->showBag(*PLAYER);
	}
}

void SetMap::InitialObstacle(cocos2d::TMXTiledMap* tileMap) {
    TMXObjectGroup* objectLayer = tileMap->getObjectGroup("Obstacles");    //��ȡ�ϰ�����
    if (objectLayer) {
        //�����ϰ����飬��ȡ�ϰ����λ����Ϣ
        auto obstacles = objectLayer->getObjects();

        for (const auto& obj : obstacles) {
            ValueMap obstacle = obj.asValueMap();

			auto objectType = obstacle["type"].asString();
			CCLOG("Obstacle type: %s", objectType.c_str());
			if (objectType == "rectangle") {
				// ���ݶ������Ͷ�ȡ������
				// �ϰ���ȫΪ����
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();
				float width = obstacle["width"].asFloat();
				float height = obstacle["height"].asFloat();

				// ������������
				Rect obstacleRect(x, y, width, height);

				// ������Դ洢��ʹ�����������������ײ���
				// ������ӵ�һ���ϰ����б���
				ObstacleList.push_back(obstacleRect);
			}
			else if (objectType == "ellipse") {
			    // ���ݶ������Ͷ�ȡ������
				// ����Ϊ��Բ����ȡΪ���͵� 
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();
				TeleportPointsList.push_back(Vec2(x,y));
			}
			else if (objectType == "point") {
			    // ���ݶ������Ͷ�ȡ������
				// ����Ϊ�㣬��ȡΪ������ 
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();
				InteractivePointsList.push_back(Vec2(x,y));
			}
        }
    }
}


bool SetMap::IsMoveable(cocos2d::Vec2& pos) {
	for (const auto& obstacle : ObstacleList) {
		if (obstacle.containsPoint(pos))     //�ж��Ƿ����ϰ��﷢����ײ
		{
			CCLOG("Can't move to this position");
			return false;
		}
	}
	CCLOG("Can move to this position");
	return true;
}

void SetMap::LoadMap() {
	/*****************************************������Ը�����ͼ���м��ش���********************************************/
	// ���س�ʼ��ͼ
	auto RebirthTemple = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
	float RebirthTempleWidth = RebirthTemple->getTileSize().width * RebirthTemple->getMapSize().width;
	float RebirthTempleHeight = RebirthTemple->getTileSize().height * RebirthTemple->getMapSize().height;
	RebirthTemple->setAnchorPoint(Vec2(0.5f, 0.5f));    ////���õ�ͼê��Ϊ����
	InitialObstacle(RebirthTemple);    //��ʼ���ϰ���

	BlackFogList.push_back(RebirthTemple->getLayer("BlackFog"));    //����ʼ��ͼ�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ

	// ���ػ�ɽ��ͼ
	auto Volcano = TMXTiledMap::create("Maps/volcano/volcano.tmx");
	BlackFogList.push_back(Volcano->getLayer("BlackFog"));    //����ɽ��ͼ�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(Volcano);    //��ʼ���ϰ���


	// ����ѩ�ص�ͼ
	auto SnowyWinter = TMXTiledMap::create("Maps/SnowyWinter/SnowyWinter.tmx");
	BlackFogList.push_back(SnowyWinter->getLayer("BlackFog"));    //��ѩ�ص�ͼ�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(SnowyWinter);    //��ʼ���ϰ���

	// ����ɳĮ��ͼ
	auto DeathDesert = TMXTiledMap::create("Maps/DeathDesert/DeathDesert.tmx");
	BlackFogList.push_back(DeathDesert->getLayer("BlackFog"));    //��ɳĮ��ͼ�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(DeathDesert);    //��ʼ���ϰ���

	// ����ɭ�ֵ�ͼ
	auto BrightForest = TMXTiledMap::create("Maps/BrightForest/BrightForest.tmx");
	BlackFogList.push_back(BrightForest->getLayer("BlackFog"));    //��ɭ�ֵ�ͼ�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(BrightForest);    //��ʼ���ϰ���

	//���ػ�ɽѩ�ر߽�
	auto Vol_Snow = TMXTiledMap::create("Maps/Vol_Snow_Ecotonal/Vol_Snow_Ecotonal.tmx");
	BlackFogList.push_back(Vol_Snow->getLayer("BlackFog"));    //����ɽѩ�ر߽�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(Vol_Snow);    //��ʼ���ϰ���

	//���ػ�ɽɭ�ֱ߽�
	auto Vol_Forest = TMXTiledMap::create("Maps/Vol_Forest_Ecotonal/Vol_Forest_Ecotonal.tmx");
	BlackFogList.push_back(Vol_Forest->getLayer("BlackFog"));    //����ɽɭ�ֱ߽�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(Vol_Forest);    //��ʼ���ϰ���

	//����ɭ��ѩ�ر߽�
	auto Desert_Snow = TMXTiledMap::create("Maps/Desert_Snow_Ecotonal/Desert_Snow_Ecotonal.tmx");
	BlackFogList.push_back(Desert_Snow->getLayer("BlackFog"));    //��ɭ��ѩ�ر߽�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(Desert_Snow);    //��ʼ���ϰ���

	//����ɭ��ɳĮ�߽�
	auto Forest_Desert = TMXTiledMap::create("Maps/Forest_Desert_Ecotonal/Forest_Desert_Ecotonal.tmx");
	BlackFogList.push_back(Forest_Desert->getLayer("BlackFog"));    //��ɭ��ɳĮ�߽�����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ��ͼ��ɫ����ʾ
	IsRegionRevealed.push_back(false);    //��ʼ��ͼ���򲻱���ʾ
	InitialObstacle(Forest_Desert);    //��ʼ���ϰ���

	/************************************��ʼ�Ը�����ͼ������ʾ����******************************************/
	//��ʼ����ʼ��ͼλ��
	RebirthTemple->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	RebirthTemple->setScale(1.0f);
	RebirthTemple->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(RebirthTemple);

	//���û�ɽ��ͼΪ��ʼ��ͼ���Ͻ�
	Volcano->setPosition(Vec2(visibleSize.width / 2 - RebirthTempleWidth - Derivation, visibleSize.height / 2 + RebirthTempleHeight + Derivation));
	Volcano->setScale(1.0f);
	Volcano->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Volcano);

	//����ѩ��Ϊ��ʼ��ͼ���Ͻ�
	SnowyWinter->setPosition(Vec2(visibleSize.width / 2 + RebirthTempleWidth + Derivation, visibleSize.height / 2 + RebirthTempleHeight + Derivation));
	SnowyWinter->setScale(1.0f);
	SnowyWinter->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(SnowyWinter);

	//��������ɳĮΪ��ʼ��ͼ���½�
	DeathDesert->setPosition(Vec2(visibleSize.width / 2 + RebirthTempleWidth + Derivation, visibleSize.height / 2 - RebirthTempleHeight - Derivation));
	DeathDesert->setScale(1.0f);
	DeathDesert->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(DeathDesert);

	//��������ɭ��Ϊ��ʼ��ͼ���½�
	BrightForest->setPosition(Vec2(visibleSize.width / 2 - RebirthTempleWidth - Derivation, visibleSize.height / 2 - RebirthTempleHeight - Derivation));
	BrightForest->setScale(1.0f);
	BrightForest->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(BrightForest);


	/********************************���÷ֽ��ͼ��λ��**************************************/
	//���û�ɽѩ�ر߽�
	Vol_Snow->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + RebirthTempleHeight + Derivation));
	Vol_Snow->setScale(1.0f);
	Vol_Snow->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Vol_Snow);

	//���û�ɽɭ�ֱ߽�
	Vol_Forest->setPosition(Vec2(visibleSize.width / 2 - RebirthTempleWidth - Derivation, visibleSize.height / 2));
	Vol_Forest->setScale(1.0f);
	Vol_Forest->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Vol_Forest);

	//����ɭ��ѩ�ر߽�,����ȥ��ɭ��ѩ��ʵ����ɳĮ��ѩ��
	Desert_Snow->setPosition(Vec2(visibleSize.width / 2 + RebirthTempleWidth + Derivation, visibleSize.height / 2));
	Desert_Snow->setScale(1.0f);
	Desert_Snow->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Desert_Snow);

	//����ɭ��ɳĮ�߽�
	Forest_Desert->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - RebirthTempleHeight - Derivation));
	Forest_Desert->setScale(1.0f);
	Forest_Desert->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->addChild(Forest_Desert);

	SetBlackFogInMicroMap();    //���µ�ͼ�еĺ�ɫ��
}

void SetMap::HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction) {
	Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
	
	// ���Ŀ��λ���Ƿ���ƶ�
	if (IsMoveable(targetPosition)) {
		if (!isKeyPressed[keyIndex]) {
			log("success&&&&&&&&&&&&&&&&");
			isKeyPressed[keyIndex] = true;
			PLAYER->Move(direction);
			this->schedule([=](float dt) {
				PLAYER->Move(direction);
				}, 0.8f, scheduleKey);
		}
		//@cbx 
		/*if (BagManager::getInstance()->getItemsNum() % 5 == 4)
		{
			shoes* it5 = new shoes(_goods.boots);
			BagManager::getInstance()->addItem(it5);
			return;
		}*/
	}
}

void SetMap::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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

void SetMap::SetBlackFogInMicroMap() {
	for (int i = 0; i < (int)BlackFogList.size(); i++) {
		if (!BlackFogList[i]->getParent()){
			this->addChild(BlackFogList[i]);
		}
		CCLOG("SetBlackFogInMicroMap: %d", i);
		BlackFogList[i]->setLocalZOrder(100);
		// ����������Ѿ�����ʾ�������غ�ɫ��������С��ͼ����ʾ��ɫ��
		BlackFogList[i]->setVisible( IsRegionRevealed[i] == true ? false : IsBlackFogVisible[i]);
	}
}

