#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp/n");
}

bool HelloWorld::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // ��ȡ��Ļ��С��ԭ��
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->CreateBackground(visibleSize);    //������Ϸ��ʼ���汳��

    // ��ʼ��Ϸ��ť
    auto button = cocos2d::ui::Button::create("Button/PlayButton.png", "Button/PlayButtonClicked.png", "Button/PlayButtonClicked.png");
    button->ignoreContentAdaptWithSize(false); 
    button->setContentSize(Size(300, 150));
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));

    // ��ť����¼�������
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scene = SetPlayerScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK)); // �����л�
        }
        });
    this->addChild(button);

    return true;
}

void HelloWorld::CreateBackground(Size& visibleSize) {
    // ������Ϸ�Ŀ�ʼ����
    auto Background = Sprite::create("Scene/StartBackground.jpg");    
    Background->setPosition(visibleSize.width / 2, visibleSize.height / 2);    
    Background->setScale(1.08f);  
    Background->setScaleY(1.4f);
    this->addChild(Background);    
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{

    Director::getInstance()->end();

}