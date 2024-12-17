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