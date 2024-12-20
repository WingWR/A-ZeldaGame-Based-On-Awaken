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
        equipment_levelMax = 10;
    }

    // ���������������ʹ�����Ϊ��̬��
    virtual ~equipment() {}

    // ���ӽ�ɫ������
    int increase_attribute;

    // װ���ĵȼ�
    int equipment_level;

    // װ�������ȼ�
    int equipment_levelMax;

    // ����װ��������
    int equipment_cost;

    // ������Ʒ�������麯����������������д��
    virtual void updateDescription(){}
};

// ����Ʒ��
class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}

    // ���ӽ�ɫ��HP
    int add_HP;
};

// ������
class weapon : public equipment
{
public:
    weapon(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}

    // ������Ʒ������
    void updateDescription()
    {
        if (increase_criticalChance <= 0)
            description = "Increase your attack power by " + to_string(this->increase_attribute) + " points\nLevel: " + to_string(equipment_level) + "\nUpgrade needs: " + to_string(equipment_cost);
        else
            description = "Increase your attack power by " + to_string(this->increase_attribute) + " points and increase your critical chance by " + to_string(int(this->increase_criticalChance * 100)) + "%\nLevel: " + to_string(equipment_level) + "\nUpgrade needs : " + to_string(equipment_cost);
    }

    // ����������
    float increase_criticalChance = 0.0f;
};

// ������
class armor :public equipment
{
public:
    armor(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}
    
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
        : equipment(itemName, imagePath, itemDescription) {}

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
        : equipment(itemName, imagePath, itemDescription){} 

    // ���ý�ɫ����
    ElementType setPlayerElementType;

    // ������Ʒ��Ԫ������
    void SetPlayerElementType(ElementType elementType) { setPlayerElementType = elementType; }
};

// �����Ǿ������Ʒ
class goods
{
public:
    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����
    // ���ã�����10�㹥����
    weapon icon_sword;

    // ��Ʒ���ƣ���
    // ��Ʒ���ࣺ����
    // ���ã�����20�㹥������10%������
    weapon great_sword;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����
    // ���ã�����30�㹥����
    weapon long_sword;

    // ��Ʒ���ƣ�ذ��
    // ��Ʒ���ࣺ����
    // ���ã�����10�㹥������25%������
    weapon dagger;
    
    // ��Ʒ���ƣ�����֮��
    // ��Ʒ���ࣺ����
    // ���ã�����50�㹥������50%������
    weapon final_weapon;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����
    // ���ã�����5�����ֵ
    armor icon_conselet;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����
    // ���ã�����20�����ֵ
    armor shield;

    // ��Ʒ���ƣ�ͷ��
    // ��Ʒ���ࣺ����
    // ���ã�����15�����ֵ
    armor helmet;

    // ��Ʒ���ƣ�����֮��
    // ��Ʒ���ࣺ����
    // ���ã�����50�����ֵ
    armor final_armor;

    // ��Ʒ���ƣ�ѥ��
    // ��Ʒ���ࣺЬ��
    // ���ã�����5���ٶ�
    shoes boots;

    // ��Ʒ���ƣ���ʯѥ
    // ��Ʒ���ࣺЬ��
    // ���ã�����7���ٶ�
    shoes diamond_shoes;

    // ��Ʒ���ࣺ����֮ѥ
    // ��Ʒ���ࣺЬ��
    // ���ã�����12���ٶ�
    shoes final_shoes;

    // ��Ʒ���ƣ������ָ
    // ��Ʒ���ࣺ��Ʒ
    // ���ã������ɫ����Ϊ������
    accessories fire_ring;

    // ��Ʒ���ƣ���������
    // ��Ʒ���ࣺ��Ʒ
    // ���ã�����ɫ����Ϊ������
    accessories ice_nacklace;

    // ��Ʒ���ƣ�ɭ��Ȩ��
    // ��Ʒ���ࣺ��Ʒ
    // ���ã�����ɫ����Ϊ������
    accessories forest_scepter;
    // ��Ʒ���ƣ���ʯ����
    // ��Ʒ���ࣺ��Ʒ
    // ���ã�����ɫ����Ϊ������
    accessories rack_cape;

    // ��Ʒ���ƣ��Ϲ�
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�10������ֵ
    consumable pumkin;

    // ��Ʒ���ƣ�ƻ��
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�5������ֵ
    consumable apple;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�15������ֵ
    consumable cheese;

    // ��Ʒ���ƣ�����
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�20������ֵ
    consumable chicken_leg;

    // ��Ʒ���ƣ�ơ��
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�10������ֵ
    consumable beer;

    // ��Ʒ���ƣ�����ҩˮ
    // ��Ʒ���ࣺ����Ʒ
    // ���ã��ָ�50������ֵ
    consumable life_potion;
    goods()
        : pumkin("pumpkin", "goods/Pumpkin.png", "Restore your health by 10 points"),
        icon_sword("sword", "goods/sword.png", "Increase your attack power"),
        icon_conselet("conselet", "goods/conselet.png", "Increase your defense"),
        boots("boots", "goods/boots.png", "Increase your speed"),
        great_sword("great sword", "goods/great_sword.png", "Increase your attack power"),
        long_sword("long sword", "goods/long_sword.png", "Increase your attack power"),
        dagger("dagger", "goods/dagger.png", "Increase your attack power and critical chance"),
        final_weapon("final sword", "goods/final_sword.png", "Increase your attack power and critical chance"),
        shield("shield", "goods/shield.png", "Increase your defense"),
        helmet("helmet", "goods/helmet.png", "Increase your defense"),
        final_armor("final armor", "goods/final_armor.png", "Increase your defense"),
        diamond_shoes("diamond shoes", "goods/diamond_shoes.png", "Increase your speed"),
        final_shoes("final shoes", "goods/final_shoes.png", "Increase your speed"),
        fire_ring("fire ring", "goods/fire_ring.png", "Set your element to Fire"),
        ice_nacklace("ice necklace", "goods/ice_nacklace.png", "Set your element to Ice"),
        forest_scepter("forest scepter", "goods/forest_scepter.png", "Set your element to Earth"),
        rack_cape("rack cape", "goods/rack_cape.png", "Set your element to Rock"),
        apple("apple", "goods/apple.png", "Restore your health by 5 points"),
        cheese("cheese", "goods/cheese.png", "Restore your health by 15 points"),
        chicken_leg("chicken_leg", "goods/chicken_leg.png", "Restore your health by 20 points"),
        beer("beer", "goods/beer.png", "Restore your health by 10 points"),
        life_potion("life potion", "goods/life_potion.png", "Restore your health by 50 points")
    {
        // ������ֵ
        pumkin.add_HP = 10;
        apple.add_HP = 5;
        cheese.add_HP = 15;
        chicken_leg.add_HP = 20;
        beer.add_HP = 10;
        life_potion.add_HP = 50;

        icon_sword.increase_attribute = 10;
        icon_sword.updateDescription();

        great_sword.increase_attribute = 20;
        great_sword.increase_criticalChance = 0.1f;
        great_sword.updateDescription();

        long_sword.increase_attribute = 30;
        long_sword.updateDescription();

        dagger.increase_attribute = 10;
        dagger.increase_criticalChance = 0.25f;
        dagger.updateDescription();

        final_weapon.increase_attribute = 50;
        final_weapon.increase_criticalChance = 0.5f;
        final_weapon.updateDescription();

        icon_conselet.increase_attribute = 5;
        icon_conselet.updateDescription();

        shield.increase_attribute = 20;
        shield.updateDescription();

        helmet.increase_attribute = 15;
        helmet.updateDescription();

        final_armor.increase_attribute = 50;
        final_armor.updateDescription();

        boots.increase_attribute = 5;
        boots.updateDescription();

        diamond_shoes.increase_attribute = 7;
        diamond_shoes.updateDescription();

        final_shoes.increase_attribute = 12;
        final_shoes.updateDescription();

        fire_ring.SetPlayerElementType(ElementType::FIRE);
        ice_nacklace.SetPlayerElementType(ElementType::ICE);
        forest_scepter.SetPlayerElementType(ElementType::GRASS);
        rack_cape.SetPlayerElementType(ElementType::ROCK);
    }
};
#endif