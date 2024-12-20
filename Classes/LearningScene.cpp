#include "LearningScene.h"

USING_NS_CC;

Scene* LearningScene::createScene() {
    return LearningScene::create();
}

bool LearningScene::init() {
    if (!Scene::init()) {
        return false;
    }

    /* 加载人 */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    LEARNER = new Player("Player" + std::to_string(SetPlayerScene::who + 1), this, visibleSize.width / 2, visibleSize.height / 2, 1.0f, 100, 50, 20, 50, 10, 80, 1);

    /* 加载背景图 */
    // 待确认:是否加载地图
    auto background = Sprite::create("Scene/LearningScene.png");
    if (background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height);
        this->addChild(background, -10); // 将背景图放置在最底层
    }

    /* 加入对话框chatPanel */
    auto chatPanel = Sprite::create("UI/Panel5.png");
    chatPanel->setContentSize(Size(1600, 300));
    chatPanel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));
    chatPanel->setOpacity(190);
    this->addChild(chatPanel, -1);

    welcome();

    return true;
}

/* 欢迎 */
void LearningScene::welcome() {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /* welcome文字 */
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

    /* Yes文字 */
    auto YesTxt = Label::createWithTTF("YES!", "fonts/KuaiLe_Chinese.ttf", 40);
    YesTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    YesTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(YesTxt,2); 

    YesButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(welcomeTxt);
        welcomeTxt = nullptr;
        this->removeChild(YesButton);
        YesButton = nullptr;
        this->removeChild(YesTxt);
        YesTxt = nullptr;
        // 下一步
        this->learnMove_1();
        });
}

/* 学走路 */
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(moveTxt);
        moveTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // 下一步
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
    /* 键盘图 */
    auto keyboardPic = Sprite::create("Others/KeyButtonWASD.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* 键盘监听 */
    auto listener_move = EventListenerKeyboard::create();
    listener_move->onKeyPressed = CC_CALLBACK_2(LearningScene::MoveKeyPressed, this);
    listener_move->onKeyReleased = CC_CALLBACK_2(LearningScene::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_move, this);
    // 下一步
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 580, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(moveTxt);
        moveTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        this->removeChild(keyboardPic);
        keyboardPic = nullptr;
        // 取消键盘监听
        _eventDispatcher->removeEventListener(listener_move);
        listener_move = nullptr;
        // 下一步
        this->learnAttack_1();
        });
}

/* 学攻击 */
void LearningScene::learnAttack_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("2.Attack", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* atkTxt */
    auto atkTxt = Label::createWithTTF("Press J to attack. Cool-down time exists.", "fonts/Lacquer.ttf", 40);
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(atkTxt);
        atkTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // 下一步
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
    auto atkTxt = Label::createWithTTF("Press J to attack. Cool-down time exists.", "fonts/Lacquer.ttf", 40);
    atkTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 250));
    atkTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(atkTxt, 1);
    /* 键盘图 */
    auto keyboardPic = Sprite::create("Others/KeyButtonJ.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* 键盘监听 */
    auto listener_atk = EventListenerKeyboard::create();
    listener_atk->onKeyPressed = CC_CALLBACK_2(LearningScene::KeyPressed, this);
    listener_atk->onKeyReleased = CC_CALLBACK_2(LearningScene::KeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener_atk, this);
    // 下一步
    /* NextButton */
    auto NextButton = ui::Button::create("Button/NextButton.png", "Button/NextButtonClicked.png");
    NextButton->ignoreContentAdaptWithSize(false);
    NextButton->setContentSize(Size(60, 60));
    NextButton->setPosition(Vec2(visibleSize.width / 2 + 660, visibleSize.height - 250));
    NextButton->setOpacity(180);
    this->addChild(NextButton, 1);
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(atkTxt);
        atkTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        this->removeChild(keyboardPic);
        keyboardPic = nullptr;
        // 取消键盘监听
        _eventDispatcher->removeEventListener(listener_atk);
        listener_atk = nullptr;
        // 下一步
        this->learnChat_1();
        });
}

/* 学交互 */
void LearningScene::learnChat_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* 加入NPC */
    CHATNPC = new NPC("npc0", visibleSize.width / 2 - 250, visibleSize.height / 2, 1.0f, this, LEARNER, nullptr);
    LEARNER->editSizeOffset(Size(45,110),Vec2(0,50));
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(chatTxt);
        chatTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // 下一步
        this->learnChat_2();
        });
}

void LearningScene::learnChat_2() {
    // 监测npc是否在有效触发范围内
    this->schedule([=](float dt) {
        CHATNPC->update();
        }, 0.1f, "npc_check_scheduler");
    // 检测是否碰撞
    this->schedule([=](float dt) {
        LEARNER->preventOverlap(LEARNER, CHATNPC);
        }, 0.001f, "player_check_collision_scheduler");

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
    /* 键盘图 */
    auto keyboardPic = Sprite::create("Others/KeyButtonC.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* 键盘监听 */
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
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
        // 取消键盘监听
        _eventDispatcher->removeEventListener(listener_chat);
        listener_chat = nullptr; 
        // 取消监测
        this->unschedule("player_check_collision_scheduler");
        this->unschedule("npc_check_scheduler");
        // 下一步
        this->learnBag_1();
        });
}

/* 学习背包 */
void LearningScene::learnBag_1() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* titleTxt */
    auto titleTxt = Label::createWithTTF("4.BagSystem", "fonts/KuaiLe_Chinese.ttf", 60);
    titleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
    titleTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(titleTxt, 1);
    /* bagTxt */
    auto bagTxt = Label::createWithTTF("Press B to open the bag and checkout the tasks.", "fonts/Lacquer.ttf", 40);
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
        this->removeChild(titleTxt);
        titleTxt = nullptr;
        this->removeChild(bagTxt);
        bagTxt = nullptr;
        this->removeChild(NextButton);
        NextButton = nullptr;
        // 下一步
        this->learnBag_2();
        });
}

void LearningScene::learnBag_2() {
    /* 实例化背包 */ 
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
    /* 键盘图 */
    auto keyboardPic = Sprite::create("Others/KeyButtonB.png");
    keyboardPic->setPosition(Vec2(visibleSize.width / 2 - 400, visibleSize.height - 150));
    keyboardPic->setScale(0.8f);
    this->addChild(keyboardPic, 1);
    /* 键盘监听 */
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 移除Button&Txt
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
        // 取消键盘监听
        _eventDispatcher->removeEventListener(listener_bag);
        listener_bag = nullptr;
        // 下一步
        this->finish();
        });
}

/* 完成 */
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
    /* NextButton监听 */
    NextButton->addClickEventListener([=](Ref* sender)mutable {
        // 切换场景
        auto scene = MainGameScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });
}

/* 键盘监听:Move */
void LearningScene::MoveKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	/* 移动:W/S/A/D */
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        if (!isKeyPressed[0]) {
            isKeyPressed[0] = true;
            LEARNER->learnMove(UP);
            this->schedule([&](float dt) {
                LEARNER->learnMove(UP);
                }, 0.8f, "MoveUP");
        }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        if (!isKeyPressed[1]) {
            isKeyPressed[1] = true;
            LEARNER->learnMove(DOWN);
            this->schedule([&](float dt) {
                LEARNER->learnMove(DOWN);
                }, 0.8f, "MoveDOWN");
        }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        if (!isKeyPressed[2]) {
            isKeyPressed[2] = true;
            LEARNER->learnMove(LEFT);
            this->schedule([&](float dt) {
                LEARNER->learnMove(LEFT);
                }, 0.8f, "MoveLEFT");
        }
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        if (!isKeyPressed[3]) {
            isKeyPressed[3] = true;
            LEARNER->learnMove(RIGHT);
            this->schedule([&](float dt) {
                LEARNER->learnMove(RIGHT);
                }, 0.8f, "MoveRIGHT");
        }
	}	
}

void LearningScene::KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		if (isKeyPressed[0]) {
			isKeyPressed[0] = false;
            LEARNER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveUP");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		if (isKeyPressed[1]) {
			isKeyPressed[1] = false;
            LEARNER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveDOWN");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		if (isKeyPressed[2]) {
			isKeyPressed[2] = false;
            LEARNER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveLEFT");
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		if (isKeyPressed[3]) {
			isKeyPressed[3] = false;
            LEARNER->mySprite->stopAllActions();  // 停止当前的所有动作
			this->unschedule("MoveRIGHT");
		}
	}
}

/* 键盘监听:Move+Atk */
void LearningScene::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    /* 移动:W/S/A/D */
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        if (!isKeyPressed[0]) {
            isKeyPressed[0] = true;
            LEARNER->learnMove(UP);
            this->schedule([&](float dt) {
                LEARNER->learnMove(UP);
                }, 0.8f, "MoveUP");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        if (!isKeyPressed[1]) {
            isKeyPressed[1] = true;
            LEARNER->learnMove(DOWN);
            this->schedule([&](float dt) {
                LEARNER->learnMove(DOWN);
                }, 0.8f, "MoveDOWN");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        if (!isKeyPressed[2]) {
            isKeyPressed[2] = true;
            LEARNER->learnMove(LEFT);
            this->schedule([&](float dt) {
                LEARNER->learnMove(LEFT);
                }, 0.8f, "MoveLEFT");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        if (!isKeyPressed[3]) {
            isKeyPressed[3] = true;
            LEARNER->learnMove(RIGHT);
            this->schedule([&](float dt) {
                LEARNER->learnMove(RIGHT);
                }, 0.8f, "MoveRIGHT");
        }
    }
    /* 攻击:I/K/J/L */
    else if (keyCode == EventKeyboard::KeyCode::KEY_I) {
        LEARNER->ChangeFaceTo(UP);
        LEARNER->Creature::Attack();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_K) {
        LEARNER->ChangeFaceTo(DOWN);
        LEARNER->Creature::Attack();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
        LEARNER->ChangeFaceTo(LEFT);
        LEARNER->Creature::Attack();
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_L) {
        LEARNER->ChangeFaceTo(RIGHT);
        LEARNER->Creature::Attack();
    }
}

/* 键盘监听:Move+Atk+Chat */
void LearningScene::ChatKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    /* 移动:W/S/A/D */
    if (keyCode == EventKeyboard::KeyCode::KEY_W) {
        if (!isKeyPressed[0]) {
            isKeyPressed[0] = true;
            LEARNER->learnMove(UP);
            this->schedule([&](float dt) {
                LEARNER->learnMove(UP);
                }, 0.8f, "MoveUP");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
        if (!isKeyPressed[1]) {
            isKeyPressed[1] = true;
            LEARNER->learnMove(DOWN);
            this->schedule([&](float dt) {
                LEARNER->learnMove(DOWN);
                }, 0.8f, "MoveDOWN");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
        if (!isKeyPressed[2]) {
            isKeyPressed[2] = true;
            LEARNER->learnMove(LEFT);
            this->schedule([&](float dt) {
                LEARNER->learnMove(LEFT);
                }, 0.8f, "MoveLEFT");
        }
    }
    else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
        if (!isKeyPressed[3]) {
            isKeyPressed[3] = true;
            LEARNER->learnMove(RIGHT);
            this->schedule([&](float dt) {
                LEARNER->learnMove(RIGHT);
                }, 0.8f, "MoveRIGHT");
        }
    }
    /* 攻击:J */
    else if (keyCode == EventKeyboard::KeyCode::KEY_J) {
        
        LEARNER->Creature::Attack();
    }
    /* 对话 */
    else if (keyCode == EventKeyboard::KeyCode::KEY_C) {
        CHATNPC->Chat();
    }
}

/* 键盘监听:bag */
void LearningScene::BagKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_B) {
        if (BagManager::getInstance()->isBagVisible())
            // 隐藏背包
            BagManager::getInstance()->hideBag(*LEARNER);
        else
            // 打开背包
            BagManager::getInstance()->showBag(*LEARNER);
    }
}