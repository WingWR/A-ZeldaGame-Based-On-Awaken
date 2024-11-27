#include <iostream>
#include "SetPlayerScene.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* SetPlayerScene::createScene() {
    return SetPlayerScene::create();
}

bool SetPlayerScene::init() {
    if (!Scene::init()) {
        return false;
    }

    /* ������ʾ��ӭ��������Ϸ */ 
    auto WelcomeTxt = Label::createWithTTF("Welcome to the Genshin-Style-Open-World-Adventure-Game!", "fonts/Marker Felt.ttf", 70);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    WelcomeTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 600));
    this->addChild(WelcomeTxt);

    /* ����������� */
    // ���������
    auto textField = ui::TextField::create("Enter Name Here", "Arial", 40);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 750));
    textField->setMaxLength(20);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(Color4B::WHITE);
    textField->setCursorEnabled(true); // ���ù����ʾ
    this->addChild(textField);

    // �ύ��ť
    auto SubmitButton = ui::Button::create("Button/SubmitButton.png", "Button/SubmitButtonClicked.png");
    SubmitButton->setTitleText("");
    SubmitButton->ignoreContentAdaptWithSize(false);  
    SubmitButton->setContentSize(Size(60, 60));
    SubmitButton->setTitleFontSize(24);
    SubmitButton->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height - 750));
    this->addChild(SubmitButton);

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
                textField->setPlaceHolder("Enter Name Here"); // �ָ�ռλ������
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
        name = textField->getString(); // ��ȡ�������ı�����
        if (name.empty()) {
            // ��������Ϊ�գ���ʾ�û���������
            auto warningLabel = Label::createWithSystemFont("Name cannot be empty!", "Arial", 24);
            warningLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 550));
            warningLabel->setTextColor(Color4B::RED);
            this->addChild(warningLabel);
            // 2����Ƴ�����
            this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
                this->removeChild(warningLabel);
                }), nullptr));
        }
        else {
            CCLOG("Player Name: %s", name.c_str()); // ��ӡ�������
            // ���Խ� name ���浽�ļ��򴫵ݵ���һ������
            // Director::getInstance()->replaceScene(TransitionFade::create(1.0f, NextScene::createScene(), Color3B::BLACK));
        }
        });



    return true;
}
