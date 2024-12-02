#include <iostream>
#include "SetPlayerScene.h"
#include "Player.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

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
    ChooseRoleTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 200));
    ChooseRoleTxt->setTextColor(Color4B(220, 220, 220, 255));
    select_role_scene->addChild(ChooseRoleTxt);
    
    /* ���ص�һ����ɫ */
    auto panel_role = ui::Scale9Sprite::create("UI/Panel3.png");
    panel_role->setPreferredSize(Size(800, 800));
    panel_role->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    select_role_scene->addChild(panel_role, -1);

    /* �л���ɫ */
    Player player;
    player.showPlayer("Arthur", select_role_scene, 0.55f, visibleSize.width / 2 - 30, visibleSize.height / 2 + 50);

    //player.PlayerAttack("Longbow", select_role_scene, 3, 0.4, visibleSize.width / 2, visibleSize.height / 2);

    return select_role_scene;
}
