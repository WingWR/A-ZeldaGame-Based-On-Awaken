#include "LearningScene.h"

USING_NS_CC;

Scene* LearningScene::createScene() {
    return LearningScene::create();
}

bool LearningScene::init() {
    if (!Scene::init()) {
        return false;
    }

    /* ������ */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    LEARNER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 2.0f, 100, 50, 20, 50, 10, 80, 1);

    /* ���ر���ͼ */
    // ��ȷ��:�Ƿ���ص�ͼ
    auto background = Sprite::create("Scene/LearningScene.png");
    if (background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height);
        this->addChild(background, -10); // ������ͼ��������ײ�
    }

    /* ����Ի���chatPanel */
    auto chatPanel = Sprite::create("UI/Panel5.png");
    chatPanel->setContentSize(Size(1600, 300));
    chatPanel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));
    chatPanel->setOpacity(190);
    this->addChild(chatPanel, -1);

    welcome();

    return true;
}

/* ��ӭ */
void LearningScene::welcome() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /* welcome���� */
    auto welcomeTxt = Label::createWithTTF("Are you ready to learn some operations?", "fonts/Lacquer.ttf", 60);
    welcomeTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    welcomeTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(welcomeTxt, 0);

    /* YesButtun */
    auto YesButton = ui::Button::create("Button/YesButton.png", "Button/YesButtonClicked.png");
    YesButton->ignoreContentAdaptWithSize(false);
    YesButton->setContentSize(Size(150, 60));
    YesButton->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    this->addChild(YesButton, 1);

    /* Yes���� */
    auto YesTxt = Label::createWithTTF("YES!", "fonts/KuaiLe_Chinese.ttf", 40);
    YesTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    YesTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(YesTxt,2); 

    YesButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(welcomeTxt);
        welcomeTxt = nullptr;
        this->removeChild(YesButton);
        YesButton = nullptr;
        this->removeChild(YesTxt);
        YesTxt = nullptr;
        // ��һ��
        this->learnMove_1();
        });
}

/* ѧ��· */
void LearningScene::learnMove_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("1.Move", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* moveTxt */
    auto moveTxt = Label::createWithTTF("Press W/S/A/D to go forward/back/left/right. ", "fonts/Lacquer.ttf", 40);
    moveTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    moveTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(moveTxt, 1);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(moveTxt);
        moveTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // ��һ��
        this->learnMove_2();
        });
}

void LearningScene::learnMove_2() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("Now have a try!", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* moveTxt */
    auto moveTxt = Label::createWithTTF("Press W/S/A/D to go forward/back/left/right. ", "fonts/Lacquer.ttf", 40);
    moveTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    moveTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(moveTxt, 1);
    /* ����ͼ */
    auto keyboardPic = Sprite::create("Others/KeyButtonWASD.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* ���̼��� */
    auto listener_move = EventListenerKeyboard::create();
    listener_move->onKeyPressed = CC_CALLBACK_2(LearningScene::MoveKeyPressed, this);
    listener_move->onKeyReleased = CC_CALLBACK_2(LearningScene::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_move, this);
    // ��һ��
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(moveTxt);
        moveTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        this->removeChild(keyboardPic);
        keyboardPic = nullptr;
        // ȡ�����̼���
        _eventDispatcher->removeEventListener(listener_move);
        listener_move = nullptr;
        // ��һ��
        this->learnAttack_1();
        });
}

/* ѧ���� */
void LearningScene::learnAttack_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("2.Attack", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* atkTxt */
    auto atkTxt = Label::createWithTTF("Press I/K/J/L to release forward/backward/left/right attack. ", "fonts/Lacquer.ttf", 40);
    atkTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    atkTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(atkTxt, 1);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 660, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(atkTxt);
        atkTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // ��һ��
        this->learnAttack_2();
        });
}

void LearningScene::learnAttack_2() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("Now have a try!", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* atkTxt */
    auto atkTxt = Label::createWithTTF("Press I/K/J/L to release forward/backward/left/right attack.", "fonts/Lacquer.ttf", 40);
    atkTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    atkTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(atkTxt, 1);
    /* ����ͼ */
    auto keyboardPic = Sprite::create("Others/KeyButtonIJKL.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* ���̼��� */
    auto listener_atk = EventListenerKeyboard::create();
    listener_atk->onKeyPressed = CC_CALLBACK_2(LearningScene::KeyPressed, this);
    listener_atk->onKeyReleased = CC_CALLBACK_2(LearningScene::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_atk, this);
    // ��һ��
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 660, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(atkTxt);
        atkTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        this->removeChild(keyboardPic);
        keyboardPic = nullptr;
        // ȡ�����̼���
        _eventDispatcher->removeEventListener(listener_atk);
        listener_atk = nullptr;
        // ��һ��
        this->learnChat_1();
        });
}

/* ѧ���� */
void LearningScene::learnChat_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* ����NPC */
    CHATNPC = new NPC("npc0", visibleSize.width / 2, visibleSize.height / 2, 2.0f, this, LEARNER);
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("3.Chat", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* chatTxt */
    auto chatTxt = Label::createWithTTF("Walk up to the NPC and press C to chat with him.", "fonts/Lacquer.ttf", 40);
    chatTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    chatTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(chatTxt, 1);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(chatTxt);
        chatTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // ��һ��
        this->learnChat_2();
        });
}

void LearningScene::learnChat_2() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("Now have a try!", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* chatTxt */
    auto chatTxt = Label::createWithTTF("Walk up to the NPC and press C to chat with him.", "fonts/Lacquer.ttf", 40);
    chatTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    chatTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(chatTxt, 1);
    /* ����ͼ */
    auto keyboardPic = Sprite::create("Others/KeyButtonC.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* ���̼��� */
    auto listener_chat = EventListenerKeyboard::create();
    listener_chat->onKeyPressed = CC_CALLBACK_2(LearningScene::ChatKeyPressed, this);
    listener_chat->onKeyReleased = CC_CALLBACK_2(LearningScene::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_chat, this);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(chatTxt);
        chatTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        this->removeChild(CHATNPC->mySprite);
        free(CHATNPC);
        this->removeChild(keyboardPic);
        keyboardPic = nullptr;
        // ȡ�����̼���
        _eventDispatcher->removeEventListener(listener_chat);
        listener_chat = nullptr; 
        // ��һ��
        this->learnBag_1();
        });
}

/* ѧϰ���� */
void LearningScene::learnBag_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("4.BagSystem", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* bagTxt */
    auto bagTxt = Label::createWithTTF("Press B to open the bag and press P to pick an item.", "fonts/Lacquer.ttf", 40);
    bagTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    bagTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(bagTxt, 1);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(bagTxt);
        bagTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // ��һ��
        this->learnBag_2();
        });
}

void LearningScene::learnBag_2() {
    /* ʵ�������� */ 
    BagManager* bagManager = BagManager::getInstance();
    if (bagManager->getParent() == nullptr)
        this->addChild(bagManager);
    // visibleSize
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("Now have a try!", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* bagTxt */
    auto bagTxt = Label::createWithTTF("Press B to open the bag.", "fonts/Lacquer.ttf", 40);
    bagTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    bagTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(bagTxt, 1);
    /* ����ͼ */
    auto keyboardPic = Sprite::create("Others/KeyButtonB.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* ���̼��� */
    auto listener_bag = EventListenerKeyboard::create();
    listener_bag->onKeyPressed = CC_CALLBACK_2(LearningScene::BagKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_bag, this);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �Ƴ�Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(bagTxt);
        bagTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        this->removeChild(keyboardPic);
        keyboardPic = nullptr;
        this->removeChild(bagManager);
        bagManager = nullptr;
        // ȡ�����̼���
        _eventDispatcher->removeEventListener(listener_bag);
        listener_bag = nullptr;
        // ��һ��
        this->finish();
        });
}

/* ��� */
void LearningScene::finish() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("Congratulations!", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* finishTxt */
    auto bagTxt = Label::createWithTTF("You have finished the beginner tutorial.", "fonts/Lacquer.ttf", 40);
    bagTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    bagTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(bagTxt, 1);
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton���� */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // �л�����
        auto scene = SetMap::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });
}

/* ���̼���:Move */
void LearningScene::MoveKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	Vec2 moveBy;
	int speed = 30;
	
	/* �ƶ�:W/S/A/D */
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		moveBy = Vec2(0, speed);
		Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[0]) {
            isKeyPressed[0] = true;
            LEARNER->Move(UP);
            this->schedule([&](float dt) {
                LEARNER->Move(UP);
                }, 0.8f, "MoveUP");
        }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		moveBy = Vec2(0, -speed);
		Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[1]) {
            isKeyPressed[1] = true;
            LEARNER->Move(DOWN);
            this->schedule([&](float dt) {
                LEARNER->Move(DOWN);
                }, 0.8f, "MoveDOWN");
        }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		moveBy = Vec2(-speed, 0);
		Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[2]) {
            isKeyPressed[2] = true;
            LEARNER->Move(LEFT);
            this->schedule([&](float dt) {
                LEARNER->Move(LEFT);
                }, 0.8f, "MoveLEFT");
        }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		moveBy = Vec2(speed, 0);
		Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[3]) {
            isKeyPressed[3] = true;
            LEARNER->Move(RIGHT);
            this->schedule([&](float dt) {
                LEARNER->Move(RIGHT);
                }, 0.8f, "MoveRIGHT");
        }
	}	
}

void LearningScene::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
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

/* ���̼���:Move+Atk */
void LearningScene::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    Vec2 moveBy;
    int speed = 30;

    /* �ƶ�:W/S/A/D */
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        moveBy = Vec2(0, speed);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[0]) {
            isKeyPressed[0] = true;
            LEARNER->Move(UP);
            this->schedule([&](float dt) {
                LEARNER->Move(UP);
                }, 0.8f, "MoveUP");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        moveBy = Vec2(0, -speed);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[1]) {
            isKeyPressed[1] = true;
            LEARNER->Move(DOWN);
            this->schedule([&](float dt) {
                LEARNER->Move(DOWN);
                }, 0.8f, "MoveDOWN");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        moveBy = Vec2(-speed, 0);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[2]) {
            isKeyPressed[2] = true;
            LEARNER->Move(LEFT);
            this->schedule([&](float dt) {
                LEARNER->Move(LEFT);
                }, 0.8f, "MoveLEFT");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        moveBy = Vec2(speed, 0);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[3]) {
            isKeyPressed[3] = true;
            LEARNER->Move(RIGHT);
            this->schedule([&](float dt) {
                LEARNER->Move(RIGHT);
                }, 0.8f, "MoveRIGHT");
        }
    }
    /* ����:I/K/J/L */
    else if (keyCode == EventKeyboard::KeyCode::KEY_I)
        LEARNER->Creature::Attack(UP);
    else if (keyCode == EventKeyboard::KeyCode::KEY_K)
        LEARNER->Creature::Attack(DOWN);
    else if (keyCode == EventKeyboard::KeyCode::KEY_J)
        LEARNER->Creature::Attack(LEFT);
    else if (keyCode == EventKeyboard::KeyCode::KEY_L)
        LEARNER->Creature::Attack(RIGHT);
}

/* ���̼���:Move+Atk+Chat */
void LearningScene::ChatKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    Vec2 moveBy;
    int speed = 30;

    /* �ƶ�:W/S/A/D */
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        moveBy = Vec2(0, speed);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[0]) {
            isKeyPressed[0] = true;
            LEARNER->Move(UP);
            this->schedule([&](float dt) {
                LEARNER->Move(UP);
                }, 0.8f, "MoveUP");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        moveBy = Vec2(0, -speed);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[1]) {
            isKeyPressed[1] = true;
            LEARNER->Move(DOWN);
            this->schedule([&](float dt) {
                LEARNER->Move(DOWN);
                }, 0.8f, "MoveDOWN");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        moveBy = Vec2(-speed, 0);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[2]) {
            isKeyPressed[2] = true;
            LEARNER->Move(LEFT);
            this->schedule([&](float dt) {
                LEARNER->Move(LEFT);
                }, 0.8f, "MoveLEFT");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        moveBy = Vec2(speed, 0);
        Vec2 targetPosition = LEARNER->mySprite->getPosition() + moveBy;
        if (!isKeyPressed[3]) {
            isKeyPressed[3] = true;
            LEARNER->Move(RIGHT);
            this->schedule([&](float dt) {
                LEARNER->Move(RIGHT);
                }, 0.8f, "MoveRIGHT");
        }
    }
    /* ����:I/K/J/L */
    else if (keyCode == EventKeyboard::KeyCode::KEY_I)
        LEARNER->Creature::Attack(UP);
    else if (keyCode == EventKeyboard::KeyCode::KEY_K)
        LEARNER->Creature::Attack(DOWN);
    else if (keyCode == EventKeyboard::KeyCode::KEY_J)
        LEARNER->Creature::Attack(LEFT);
    else if (keyCode == EventKeyboard::KeyCode::KEY_L)
        LEARNER->Creature::Attack(RIGHT);
    /* �Ի� */
    else if (keyCode == EventKeyboard::KeyCode::KEY_C) {
        CHATNPC->Chat();
    }
}

/* ���̼���:bag */
void LearningScene::BagKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_B) {
        if (BagManager::getInstance()->isBagVisible())
            // ���ر���
            BagManager::getInstance()->hideBag(*LEARNER);
        else
            // �򿪱���
            BagManager::getInstance()->showBag(*LEARNER);
    }
}