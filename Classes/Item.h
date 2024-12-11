#pragma once
#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"

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

    // ��ֵ���������
    item& operator=(const item& other)
    {
        if (this != &other) // �������Ҹ�ֵ
        {  
            // ���ƻ�����Ա
            name = other.name;
            description = other.description;
            image = cocos2d::Sprite::create(other.imageName);  // �����¸���
        }
        return *this;
    }

    // ���������������ʹ�����Ϊ��̬��
    virtual ~item() {}
};
// װ����
class equipment:public item
{
public:
    equipment(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    // ���������������ʹ�����Ϊ��̬��
    virtual ~equipment() {}
};

// ����Ʒ��
class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    int add_HP;

    // ��ֵ���������
    consumable& operator=(const consumable& other) 
    {
        if (this != &other) // �������Ҹ�ֵ
        {  
            // ��ֵ���� item �ĳ�Ա
            item::operator=(other);
            // ��ֵ consumable ��ĳ�Ա
            add_HP = other.add_HP;
        }
        return *this;
    }
};

// ������
class weapon : public equipment
{
public:
   weapon(const string& itemName, const string& imagePath, const string& itemDescription)
       : equipment(itemName, imagePath, itemDescription) {}
   // ���ӽ�ɫ�Ĺ�����
   int increase_attack;

   // ��ֵ���������
   weapon& operator=(const weapon& other)
   {
       if (this != &other) // �������Ҹ�ֵ
       {
           // ��ֵ���� item �ĳ�Ա
           item::operator=(other);
           // ��ֵ weapon ��ĳ�Ա
           increase_attack = other.increase_attack;
       }
       return *this;
   }
};

// ������
class armor :public equipment
{
public:
    armor(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}
    // ���ӽ�ɫ�ķ���ֵ
    int increase_defense;

    // ��ֵ���������
    armor& operator=(const armor& other)
    {
        if (this != &other) // �������Ҹ�ֵ
        {
            // ��ֵ���� item �ĳ�Ա
            item::operator=(other);
            // ��ֵ armor ��ĳ�Ա
            increase_defense = other.increase_defense;
        }
        return *this;
    }
};

// Ь����
class shoes :public equipment
{
public:
    shoes(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) {}
    // ���ӽ�ɫ���ٶ�
    int increase_speed;

    // ��ֵ���������
    shoes& operator=(const shoes& other)
    {
        if (this != &other) // �������Ҹ�ֵ
        {
            // ��ֵ���� item �ĳ�Ա
            item::operator=(other);
            // ��ֵ shoes ��ĳ�Ա
            increase_speed = other.increase_speed;
        }
        return *this;
    }
};

// ��Ʒ��
class accessories :public equipment
{
public:
    accessories(const string& itemName, const string& imagePath, const string& itemDescription)
        : equipment(itemName, imagePath, itemDescription) 
    {
        increase_attack = 0;
        increase_defense = 0;
        increase_speed = 0;
    }
    // ���ӽ�ɫ�Ĺ�����
    int increase_attack;
    // ���ӽ�ɫ�ķ���ֵ
    int increase_defense;
    // ���ӽ�ɫ���ٶ�
    int increase_speed;

    // ��ֵ���������
    accessories& operator=(const accessories& other)
    {
        if (this != &other) // �������Ҹ�ֵ
        {
            // ��ֵ���� item �ĳ�Ա
            item::operator=(other);
            // ��ֵ accessories ��ĳ�Ա
            increase_attack = other.increase_attack;
            increase_defense = other.increase_defense;
            increase_speed = other.increase_speed;
        }
        return *this;
    }
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
    // ���ã�����20�㹥������3���ٶ�
    accessories bomb;

    goods()
        : pumkin("pumpkin", "Pumpkin.png", "Restore your health"),   // ��ʼ���Ϲ�
        icon_sword("sword", "sword.png", "Increase your attack power"),  // ��ʼ������
        icon_conselet("conselet", "conselet.png", "Increase your defense"), // ��ʼ������
        boots("boots", "boots.png", "Increase your speed"), // ��ʼ��ѥ��
        bomb("bumb", "bumb.png", "Increase your attack power") // ��ʼ����ҩ
    {
        // ������ֵ
        pumkin.add_HP = 10;  
        icon_sword.increase_attack = 10;  
        icon_conselet.increase_defense = 5; 
        boots.increase_speed = 5;
        bomb.increase_attack = 20;
        bomb.increase_speed = 3;
    }
};
#endif