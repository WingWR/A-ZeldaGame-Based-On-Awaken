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

	/*
    //���������С��ͼ����ͼ����
    MicroMap = MicroMap::create();
    MicroMap->setVisible(false);    //��ʼ����С��ͼ
    MicroMap->setScale(1.0f);    //����С��ͼ���ű���
    this->addChild(MicroMap, 100);     //���С��ͼ������,С��ͼ��ͼ�����ȼ����
	*/

    IsMicroMapVisible = false;    //��ʼ��С��ͼ״̬����

    //��Ӽ��̼�����������M��С��ͼ
    auto KeyListener = EventListenerKeyboard::create();
    KeyListener->onKeyPressed = CC_CALLBACK_2(SetMap::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

	//��ȡ��Ļ�ߴ�
	visibleSize = Director::getInstance()->getVisibleSize();

    /*��ʼ������ͼ�������С��ͼ�����*/
	this->InitalCamera();

    /*���س�ʼ��ͼ*/
    this->LoadMap();
  
    ///////////////////////
    // ���̼���
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressed, this);
    listener->onKeyReleased = CC_CALLBACK_2(SetMap::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // lq�ӵĵ���С��
    PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 80, 1);

	// lq�ӵĵ���С��
	PLAYER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 0.5f, 100, 50, 20, 50, 10, 500, 1);

	// �Ӹ�npc
	npc1 = new NPC("npc1", visibleSize.width / 2, visibleSize.height / 2 - 200, 1.0f, this, PLAYER);

	Bonus b;
	// �Ӹ�����
	Monster1 = new Monster("Monster1", 100000, 600, 20, 20, 20, 100, 2, 50, 100, 0, b, PLAYER, 1000, 1, this);
	this->addChild(Monster1);
	// �Ӹ�Monster2
	Monster2 = new Monster("Monster2", 100000, 600, 20, 20, 20, 100, 2, 1000, 100, 0, b, PLAYER, 1000, 1, this);
	this->addChild(Monster2);
	// ����
	BagManager* bagManager = BagManager::getInstance();
	if (bagManager->getParent() == nullptr)
		this->addChild(bagManager);
	///////////////////////

	this->MainCameraFollowPlayer();    //ע������ͼ�����������ҵĺ���

    return true;
}

void SetMap::InitalCamera() {
	//��������ͼ�����
	camera = getDefaultCamera();

	//����С��ͼ�����
	camera_in_micro_map = Camera::createPerspective(60.0f,visibleSize.width / visibleSize.height, 100.0f, 4000.0f);
	
	// ��С��ͼ��������������
	camera_in_micro_map->setVisible(false);    //��ʼ����С��ͼ�����
	this->addChild(camera_in_micro_map);
}

EventListenerMouse* SetMap::createMouseListener(Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed) {
	auto listener = EventListenerMouse::create();
	listener->onMouseMove = [=](EventMouse* event) {
		float ScrollY = event->getScrollY();
		Vec3 cameraPosition = camera->getPosition3D();

		//ͨ���������룬����������߶�
		cameraPosition.z += ScrollY * ScrollSpeed;

		// ���� Z ֵ��Χ
		cameraPosition.z = std::min(cameraPosition.z, MaxHeight); // ���߶�
		cameraPosition.z = std::max(cameraPosition.z, MinHeight); // ��С�߶�

		camera->setPosition3D(cameraPosition);
		CCLOG("cameraPosition.z = %f", cameraPosition.z);
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
	mainMapListener = createMouseListener(camera, 600.0f, 200.0f, ScrollSpeed);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mainMapListener, camera);    // ��ȡ�¼�����������Ӽ�����

	// �������������ʵʱ��������
	schedule([=](float dt) {
		float updatedCameraZ = camera->getPosition3D().z;    //��ȡ������ĸ߶�
		Vec2 playerPosition = PLAYER->mySprite->getPosition();    //��ȡ���λ��
		this->UpdateCameraPosition(camera, playerPosition, updatedCameraZ);    //���������λ��
		}, "camera_update_key");
}

void SetMap::MicroCameraFollowPlayer() {
	// ����������ĳ�ʼλ��
	float InitCameraZinMicroMap = 2000.0f;

	// ÿ�ν���С��ͼʱ����С�������λ����������λ��
	Vec2 centerPosition(1200, 1200);
	UpdateCameraPosition(camera_in_micro_map, centerPosition, InitCameraZinMicroMap);

	// �򴴽�����С��ͼ������
	microMapListener = createMouseListener(camera_in_micro_map, 3000.0f, 1200.0f, ScrollSpeed);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(microMapListener, camera_in_micro_map);    	// ��ȡ�¼�����������Ӽ�����
}

void SetMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // �л�С��ͼ��ʾ״̬
        IsMicroMapVisible = !IsMicroMapVisible;
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
}

void SetMap::InitialObstacle(cocos2d::TMXTiledMap* tileMap) {
    TMXObjectGroup* objectLayer = tileMap->getObjectGroup("Obstacles");    //��ȡ�ϰ�����
    if (objectLayer) {
        //�����ϰ����飬��ȡ�ϰ����λ����Ϣ
        auto obstacles = objectLayer->getObjects();

        for (const auto& obj : obstacles) {
            ValueMap obstacle = obj.asValueMap();

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
    CCLOG("RebirthTempleWidth:  %f RebirthTempleHeight: %f",RebirthTempleWidth, RebirthTempleHeight);
    RebirthTemple->setAnchorPoint(Vec2(0.5f, 0.5f));    ////���õ�ͼê��Ϊ����
    //InitialObstacle(RebirthTemple);    //��ʼ���ϰ���

    // ���ػ�ɽ��ͼ
    auto Volcano = TMXTiledMap::create("Maps/volcano/volcano.tmx");
    //InitialObstacle(Volcano);    //��ʼ���ϰ���

    // ����ѩ�ص�ͼ
    auto SnowyWinter= TMXTiledMap::create("Maps/SnowyWinter/SnowyWinter.tmx");
    //InitialObstacle(SnowyWinter);    //��ʼ���ϰ���

    // ����ɳĮ��ͼ
    auto DeathDesert = TMXTiledMap::create("Maps/DeathDesert/DeathDesert.tmx");
    //InitialObstacle(DeathDesert);    //��ʼ���ϰ���

    // ����ɭ�ֵ�ͼ
    auto BrightForest = TMXTiledMap::create("Maps/BrightForest/BrightForest.tmx");
    //InitialObstacle(BrightForest);    //��ʼ���ϰ���

    //���ػ�ɽѩ�ر߽�
    auto Vol_Snow= TMXTiledMap::create("Maps/Vol_Snow_Ecotonal/Vol_Snow_Ecotonal.tmx");
    //InitialObstacle(Vol_Snow);    //��ʼ���ϰ���

    //���ػ�ɽɭ�ֱ߽�
    auto Vol_Forest= TMXTiledMap::create("Maps/Vol_Forest_Ecotonal/Vol_Forest_Ecotonal.tmx");
    //InitialObstacle(Vol_Forest);    //��ʼ���ϰ���

    //����ɭ��ѩ�ر߽�
    auto Desert_Snow= TMXTiledMap::create("Maps/Desert_Snow_Ecotonal/Desert_Snow_Ecotonal.tmx");
    //InitialObstacle(Forest_Snow);    //��ʼ���ϰ���

    //����ɭ��ɳĮ�߽�
    auto Forest_Desert= TMXTiledMap::create("Maps/Forest_Desert_Ecotonal/Forest_Desert_Ecotonal.tmx");
    //InitialObstacle(Forest_Desert);    //��ʼ���ϰ���

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
}

void SetMap::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	Vec2 moveBy;
	int speed = 30;
	/* ����:I/K/J/L */
	if (keyCode == EventKeyboard::KeyCode::KEY_I)
		PLAYER->Attack(UP);
	else if (keyCode == EventKeyboard::KeyCode::KEY_K)
		PLAYER->Attack(DOWN);
	else if (keyCode == EventKeyboard::KeyCode::KEY_J)
		PLAYER->Attack(LEFT);
	else if (keyCode == EventKeyboard::KeyCode::KEY_L)
		PLAYER->Attack(RIGHT);
	/* �ƶ�:W/S/A/D */
	else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		moveBy = Vec2(0, speed);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[0]) {
				isKeyPressed[0] = true;
				PLAYER->Move(UP);
				this->schedule([&](float dt) {
					PLAYER->Move(UP);
					}, 0.8f, "MoveUP");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		moveBy = Vec2(0, -speed);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[1]) {
				isKeyPressed[1] = true;
				PLAYER->Move(DOWN);
				this->schedule([&](float dt) {
					PLAYER->Move(DOWN);
					}, 0.8f, "MoveDOWN");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		moveBy = Vec2(-speed, 0);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[2]) {
				isKeyPressed[2] = true;
				PLAYER->Move(LEFT);
				this->schedule([&](float dt) {
					PLAYER->Move(LEFT);
					}, 0.8f, "MoveLEFT");
			}
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		moveBy = Vec2(speed, 0);
		Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
		if (IsMoveable(targetPosition)) {
			if (!isKeyPressed[3]) {
				isKeyPressed[3] = true;
				PLAYER->Move(RIGHT);
				this->schedule([&](float dt) {
					PLAYER->Move(RIGHT);
					}, 0.8f, "MoveRIGHT");
			}
		}
	}

	// ����Monster1����Ч���ã��ǵ�ɾ
	else if (keyCode == EventKeyboard::KeyCode::KEY_T) {
		int dx = Monster1->mySprite->getPosition().x - PLAYER->mySprite->getPosition().x;
		int dy = Monster1->mySprite->getPosition().y - PLAYER->mySprite->getPosition().y;
		if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(Monster1->getAtkRange(), 2))
			Monster1->Attack();
		else
			Monster1->Attack();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_Y) {
		npc1->Chat();
		//Monster2->Attack(UP);
		//PLAYER->Heal();
		//PLAYER->Die();
	}
	/* B/P:���� */
	else if (keyCode == EventKeyboard::KeyCode::KEY_B) {

		if (BagManager::getInstance()->isBagVisible())
			// ���ر���
			BagManager::getInstance()->hideBag(*PLAYER);
		else
			// �򿪱���
			BagManager::getInstance()->showBag(*PLAYER);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_P) {
		goods _goods;
		if (BagManager::getInstance()->getItemsNum() % 5 == 0)
		{
			weapon* it1 = new weapon(_goods.icon_sword);
			BagManager::getInstance()->addItem(it1);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 1)
		{
			consumable* it2 = new consumable(_goods.pumkin);
			BagManager::getInstance()->addItem(it2);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 2)
		{
			accessories* it3 = new accessories(_goods.bomb);
			BagManager::getInstance()->addItem(it3);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 3)
		{
			armor* it4 = new armor(_goods.icon_conselet);
			BagManager::getInstance()->addItem(it4);
			return;
		}
		if (BagManager::getInstance()->getItemsNum() % 5 == 4)
		{
			shoes* it5 = new shoes(_goods.boots);
			BagManager::getInstance()->addItem(it5);
			return;
		}
	}
}

void SetMap::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (isKeyPressed[0]) {
			isKeyPressed[0] = false;
			this->unschedule("MoveUP");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (isKeyPressed[1]) {
			isKeyPressed[1] = false;
			this->unschedule("MoveDOWN");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (isKeyPressed[2]) {
			isKeyPressed[2] = false;
			this->unschedule("MoveLEFT");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (isKeyPressed[3]) {
			isKeyPressed[3] = false;
			this->unschedule("MoveRIGHT");
		}
	}
}