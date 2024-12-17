#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"
#include "ElementType.h"

USING_NS_CC;
using namespace ui;
using namespace std;

class item
{
public:
    // ��Ʒ������
    string name;
    // ��Ʒ��ͼ��
    cocos2d::Sprite* image;
    // ��Ʒ������
    string description;

    // ��Ʒ��ͼ������
    string imageName;

    // ���캯������Ҫ����Ʒ�����ֳ�Ա������ֵ
    item(const string& itemName, const string& imagePath, const string& itemDescription)
        : name(itemName), description(itemDescription)
    {
        image = cocos2d::Sprite::create(imagePath); // ������ƷͼƬ
        imageName = imagePath;
    }

    // ��ȡ��Ʒ������
    string getName() const
    {
        return name;
    }

    // ��ȡ��Ʒ������
    string getDescription() const
    {
        return description;
    }

    // ���������������ʹ�����Ϊ��̬��
    virtual ~item() {}
};
// װ����
class equipment :public item
{
public:
    equipment(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription)
    {
        equipment_level = 1;
        equipment_cost = 100;
    }

    // ���������������ʹ�����Ϊ��̬��
    virtual ~equipment() {}

    // ���ӽ�ɫ������
    int increase_attribute;

    // װ���ĵȼ�
    int equipment_level;

    // ����װ��������
    int equipment_cost;

    // ������Ʒ�������麯����������������д��
    virtual void updateDescription() {}
};

// ����Ʒ��
class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {
    }

    // ���ӽ�ɫ��HP
    int add_HP;
};

// ������
class weapon : public equipment
{
public:
    weapon(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // ������Ʒ������
    void updateDescription()
    {
        description = "Increase your attack power by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
    }
};

// ������
class armor :public equipment
{
public:
    armor(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // ������Ʒ������
    void updateDescription() override
    {
        description = "Increase your defense by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
    }
};

// Ь����
class shoes :public equipment
{
public:
    shoes(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // ������Ʒ������
    void updateDescription() override
    {
        description = "Increase your shoes by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
    }
};

// ��Ʒ��
class accessories :public equipment
{
public:
    accessories(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {
    }

    // ���ý�ɫ����
    ElementType setPlayerElementType;

    // ������Ʒ��Ԫ������
    void SetPlayerElementType(ElementType elementType) { setPlayerElementType = elementType; }
};

// �����Ǿ������Ʒ
class goods
{
public:
    // ��Ʒ���ƣ��Ϲ�
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�10������ֵ
    consumable pumkin;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����
    // ���ã�����10�㹥����
    weapon icon_sword;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����
    // ���ã�����5�����ֵ
    armor icon_conselet;

    // ��Ʒ���ƣ�ѥ��
    // ��Ʒ���ࣺЬ��
    // ���ã�����5���ٶ�
    shoes boots;

    // ��Ʒ���ƣ���ҩ
    // ��Ʒ���ࣺ��Ʒ
    // ���ã�����ɫ��Ϊ������
    accessories bomb;

    goods()
        : pumkin("pumpkin", "goods/Pumpkin.png", "Restore your health by 10 points"),   // ��ʼ���Ϲ�
        icon_sword("sword", "goods/sword.png", "Increase your attack power"),  // ��ʼ������
        icon_conselet("conselet", "goods/conselet.png", "Increase your defense"), // ��ʼ������
        boots("boots", "goods/boots.png", "Increase your speed"), // ��ʼ��ѥ��
        bomb("bumb", "goods/bumb.png", "Set your attribute to fire") // ��ʼ����ҩ
    {
        // ������ֵ
        pumkin.add_HP = 10;
        icon_sword.increase_attribute = 10;
        icon_sword.updateDescription();
        icon_conselet.increase_attribute = 5;
        icon_conselet.updateDescription();
        boots.increase_attribute = 5;
        boots.updateDescription();
        bomb.SetPlayerElementType(ElementType::FIRE);
    }
};
#endif