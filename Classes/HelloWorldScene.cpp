#include "HelloWorldScene.h"
#include "ui/CocosGUI.h"
#include "SetPlayerScene.h"
#include "MapScene.h"

#include "SetMap.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s/n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp/n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Genshin Style Open World Adventure Game", "fonts/Lacquer.ttf", 48);
    if (label == nullptr)
    {
        problemLoading("'fonts/Lacquer.ttf.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
 
    // ��ʼ��Ϸ��ť
    auto button = cocos2d::ui::Button::create("Button/PlayButton.png", "Button/PlayButtonClicked.png", "Button/PlayButtonClicked.png");
    button->ignoreContentAdaptWithSize(false);  // �������ݴ�С����
    button->setContentSize(Size(300, 150));
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) 
        {
        case ui::Widget::TouchEventType::BEGAN:
            CCLOG("Button Start Pressed");
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("Button Start Released");
            break;
        default:
            break;
        }
        });
    // ��ť����¼�������
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scene = SetPlayerScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK)); // �����л�
            CCLOG("Button clicked, switching to SetPlayerScene.");
        }
        });
    this->addChild(button);

    //�����ͼ
    /*auto button = cocos2d::ui::Button::create("Button/PlayButton.png", "Button/PlayButtonClicked.png", "Button/PlayButtonClicked.png");
    button->ignoreContentAdaptWithSize(false);  // �������ݴ�С����
    button->setContentSize(Size(300, 150));
    button->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 300));
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        switch (type) 
        {
        case ui::Widget::TouchEventType::BEGAN:
            CCLOG("Button Map Pressed");
            break;
        case ui::Widget::TouchEventType::ENDED:
            CCLOG("Button Map Released");
            break;
        default:
            break;
        }
        });
    // ��ť����¼�������
    button->addTouchEventListener([](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scene = MapScene::createScene();          
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::BLACK)); // �����л�

            CCLOG("Button clicked, switching to MapScene.");
        }
        });
    this->addChild(button);
    return true;*/
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
