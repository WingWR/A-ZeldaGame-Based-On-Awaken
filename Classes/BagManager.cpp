#include "BagManager.h"
#include "ui/CocosGUI.h"
#include <vector>
#include "Item.h"

USING_NS_CC;
using namespace ui;
using namespace std;

BagManager* BagManager::_instance = nullptr;

BagManager* BagManager::getInstance()
{
    // ���ʵ�������ڣ�����һ���µ�ʵ��
    if (_instance == nullptr) {
        _instance = new BagManager();  // ����ʵ��
        _instance->init();  // ��ʼ��ʵ���������Ҫ�Ļ���
    }
    return _instance;  // ����ʵ��ָ��
}

BagManager::BagManager() : _isBagOpen(false), _bagPanel(nullptr)
{
    for (int i = 0; i < 40; i++)
        items[i] = nullptr;
}

BagManager::~BagManager()
{
    if (_bagPanel) 
    {
        _bagPanel->removeFromParent();
    }
    if (_bagBackground) 
    {
        _bagBackground->release();
    }
}

bool BagManager::init()
{
    if (!Node::init()) 
    {
        return false;  // ��ʼ��ʧ��
    }

    // ����������壬��Ϊ����UI������
    _bagPanel = Node::create();
    this->addChild(_bagPanel);  // �����������ӵ���ǰ�ڵ�
    _bagPanel->setVisible(false);  // Ĭ������±��������ص�
    
    return true;  // ��ʼ���ɹ�
}

void BagManager::showBag()
{
    // ���������δ�򿪣��򴴽�����ʾ��������
    if (!_isBagOpen)
    {
        // ���Ʊ������
        createBagBackground();

        // ������Ʒ�����ӳߴ�ͼ��
        float xStart = 35.0f;  // ��ʼXλ��
        float yStart = _bagBackground->getContentSize().height - 30.0f;  // ��ʼYλ�ã��������������·���

        // ����5x8����Ʒ����
        vector<Button*> slots;
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 5; ++col)
            {
                // ����ÿ�����ӵ�����
                float xPos = xStart + col * 30;
                float yPos = yStart - row * 30;

                // �������ӣ�ʹ��Sprite��Ϊ����
                auto slot = Button::create("item_slot.png");
                slot->setPosition(Vec2(xPos, yPos));
                slot->addClickEventListener([=](Ref* sender) {
                    // �������ʱ����Ƿ�����Ʒ
                    if (items[row * 5 + col] != NULL)
                    {
                        // ����Ʒ��Ϣ���
                        auto itemInfoBackground = Sprite::create("item_info_background.png");
                        float itemInfoBackground_x = slot->getPosition().x + itemInfoBackground->getContentSize().width / 2 + slot->getContentSize().width / 2;
                        float itemInfoBackground_y = slot->getPosition().y - itemInfoBackground->getContentSize().height / 2 + slot->getContentSize().height / 2;
                        itemInfoBackground->setPosition(Vec2(itemInfoBackground_x, itemInfoBackground_y)); // �����������ڸ����Ա�
                        _bagBackground->addChild(itemInfoBackground);

                        // �����رհ�ť������ť��
                        auto closeButton = Button::create("close_button.png");
                        closeButton->setPosition(Vec2(itemInfoBackground->getContentSize().width, itemInfoBackground->getContentSize().height)); // ���Ͻ�λ��
                        closeButton->addClickEventListener([=](Ref* sender) {
                            // �������ťʱ�Ƴ� itemInfoBackground
                            itemInfoBackground->removeFromParent();  // �Ӹ��ڵ��Ƴ�
                            });

                        // ���رհ�ť��ӵ�������
                        itemInfoBackground->addChild(closeButton);

                        // ��ȡ��Ʒ����
                        string itemName = items[row * 5 + col]->getName();

                        // ��������ʾ��Ʒ���ֵ� Label
                        auto itemNameLabel = Label::createWithSystemFont(itemName, "Arial", 8);
                        itemNameLabel->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 10));  // �����ڱ����Ϸ�
                        itemInfoBackground->addChild(itemNameLabel);
                    }
                    });
                _bagBackground->addChild(slot);
                slots.push_back(slot);
            }
        }
        item* it1 = new item("sword", "sword.png");
        it1->image->setPosition(Vec2(slots[0]->getContentSize().width / 2, slots[0]->getContentSize().height / 2));
        slots[0]->addChild(it1->image);
        items[0] = it1;
        item* it2 = new item("pumpkin", "Pumpkin.png");
        it2->image->setPosition(Vec2(slots[1]->getContentSize().width / 2, slots[1]->getContentSize().height / 2));
        slots[1]->addChild(it2->image);
        items[1] = it2;

        // ������ɫ��屳��
        createCharacterPanel();

        _bagPanel->setVisible(true);  // ��ʾ�������
        _isBagOpen = true;
    }
}

void BagManager::hideBag()
{
    if (_isBagOpen)
    {
        _bagPanel->setVisible(false);  // ���ر������
        _bagPanel->removeChild(_bagBackground);  // �Ƴ�����
        _bagPanel->removeChild(_characterBackground);  // �Ƴ���ɫ��屳��
        _bagBackground = nullptr;  // �������ָ��
        _characterBackground = nullptr;
        _isBagOpen = false;  // ����״̬
    }
}

void BagManager::updateBagUI()
{
  
}

// ������������
void BagManager::createBagBackground()
{
    // ���ñ�������ͼƬ
    _bagBackground = Sprite::create("bag_background.png");
    _bagBackground->setPosition(Director::getInstance()->getVisibleSize() / 2);
    _bagPanel->addChild(_bagBackground);

    // ������������
    auto titleLabel = Label::createWithTTF("MY_BAG", "fonts/arial.ttf", 8);
    titleLabel->setPosition(Vec2(_bagBackground->getContentSize().width / 2, _bagBackground->getContentSize().height - 10));
    _bagBackground->addChild(titleLabel);
}

// ������ɫ���
void BagManager::createCharacterPanel()
{
    // ���ý�ɫ��屳��
    _characterBackground = Sprite::create("character_background.png");
    float characterBackground_x = _bagBackground->getPositionX() + _bagBackground->getContentSize().width / 2 + _characterBackground->getContentSize().width / 2;
    float characterBackground_y = _bagBackground->getPositionY() + _bagBackground->getContentSize().height / 2 - _characterBackground->getContentSize().height / 2;
    _characterBackground->setPosition(Vec2(characterBackground_x, characterBackground_y));
    _bagPanel->addChild(_characterBackground);

    // ������ɫ������
    auto characterTitleLabel = Label::createWithTTF("MY_CHARACTER", "fonts/arial.ttf", 8);
    characterTitleLabel->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height - 10));
    _characterBackground->addChild(characterTitleLabel);

    // ���Ʊ߿�
    float borderWidth = _characterBackground->getContentSize().width / 2;
    float borderHeight = _characterBackground->getContentSize().height / 2;

    Vec2 borderPosition = Vec2(borderWidth, borderHeight);

    auto drawNode = DrawNode::create();
    _characterBackground->addChild(drawNode);

    drawNode->drawRect(
        Vec2(borderPosition.x - borderWidth / 2, borderPosition.y - borderHeight / 2),
        Vec2(borderPosition.x + borderWidth / 2, borderPosition.y + borderHeight / 2),
        Color4F(1.0f, 1.0f, 1.0f, 1.0f)
    );
    // �ڽ�ɫ����������װ����
    // ����
    auto button1 = Button::create("item_slot.png");// ��Ӱ�ť
    button1->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 15, borderPosition.y + borderHeight / 2 - 15));
    button1->addClickEventListener([](Ref* sender) {});// ��Ӱ�ť����¼�
    _characterBackground->addChild(button1);
    auto labe1 = Label::createWithTTF("Weapon", "fonts/arial.ttf", 8);// ������� 
    labe1->setPosition(Vec2(10, -6));
    button1->addChild(labe1);
    // ����
    auto button2 = Button::create("item_slot.png");
    button2->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 15, borderPosition.y - borderHeight / 2 + 15));
    button2->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button2);
    auto labe2 = Label::createWithTTF("Armor", "fonts/arial.ttf", 8);
    labe2->setPosition(Vec2(10, -6));
    button2->addChild(labe2);
    // Ь��
    auto button3 = Button::create("item_slot.png");
    button3->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 15, borderPosition.y + borderHeight / 2 - 15));
    button3->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button3);
    auto labe3 = Label::createWithTTF("Shoes", "fonts/arial.ttf", 8);
    labe3->setPosition(Vec2(10, -6));
    button3->addChild(labe3);
    // ��Ʒ
    auto button4 = Button::create("item_slot.png");
    button4->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 15, borderPosition.y - borderHeight / 2 + 15));
    button4->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button4);
    auto labe4 = Label::createWithTTF("Accessories", "fonts/arial.ttf", 8);
    labe4->setPosition(Vec2(10, -6));
    button4->addChild(labe4);

    //��ʾ��ɫ�ĵȼ���HP
    auto characterLevel = Label::createWithTTF("Level:", "fonts/arial.ttf", 8);
    characterLevel->setPosition(Vec2(12, 130));
    _characterBackground->addChild(characterLevel);
    auto characterHP = Label::createWithTTF("HP:", "fonts/arial.ttf", 8);
    characterHP->setPosition(Vec2(15, 120));
    _characterBackground->addChild(characterHP);
}
