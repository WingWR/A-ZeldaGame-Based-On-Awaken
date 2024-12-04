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

    // ���캯������Ҫ����Ʒ�����ֳ�Ա������ֵ
    item(const string& itemName, const string& imagePath, const string& itemDescription)
        : name(itemName), description(itemDescription)
    {
        image = cocos2d::Sprite::create(imagePath); // ������ƷͼƬ
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

    // ��Ʒ���ӹ���
    void itemFunction()
    {

    }
    // ���������������ʹ�����Ϊ��̬��
    virtual ~item() {}
};
// 
class equipment:public item
{
public:
    equipment(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    void equip();
};

class consumable : public item
{
public:
    consumable(const string& itemName, const string& imagePath, const string& itemDescription)
        : item(itemName, imagePath, itemDescription) {}
    void consume();
};
#endif