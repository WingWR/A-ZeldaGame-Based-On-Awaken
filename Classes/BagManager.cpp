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
    if (_instance == nullptr) 
    {
        _instance = new BagManager();  // ����ʵ��
        _instance->init();  // ��ʼ��ʵ��
    }
    return _instance;  // ����ʵ��ָ��
}

BagManager::BagManager() : _isBagOpen(false), _bagPanel(nullptr)
{
    for (int i = 0; i < 40; i++)
    {
        items[i] = nullptr;
       
    }
    items_num = 0;
}

BagManager::~BagManager()
{
    if (_bagPanel) 
        _bagPanel->removeFromParent();
    if (_bagBackground) 
        _bagBackground->release();
    if (_characterBackground)
        _characterBackground->release();
}

bool BagManager::init()
{
    if (!Node::init()) 
        return false;  // ��ʼ��ʧ��

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
        // ������������
        createBagBackground();

        // ������Ʒ���ڵ���Ʒ
        updateBagUI();

        // ������ɫ���
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
    // ������Ʒ�����ӳߴ�ͼ��
    float xStart = 35.0f;  // ��ʼXλ��
    float yStart = _bagBackground->getContentSize().height - 30.0f;  // ��ʼYλ�ã��������������·���

    // ����5x8����Ʒ����
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 5; ++col)
        {
            // ����ÿ�����ӵ�����
            float xPos = xStart + col * 30;
            float yPos = yStart - row * 30;
            int index = row * 5 + col;

            // �����Ʒ��
            auto slot = Button::create("item_slot.png");
            slot->setPosition(Vec2(xPos, yPos));
            slot->addClickEventListener([=](Ref* sender) {
                slot_click(slot, row, col);
                });
            _bagBackground->addChild(slot);
            if (items[index] != NULL)
            {
                if (items[index]->image->getParent() == nullptr)// ͼ���Ƿ��и��ڵ�
                {
                    // ������Ʒͼ���λ�ò���ӵ���ť����
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);// ��Ӹ��ڵ�
                    items[index]->image->retain();
                }
                else
                {
                    items[index]->image->removeFromParent();// �Ƴ���ǰ�ĸ��ڵ�
                    items[index]->image->setPosition(Vec2(slot->getContentSize().width / 2, slot->getContentSize().height / 2));
                    slot->addChild(items[index]->image);
                    items[index]->image->retain();// ��֤ͼ����󲻱�����
                }
            }
        }
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
    _bagPanel->addChild(_characterBackground, -1);

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

// �����Ʒ���¼�
void BagManager::slot_click(Button* slot, int row, int col)
{
    // �������ʱ����Ƿ�����Ʒ
    if (items[row * 5 + col] != NULL)
    {
        // ����Ʒ��Ϣ���
        auto itemInfoBackground = Sprite::create("item_info_background.png");
        float itemInfoBackground_x = slot->getPosition().x + itemInfoBackground->getContentSize().width / 2 + slot->getContentSize().width / 2;
        float itemInfoBackground_y = slot->getPosition().y - itemInfoBackground->getContentSize().height / 2 + slot->getContentSize().height / 2;
        itemInfoBackground->setPosition(Vec2(itemInfoBackground_x, itemInfoBackground_y)); // �����������ڸ����Ա�
        _bagBackground->addChild(itemInfoBackground, 10);

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
        string itemDescription = items[row * 5 + col]->getDescription();

        // ��������ʾ��Ʒ���ֵ� Label
        auto itemNameLabel = Label::createWithSystemFont(itemName, "Arial", 10);
        // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
        itemNameLabel->setTextColor(Color4B(255, 215, 0, 255)); // Color4B�ĵ��ĸ�������͸����
        itemNameLabel->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 5));  // �����ڱ����Ϸ�
        itemInfoBackground->addChild(itemNameLabel);

        // ��������ʾ��Ʒ������ Label
        auto itemDescriptionLabel = Label::createWithSystemFont(itemDescription, "Arial", 8);
        // ����ê��
        itemDescriptionLabel->setAnchorPoint(Vec2(0, 0.5));
        // �����ı������Ϊ��Ʒ��Ϣ�����Ŀ�ȣ������ʵ������߾ࣩ
        float maxWidth = itemInfoBackground->getContentSize().width - 10;  // �������ұ߾�
        // ��������Ⱥ͸߶�
        itemDescriptionLabel->setDimensions(maxWidth, 0);
        itemDescriptionLabel->setPosition(Vec2(5, itemInfoBackground->getContentSize().height - 20));  // �����ڱ����Ϸ�
        itemInfoBackground->addChild(itemDescriptionLabel);

        // ����ʹ����Ʒ��ť
        auto useButton = Button::create("use_button.png");
        useButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 40));
        useButton->addClickEventListener([=](Ref* sender) {
            if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col]))
            {

            }
            else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col]))
            {
                // ��Ʒ���ӹ���
                items[row * 5 + col]->itemFunction();
                // ��������Ʒ
                discardItems(row * 5 + col);
                itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }
            }); // ���������¼�
        itemInfoBackground->addChild(useButton);

        // ������Ʒ������Ϊ��ť��Ӳ�ͬ������
        if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col])) // ��Ʒ��װ����
        {
            auto itemEquipLabel = Label::createWithSystemFont("equip", "Arial", 7); // ��ť����ʾ����װ��
            itemEquipLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ����λ��
            useButton->addChild(itemEquipLabel);
        }
        else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col])) // ��Ʒ������Ʒ��
        {
            auto itemConsumeLabel = Label::createWithSystemFont("consume", "Arial", 7); // ��ť����ʾ��������
            itemConsumeLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ����λ��
            useButton->addChild(itemConsumeLabel);
        }

        // ����������Ʒ��ť
        auto dicardButton = Button::create("use_button.png");
        dicardButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 60));
        dicardButton->addClickEventListener([=](Ref* sender) {
            // ��������Ʒ
            discardItems(row * 5 + col);
            itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }); // ���������¼�
        itemInfoBackground->addChild(dicardButton);
        // Ϊ��ť�������
        auto itemDiscardLabel = Label::createWithSystemFont("discard", "Arial", 7); // ��ť����ʾ���Ƕ���
        itemDiscardLabel->setPosition(Vec2(dicardButton->getContentSize().width / 2, dicardButton->getContentSize().height / 2)); // ����λ��
        dicardButton->addChild(itemDiscardLabel);
    }
}

// ����Ʒ��ӵ�����
void BagManager::addItem(item* it)
{
    if (it == nullptr || it->image == nullptr)
        return; // ��Ч��Ʒ���˳�����
    if (items_num < 40) // ����û����ʱ�ſ��������Ʒ
    {

        int location = 0;
        // �ҵ��յ���Ʒ��
        for (int i = 0; i < 40; i++)
            if (items[i] == NULL)
            {
                location = i;
                break;
            }
        items[location] = it; // ������Ʒ��
        it->image->retain(); // ��֤��Ʒͼ�����������
        if (_isBagOpen)
            updateBagUI();
        items_num++; // ��Ʒ������1
    }
}

// ����Ʒ�ӱ����ж���
void BagManager::discardItems(int index)
{
    // ȷ����Ʒ����
    if (items[index] != nullptr)
    {
        // �Ƴ���Ʒ��ͼ�񣨴��丸�ڵ��Ƴ���
        items[index]->image->removeFromParent();

        // �����Ʒ����
        delete items[index];  // ɾ����Ʒ����
        items[index] = nullptr; // ��ո�λ��

        // ������Ʒ����
        items_num--;

        // �������UI�Ѿ���ʾ��ˢ��UI
        if (_isBagOpen)
        {
            updateBagUI();
        }
    }
}