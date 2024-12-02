#pragma once
#ifndef __BAG_MANAGER_H__
#define __BAG_MANAGER_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Item.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class BagManager : public cocos2d::Node 
{
public:
    // ��ȡ����ʵ��
    static BagManager* getInstance();

    // ��ʼ������������
    bool init();

    // ��ʾ����
    void showBag();

    // ���ر���
    void hideBag();

    // �жϱ����Ƿ�ɼ�
    bool isBagVisible() const { return _isBagOpen; }

    //���±���UI
    void updateBagUI();

private:
    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
    BagManager();
    // ��������
    ~BagManager();

    // ��������ʾ״̬
    bool _isBagOpen;

    // �����ڵ���Ʒ
    item* items[40];

    // ������UI���
    cocos2d::Node* _bagPanel;

    // ��������
    cocos2d::Sprite* _bagBackground;

    // ��ɫ��屳��
    cocos2d::Sprite* _characterBackground;

    // ��̬��Ա���������ڴ洢����ʵ��
    static BagManager* _instance;

    // ������������
    void createBagBackground();

    // ������ɫ���
    void createCharacterPanel();

    // ��ֹ�������캯���͸�ֵ������
    BagManager(const BagManager&) = delete;
    BagManager& operator=(const BagManager&) = delete;
};

#endif // __BAG_MANAGER_H__
