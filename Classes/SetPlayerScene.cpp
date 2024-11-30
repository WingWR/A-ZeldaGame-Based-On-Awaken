#include <iostream>
#include "SetPlayerScene.h"
#include "ui/CocosGUI.h"
#include "spine/spine-cocos2dx.h"

USING_NS_CC;

Scene* SetPlayerScene::createScene() {
    return SetPlayerScene::create();
}

/* 初始化:输入玩家姓名 */
bool SetPlayerScene::init() {
    if (!Scene::init()) {
        return false;
    }
    
    /* 加载背景图 */
    auto background = Sprite::create("Scene/RegistryScene.jpg");
    if (background) {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height); 
        this->addChild(background, -10); // 将背景图放置在最底层
    }

    /* 画半透明白色矩形 */
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
 
    /* 文字提示欢迎来到本游戏 */ 
    auto WelcomeTxt = Label::createWithTTF("Welcome to the Game!", "fonts/Lacquer.ttf", 140);
    WelcomeTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 475));
    WelcomeTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(WelcomeTxt);

    /* 输入玩家姓名 */
    // 创建输入框
    auto textField = ui::TextField::create("Please enter your name", "fonts/KuaiLe_Chinese.ttf", 40);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 720));
    textField->setMaxLength(20);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(Color4B(0, 0, 0, 255));
    textField->setCursorEnabled(true); 
    // 为输入框添加边框
    auto border = ui::Scale9Sprite::create("UI/Border2.png"); 
    border->setPreferredSize(Size(textField->getContentSize().width + 80, textField->getContentSize().height + 80)); 
    border->setPosition(textField->getPosition());
    this->addChild(border, -1); 
    this->addChild(textField);
    // 提交按钮
    auto SubmitButton = ui::Button::create("Button/Button1.png", "Button/Button1Clicked.png");
    SubmitButton->setTitleText("");
    SubmitButton->ignoreContentAdaptWithSize(false);  
    SubmitButton->setContentSize(Size(180, 80));
    SubmitButton->setTitleFontSize(24);
    SubmitButton->setPosition(Vec2(visibleSize.width / 2 , visibleSize.height - 900));
    this->addChild(SubmitButton, -1);
    // 提交按键加文字
    auto SubmitTxt = Label::createWithTTF("Submit", "fonts/KuaiLe_Chinese.ttf", 30);
    SubmitTxt->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 900));
    SubmitTxt->setTextColor(Color4B(0, 0, 0, 255));
    this->addChild(SubmitTxt);
    // 监听输入框事件
    textField->addEventListener([=](Ref* sender, ui::TextField::EventType type) {
        auto textField = dynamic_cast<ui::TextField*>(sender);
        switch (type) {
        case ui::TextField::EventType::ATTACH_WITH_IME: // 点击输入框时，键盘弹出
            CCLOG("Input started");
            textField->setPlaceHolder(""); // 清空占位符文字
            break;
        case ui::TextField::EventType::DETACH_WITH_IME: // 键盘关闭
            CCLOG("Input ended");
            if (textField->getString().empty()) {
                textField->setPlaceHolder("Please Enter Your Name"); // 恢复占位符文字
            }
            break;
        case ui::TextField::EventType::INSERT_TEXT: // 插入文字
            CCLOG("Text inserted: %s", textField->getString().c_str());
            break;
        case ui::TextField::EventType::DELETE_BACKWARD: // 删除文字
            CCLOG("Text deleted");
            break;
        default:
            break;
        }
        });
    // 按钮点击事件
    SubmitButton->addClickEventListener([=](Ref* sender) mutable {
        name = textField->getString(); 
        if (name.empty()) {
            // 如果输入框为空，提示用户输入名字
            auto warningLabel = Label::createWithSystemFont("Name cannot be empty!", "fonts/Marker Felt.ttf", 35);
            warningLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 820));
            warningLabel->setTextColor(Color4B(0, 0, 0, 150));
            this->addChild(warningLabel);
            // 2秒后移除警告
            this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]() {
                this->removeChild(warningLabel);
                }), nullptr));
        }
        else {
            CCLOG("Player Name: %s", name.c_str()); // 打印玩家姓名
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, SetPlayerScene::selectRoleScene(), Color3B::BLACK));
            CCLOG("SubmitButton clicked, switching to selectRoleScene.");
        }
        });



    return true;
}

/* 选择角色 */
Scene* SetPlayerScene::selectRoleScene() {
    auto select_role_scene = Scene::create();
    // 预先定义
    auto visibleSize = Director::getInstance()->getVisibleSize();
    /* 加载背景图 */
    auto background = Sprite::create("Scene/SelectRoleScene.png");
    if (background) {  
        background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
        background->setScale(visibleSize.width / background->getContentSize().width,
            visibleSize.height / background->getContentSize().height);
        select_role_scene->addChild(background, -10);
    }
    
    /* 加载第一个角色 */
    /*
    auto spineNode = spine::SkeletonAnimation::createWithFile("Role/Player/Arthur.json", "Role/Player/Arthur.atlas");
    
    if (spineNode) {
        spineNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));    
        spineNode->setScale(0.5f);  // 缩放比例
        spineNode->setAnimation(0, "atk", false);  // 图层索引 0，动画名称 "idle"，循环播放 true
        select_role_scene->addChild(spineNode);
    }
    else {
        CCLOG("Failed to load Spine animation.");
    }*/

    return select_role_scene;
}
