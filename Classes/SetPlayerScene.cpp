#include <iostream>
#include "ui/CocosGUI.h"
#include "SetPlayerScene.h"
#include "Player.h"
#include "MainGameScene.h"

USING_NS_CC;
// ���徲̬��Ա����
int SetPlayerScene::who = 0;  // ����̬��Ա������ʼ��

Scene* SetPlayerScene::createScene() {
    return SetPlayerScene::create();
}

/* ��ʼ��:����������� */
bool SetPlayerScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    /* ���ر���ͼ */
    auto background = Sprite::create("Scene/RegistryScene.jpg");
    if (background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height); 
        this->addChild(background, -10); // ������ͼ��������ײ�
    }

    /* ����͸����ɫ���� */
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto drawNode = cocos2d::DrawNode::create();
    cocos2d::Color4F color(1.0f, 1.0f, 1.0f, 0.7); 
    cocos2d::Vec2 position(visibleSize.width / 2, visibleSize.height / 2); 
    float width = 1600.0f;  
    float height = 976.0f;  
    float radius = 30.0f;  
    drawNode->drawSolidRect(
        cocos2d::Vec2(position.x - width / 2, position.y - height / 2),  
        cocos2d::Vec2(position.x + width / 2, position.y + height / 2),  
        color
    );
    this->addChild(drawNode,-9); 
 
    /* ������ʾ��ӭ��������Ϸ */ 
    auto WelcomeTxt = Label::createWithTTF("Welcome to the Game!", "fonts/Lacquer.ttf", 140);
    WelcomeTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 475));
    WelcomeTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(WelcomeTxt);

    /* ����������� */
    // ���������
    auto textField = ui::TextField::create("Please enter your name", "fonts/KuaiLe_Chinese.ttf", 40);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 720));
    textField->setMaxLength(20);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(Color4B(0, 0, 0, 255));
    textField->setCursorEnabled(true); 
    // Ϊ�������ӱ߿�
    auto border = ui::Scale9Sprite::create("UI/Border2.png"); 
    border->setPreferredSize(Size(textField->getContentSize().width + 80, textField->getContentSize().height + 80)); 
    border->setPosition(textField->getPosition());
    this->addChild(border, -1); 
    this->addChild(textField);
    // �ύ��ť
    auto SubmitButton = ui::Button::create("Button/Button1.png", "Button/Button1Clicked.png");
    SubmitButton->setTitleText("");
    SubmitButton->ignoreContentAdaptWithSize(false);  
    SubmitButton->setContentSize(Size(180, 80));
    SubmitButton->setTitleFontSize(24);
    SubmitButton->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 900));
    this->addChild(SubmitButton, -1);
    // �ύ����������
    auto SubmitTxt = Label::createWithTTF("Submit", "fonts/KuaiLe_Chinese.ttf", 30);
    SubmitTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 900));
    SubmitTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(SubmitTxt);
    // ����������¼�
    textField->addEventListener([=](Ref* sender, ui::TextField::EventType type) {
        auto textField = dynamic_cast<ui::TextField*>(sender);
        switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME: // ��������ʱ�����̵���
            CCLOG("Input started");
            textField->setPlaceHolder(""); // ���ռλ������
            break;
        case ui::TextField::EventType::DETACH_WITH_IME: // ���̹ر�
            CCLOG("Input ended");
            if (textField->getString().empty()) {
                textField->setPlaceHolder("Please Enter Your Name"); // �ָ�ռλ������
            }
            break;
        case ui::TextField::EventType::INSERT_TEXT: // ��������
            CCLOG("Text inserted: %s", textField->getString().c_str());
            break;
        case ui::TextField::EventType::DELETE_BACKWARD: // ɾ������
            CCLOG("Text deleted");
            break;
        default:
            break;
        }
        });
    // ��ť����¼�
    SubmitButton->addClickEventListener([=](Ref* sender) mutable {
        name = textField->getString(); 
        if (name.empty()) {
            // ��������Ϊ�գ���ʾ�û���������
            auto warningLabel = Label::createWithSystemFont("Name cannot be empty!", "fonts/Marker Felt.ttf", 35);
            warningLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 820));
            warningLabel->setTextColor(Color4B(0, 0, 0, 150));
            this->addChild(warningLabel);
            // 2����Ƴ�����
            this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
                this->removeChild(warningLabel);
                }), nullptr));
        }
        else {
            CCLOG("Player Name: %s", name.c_str()); // ��ӡ�������
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, SetPlayerScene::selectRoleScene(), Color3B::BLACK));
            CCLOG("SubmitButton clicked, switching to selectRoleScene.");
        }
        });

    return true;
}

/* ѡ���ɫ */
Scene* SetPlayerScene::selectRoleScene() {
    auto select_role_scene = Scene::create();
    // Ԥ�ȶ���
    auto visibleSize = Director::getInstance()->getVisibleSize();

    /* ���ر���ͼ */
    auto background = Sprite::create("Scene/SelectRoleScene.png");
    if (background) {
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height);
        select_role_scene->addChild(background, -10);
    }

    /* ������ʾѡ���ɫ */
    auto ChooseRoleTxt = Label::createWithTTF("Please choose your role!", "fonts/KuaiLe_Chinese.ttf", 60);
    ChooseRoleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
    ChooseRoleTxt->setTextColor(Color4B(220, 220, 220, 255));
    select_role_scene->addChild(ChooseRoleTxt, 0);

    /* ѡ���ɫ */
    // Player1��ť
    auto P1Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P1Button->ignoreContentAdaptWithSize(false);
    P1Button->setContentSize(Size(300, 300));
    P1Button->setPosition(Vec2((visibleSize.width / 6) * 1, visibleSize.height / 2));
    select_role_scene->addChild(P1Button, 0);
    // Player1ͼ��
    auto P1Sprite = Sprite::create("Role/Player1/1.png");
    P1Sprite->setPosition(Vec2((visibleSize.width / 6) * 1, visibleSize.height / 2 + 30));
    P1Sprite->setScale(1.2f);
    select_role_scene->addChild(P1Sprite);
    // Player2��ť
    auto P2Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P2Button->ignoreContentAdaptWithSize(false);
    P2Button->setContentSize(Size(300, 300));
    P2Button->setPosition(Vec2((visibleSize.width / 6) * 2, visibleSize.height / 2));
    select_role_scene->addChild(P2Button, 0);
    // Player2ͼ��
    auto P2Sprite = Sprite::create("Role/Player2/1.png");
    P2Sprite->setPosition(Vec2((visibleSize.width / 6) * 2, visibleSize.height / 2 + 30));
    P2Sprite->setScale(1.2f);
    select_role_scene->addChild(P2Sprite);
    // Player3��ť
    auto P3Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P3Button->ignoreContentAdaptWithSize(false);
    P3Button->setContentSize(Size(300, 300));
    P3Button->setPosition(Vec2((visibleSize.width / 6) * 3, visibleSize.height / 2));
    select_role_scene->addChild(P3Button, 0);
    // Player3ͼ��
    auto P3Sprite = Sprite::create("Role/Player3/1.png");
    P3Sprite->setPosition(Vec2((visibleSize.width / 6) * 3, visibleSize.height / 2 + 30));
    P3Sprite->setScale(1.2f);
    select_role_scene->addChild(P3Sprite);
    // Player4��ť
    auto P4Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P4Button->ignoreContentAdaptWithSize(false);
    P4Button->setContentSize(Size(300, 300));
    P4Button->setPosition(Vec2((visibleSize.width / 6) * 4, visibleSize.height / 2));
    select_role_scene->addChild(P4Button, 0);
    // Player4ͼ��
    auto P4Sprite = Sprite::create("Role/Player4/1.png");
    P4Sprite->setPosition(Vec2((visibleSize.width / 6) * 4, visibleSize.height / 2 + 30));
    P4Sprite->setScale(1.2f);
    select_role_scene->addChild(P4Sprite);
    // Player5��ť
    auto P5Button = ui::Button::create("UI/Border1.png", "UI/Border1Clicked.png");
    P5Button->ignoreContentAdaptWithSize(false);
    P5Button->setContentSize(Size(300, 300));
    P5Button->setPosition(Vec2((visibleSize.width / 6) * 5, visibleSize.height / 2));
    select_role_scene->addChild(P5Button, 0);
    // Player5ͼ��
    auto P5Sprite = Sprite::create("Role/Player5/1.png");
    P5Sprite->setPosition(Vec2((visibleSize.width / 6) * 5, visibleSize.height / 2 + 30));
    P5Sprite->setScale(1.2f);
    select_role_scene->addChild(P5Sprite);

    /* ��ת */
    P1Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player1");
        who = Player1;
        auto scene = MainGameScene::createScene();
        //auto scene = LearningScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });
    P2Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player2");
        who = Player2;
        //auto scene = MainGameScene::createScene();
        auto scene = LearningScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });
    P3Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player3");
        who = Player3;
        //auto scene = MainGameScene::createScene();
        auto scene = LearningScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });
    P4Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player4");
        who = Player4;
        //auto scene = MainGameScene::createScene();
        auto scene = LearningScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });
    P5Button->addClickEventListener([=](Ref* sender) mutable {
        CCLOG("Choose Player5");
        who = Player5;

        //auto scene = MainGameScene::createScene();
        auto scene = LearningScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK));
        });

    return select_role_scene;
}
