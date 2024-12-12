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
        items[i] = nullptr;
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

void BagManager::showBag(Player& _player)
{
    player = _player;
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

void BagManager::hideBag(Player& _player)
{
    if (_isBagOpen)
    {
        _bagPanel->setVisible(false);  // ���ر������
        _bagPanel->removeChild(_bagBackground);  // �Ƴ�����
        _bagPanel->removeChild(_characterBackground);  // �Ƴ���ɫ��屳��
        _bagBackground = nullptr;  // �������ָ��
        _characterBackground = nullptr;
        _isBagOpen = false;  // ����״̬
        _player = player;
    }
}

void BagManager::updateBagUI()
{
    // ������Ʒ�����ӳߴ�ͼ��
    float xStart = 75.0f;  // ��ʼXλ��
    float yStart = _bagBackground->getContentSize().height - 80.0f;  // ��ʼYλ�ã��������������·���

    // ����5x8����Ʒ����
    for (int row = 0; row < 8; ++row)
        for (int col = 0; col < 5; ++col)
        {
            // ����ÿ�����ӵ�����
            float xPos = xStart + col * 80;
            float yPos = yStart - row * 70;
            int index = row * 5 + col;

            // �����Ʒ��
            auto slot = Button::create("Bag/item_slot.png");
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
    // ���½�ɫ���
    createCharacterPanel();
}

// ������������
void BagManager::createBagBackground()
{
    // ���ñ�������ͼƬ
    _bagBackground = Sprite::create("Bag/bag_background.png");
    //  _bagBackground->setPosition(Vec2(player.mySprite->getPosition().x, player.mySprite->getPosition().y));
    _bagBackground->setPosition(Director::getInstance()->getVisibleSize() / 2);
    _bagPanel->addChild(_bagBackground);

    // ������������
    auto titleLabel = Label::createWithTTF("MY_BAG", "fonts/arial.ttf", 32);
    titleLabel->setPosition(Vec2(_bagBackground->getContentSize().width / 2, _bagBackground->getContentSize().height - 20));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    titleLabel->setTextColor(Color4B(255, 215, 0, 255));
    _bagBackground->addChild(titleLabel);
}

// ������ɫ���
void BagManager::createCharacterPanel()
{
    // ���ý�ɫ��屳��
    _characterBackground = Sprite::create("Bag/character_background.png");
    float characterBackground_x = _bagBackground->getPositionX() + _bagBackground->getContentSize().width / 2 + _characterBackground->getContentSize().width / 2;
    float characterBackground_y = _bagBackground->getPositionY() + _bagBackground->getContentSize().height / 2 - _characterBackground->getContentSize().height / 2;
    _characterBackground->setPosition(Vec2(characterBackground_x, characterBackground_y));
    _bagPanel->addChild(_characterBackground, -1);

    // ������ɫ������
    auto characterTitleLabel = Label::createWithTTF("MY_CHARACTER", "fonts/arial.ttf", 32);
    characterTitleLabel->setPosition(Vec2(_characterBackground->getContentSize().width / 2, _characterBackground->getContentSize().height - 20));
    // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
    characterTitleLabel->setTextColor(Color4B(255, 215, 0, 255));
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
    auto button1 = Button::create("Bag/item_slot.png");// ��Ӱ�ť
    button1->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y + borderHeight / 2 - 30));
    button1->addClickEventListener([](Ref* sender) {});// ��Ӱ�ť����¼�
    _characterBackground->addChild(button1);
    auto label1 = Label::createWithTTF("Weapon", "fonts/arial.ttf", 16);// ������� 
    label1->setPosition(Vec2(20, -6));
    button1->addChild(label1);

    // ��ȡ��ҵ�����ͼ�����õ�������
    if (player._weapon != nullptr)
    {
        // ��ȡ����ͼ������
        auto weaponImage = player._weapon->image;
        weaponImage->retain(); // ��֤ͼ����󲻱�����
        weaponImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (weaponImage != nullptr)
        {
            weaponImage->setPosition(Vec2(button1->getContentSize().width / 2, button1->getContentSize().height / 2));
            button1->addChild(weaponImage);  // ��ͼ����ӵ���������ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton1 = Button::create("Bag/close_button.png");
    closeButton1->setPosition(Vec2(button1->getContentSize().width, button1->getContentSize().height)); // ���Ͻ�λ��
    closeButton1->addClickEventListener([=](Ref* sender) {
        if (player._weapon != nullptr)
        {
            player.atk -= player._weapon->increase_attack;
            auto _item = dynamic_cast<item*>(player._weapon); // ��������ָ��ת��Ϊ��Ʒ��ָ��
            player._weapon = nullptr; // ����ɫ����ָ����Ϊ��ָ��
            addItem(_item); // ��ж�µ�װ���Ż���Ʒ��
        }
        });
    button1->addChild(closeButton1);


    // ����
    auto button2 = Button::create("Bag/item_slot.png");
    button2->setPosition(Vec2(borderPosition.x - borderWidth / 2 - 40, borderPosition.y - borderHeight / 2 + 30));
    button2->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button2);
    auto label2 = Label::createWithTTF("Armor", "fonts/arial.ttf", 16);
    label2->setPosition(Vec2(20, -6));
    button2->addChild(label2);

    // ��ȡ��ҵĻ���ͼ�����õ�������
    if (player._armor != nullptr)
    {
        // ��ȡ����ͼ������
        auto armorImage = player._armor->image;
        armorImage->retain(); // ��֤ͼ����󲻱�����
        armorImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (armorImage != nullptr)
        {
            armorImage->setPosition(Vec2(button2->getContentSize().width / 2, button2->getContentSize().height / 2));
            button2->addChild(armorImage);  // ��ͼ����ӵ���������ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton2 = Button::create("Bag/close_button.png");
    closeButton2->setPosition(Vec2(button2->getContentSize().width, button2->getContentSize().height)); // ���Ͻ�λ��
    closeButton2->addClickEventListener([=](Ref* sender) {
        if (player._armor != nullptr)
        {
            player.def -= player._armor->increase_defense;
            auto _item = dynamic_cast<item*>(player._armor);
            player._armor = nullptr;
            addItem(_item);
        }
        });
    button2->addChild(closeButton2);


    // Ь��
    auto button3 = Button::create("Bag/item_slot.png");
    button3->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y + borderHeight / 2 - 30));
    button3->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button3);
    auto label3 = Label::createWithTTF("Shoes", "fonts/arial.ttf", 16);
    label3->setPosition(Vec2(20, -6));
    button3->addChild(label3);

    // ��ȡ��ҵ�Ь��ͼ�����õ�Ь����
    if (player._shoes != nullptr)
    {
        // ��ȡЬ��ͼ������
        auto shoesImage = player._shoes->image;
        shoesImage->retain(); // ��֤ͼ����󲻱�����
        shoesImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (shoesImage != nullptr)
        {
            shoesImage->setPosition(Vec2(button3->getContentSize().width / 2, button3->getContentSize().height / 2));
            button3->addChild(shoesImage);  // ��ͼ����ӵ�Ь������ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton3 = Button::create("Bag/close_button.png");
    closeButton3->setPosition(Vec2(0, button3->getContentSize().height)); // ���Ͻ�λ��
    closeButton3->addClickEventListener([=](Ref* sender) {
        if (player._shoes != nullptr)
        {
            player.speed -= player._shoes->increase_speed;
            auto _item = dynamic_cast<item*>(player._shoes);
            player._shoes = nullptr;
            addItem(_item);
        }
        });
    button3->addChild(closeButton3);


    // ��Ʒ
    auto button4 = Button::create("Bag/item_slot.png");
    button4->setPosition(Vec2(borderPosition.x + borderWidth / 2 + 40, borderPosition.y - borderHeight / 2 + 30));
    button4->addClickEventListener([](Ref* sender) {});
    _characterBackground->addChild(button4);
    auto label4 = Label::createWithTTF("Accessories", "fonts/arial.ttf", 16);
    label4->setPosition(Vec2(20, -6));
    button4->addChild(label4);

    // ��ȡ��ҵ���Ʒͼ�����õ���Ʒ��
    if (player._accessories != nullptr)
    {
        // ��ȡ��Ʒͼ������
        auto accessoriesImage = player._accessories->image;
        accessoriesImage->retain(); // ��֤ͼ����󲻱�����
        accessoriesImage->removeFromParent(); // �Ƴ���ǰ�ĸ��ڵ�
        if (accessoriesImage != nullptr)
        {
            accessoriesImage->setPosition(Vec2(button4->getContentSize().width / 2, button4->getContentSize().height / 2));
            button4->addChild(accessoriesImage);  // ��ͼ����ӵ���Ʒ����ť��
        }
    }

    // ��ӹرհ�ť�����װ������װ������ж��װ��
    auto closeButton4 = Button::create("Bag/close_button.png");
    closeButton4->setPosition(Vec2(0, button4->getContentSize().height)); // ���Ͻ�λ��
    closeButton4->addClickEventListener([=](Ref* sender) {
        if (player._accessories != nullptr)
        {
            player.atk -= player._accessories->increase_attack;
            player.def -= player._accessories->increase_defense;
            player.speed -= player._accessories->increase_speed;
            auto _item = dynamic_cast<item*>(player._accessories);
            player._accessories = nullptr;
            addItem(_item);
        }
        });
    button4->addChild(closeButton4);

    //��ʾ��ɫ�ĵȼ���HP��MP
    // �ȼ�
    string player_level = "Level: " + to_string(player.level);
    auto characterLevel = Label::createWithTTF(player_level, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterLevel->setAnchorPoint(Vec2(0, 0.5));
    characterLevel->setPosition(Vec2(200, 320));
    _characterBackground->addChild(characterLevel);
    // HP
    string player_HP = "HP: " + to_string(player.hp);
    auto characterHP = Label::createWithTTF(player_HP, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterHP->setAnchorPoint(Vec2(0, 0.5));
    characterHP->setPosition(Vec2(1, 320));
    _characterBackground->addChild(characterHP);
    // MP
    string player_MP = "MP: " + to_string(player.mp);
    auto characterMP = Label::createWithTTF(player_MP, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterMP->setAnchorPoint(Vec2(0, 0.5));
    characterMP->setPosition(Vec2(1, 300));
    _characterBackground->addChild(characterMP);

    // ��ʾ��ɫ�Ĺ����������������ٶ�
    // ������
    string player_attack = "Attack: " + to_string(player.atk);
    auto characterAttack = Label::createWithTTF(player_attack, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterAttack->setAnchorPoint(Vec2(0, 0.5));
    characterAttack->setPosition(Vec2(80, 320));
    _characterBackground->addChild(characterAttack);
    // ������
    string player_defense = "Defense: " + to_string(player.def);
    auto characterDefense = Label::createWithTTF(player_defense, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterDefense->setAnchorPoint(Vec2(0, 0.5));
    characterDefense->setPosition(Vec2(80, 300));
    _characterBackground->addChild(characterDefense);

    // �ٶ�
    string player_speed = "Speed: " + to_string(player.speed);
    auto characterSpeed = Label::createWithTTF(player_speed, "fonts/arial.ttf", 16);
    // ����ê�㣬����߿�ʼ
    characterSpeed->setAnchorPoint(Vec2(0, 0.5));
    characterSpeed->setPosition(Vec2(200, 300));
    _characterBackground->addChild(characterSpeed);
}

// �����Ʒ���¼�
void BagManager::slot_click(Button* slot, int row, int col)
{
    // �������ʱ����Ƿ�����Ʒ
    if (items[row * 5 + col] != NULL)
    {
        // ����Ʒ��Ϣ���
        auto itemInfoBackground = Sprite::create("Bag/item_info_background.png");
        float itemInfoBackground_x = slot->getPosition().x + itemInfoBackground->getContentSize().width / 2 + slot->getContentSize().width / 2;
        float itemInfoBackground_y = slot->getPosition().y - itemInfoBackground->getContentSize().height / 2 + slot->getContentSize().height / 2;
        itemInfoBackground->setPosition(Vec2(itemInfoBackground_x, itemInfoBackground_y)); // �����������ڸ����Ա�
        _bagBackground->addChild(itemInfoBackground, 10);

        // �����رհ�ť������ť��
        auto closeButton = Button::create("Bag/close_button.png");
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
        auto itemNameLabel = Label::createWithSystemFont(itemName, "Arial", 24);
        // ����������ɫΪ��ɫ (RGB: 255, 215, 0)
        itemNameLabel->setTextColor(Color4B(255, 215, 0, 255)); // Color4B�ĵ��ĸ�������͸����
        itemNameLabel->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 10));  // �����ڱ����Ϸ�
        itemInfoBackground->addChild(itemNameLabel);

        // ��������ʾ��Ʒ������ Label
        auto itemDescriptionLabel = Label::createWithSystemFont(itemDescription, "Arial", 16);
        // ����ê��
        itemDescriptionLabel->setAnchorPoint(Vec2(0, 0.5));
        // �����ı������Ϊ��Ʒ��Ϣ�����Ŀ�ȣ������ʵ������߾ࣩ
        float maxWidth = itemInfoBackground->getContentSize().width - 10;  // �������ұ߾�
        // ��������Ⱥ͸߶�
        itemDescriptionLabel->setDimensions(maxWidth, 0);
        itemDescriptionLabel->setPosition(Vec2(10, itemInfoBackground->getContentSize().height - 30));  // �����ڱ����Ϸ�
        itemInfoBackground->addChild(itemDescriptionLabel);

        // ����ʹ����Ʒ��ť
        auto useButton = Button::create("Bag/use_button.png");
        useButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 100));
        useButton->addClickEventListener([=](Ref* sender) {
            if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col]))
            {
                // װ������Ʒ
                equipItem(row * 5 + col);
                itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }
            else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col]))
            {
                auto consumption = dynamic_cast<consumable*>(items[row * 5 + col]);
                player.hp += consumption->add_HP;
                dynamic_cast<item*>(items[row * 5 + col]);
                // ��������Ʒ
                discardItems(row * 5 + col);
                itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }
            }); // ���������¼�
        itemInfoBackground->addChild(useButton);

        // ������Ʒ������Ϊ��ť��Ӳ�ͬ������
        if (auto equipmentItem = dynamic_cast<equipment*>(items[row * 5 + col])) // ��Ʒ��װ����
        {
            auto itemEquipLabel = Label::createWithSystemFont("equip", "Arial", 16); // ��ť����ʾ����װ��
            itemEquipLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ����λ��
            useButton->addChild(itemEquipLabel);
        }
        else if (auto consumableItem = dynamic_cast<consumable*>(items[row * 5 + col])) // ��Ʒ������Ʒ��
        {
            auto itemConsumeLabel = Label::createWithSystemFont("consume", "Arial", 16); // ��ť����ʾ��������
            itemConsumeLabel->setPosition(Vec2(useButton->getContentSize().width / 2, useButton->getContentSize().height / 2)); // ����λ��
            useButton->addChild(itemConsumeLabel);
        }

        // ����������Ʒ��ť
        auto dicardButton = Button::create("Bag/use_button.png");
        dicardButton->setPosition(Vec2(itemInfoBackground->getContentSize().width / 2, itemInfoBackground->getContentSize().height - 130));
        dicardButton->addClickEventListener([=](Ref* sender) {
            // ��������Ʒ
            discardItems(row * 5 + col);
            itemInfoBackground->removeFromParent();  // ������ر���Ʒ��Ϣ���
            }); // ���������¼�
        itemInfoBackground->addChild(dicardButton);
        // Ϊ��ť�������
        auto itemDiscardLabel = Label::createWithSystemFont("discard", "Arial", 16); // ��ť����ʾ���Ƕ���
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
            updateBagUI();
    }
}

// �������ڵ���Ʒװ������ɫ����
void BagManager::equipItem(int index)
{
    if (items[index] != nullptr)
    {
        if (auto weaponItem = dynamic_cast<weapon*>(items[index])) // ��Ʒ��������
        {
            if (player._weapon == nullptr)
            {
                // ���½�ɫ����ָ��
                player._weapon = weaponItem;
                // ���ӽ�ɫ������
                player.atk += player._weapon->increase_attack;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
        else if (auto armorItem = dynamic_cast<armor*>(items[index])) // ��Ʒ�ǻ�����
        {
            if (player._armor == nullptr)
            {
                // ���½�ɫ����ָ��
                player._armor = armorItem;
                // ���ӽ�ɫ�ķ���ֵ
                player.def += player._armor->increase_defense;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
        else if (auto shoesItem = dynamic_cast<shoes*>(items[index])) // ��Ʒ��Ь����
        {
            if (player._shoes == nullptr)
            {
                // ���½�ɫЬ��ָ��
                player._shoes = shoesItem;
                // ���ӽ�ɫ���ٶ�
                player.speed += player._shoes->increase_speed;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
        else if (auto accessoriesItem = dynamic_cast<accessories*>(items[index])) // ��Ʒ����Ʒ��
        {
            if (player._accessories == nullptr)
            {
                // ���½�ɫ��Ʒָ��
                player._accessories = accessoriesItem;
                // ���ӽ�ɫ������
                player.atk += player._accessories->increase_attack;
                // ���ӽ�ɫ�ķ���ֵ
                player.def += player._accessories->increase_defense;
                // ���ӽ�ɫ���ٶ�
                player.speed += player._accessories->increase_speed;
                // �����������Ʒ��Ϣ
                items[index] = nullptr; // ��ո�λ��
                // ������Ʒ����
                items_num--;
                // �������UI�Ѿ���ʾ��ˢ��UI
                if (_isBagOpen)
                    updateBagUI();
            }
        }
    }

}