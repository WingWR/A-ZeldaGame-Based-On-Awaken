#pragma once
#ifndef __BAG_MANAGER_H__
#define __BAG_MANAGER_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Item.h"
#include "player.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class BagManager : public cocos2d::Node 
{
public:
    // ��ȡ����ʵ��
    static BagManager* getInstance();

    // ��ʾ����
    void showBag(Player& _player);

    // ���ر���
    void hideBag();

    // �жϱ����Ƿ�ɼ�
    bool isBagVisible() const { return _isBagOpen; }

    // ����Ʒ��ӵ�����
    void addItem(item* it);


    // ��ȡ��������Ʒ����
    int getItemsNum()
    {
        return items_num;
    }
private:
    // ��ʼ������������
    bool init();

    // ˽�й��캯������ֹ�ⲿֱ��ʵ����
    BagManager();

    // ��������
    ~BagManager();

    // ʹ�ñ����Ľ�ɫ
    Player player;

    // ��������ʾ״̬
    bool _isBagOpen;

    // �����ڵ���Ʒ
    item* items[40];

    // ��������Ʒ����
    int items_num;

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

    // �����Ʒ���¼�
    void slot_click(Button* slot, int row, int col);

    // ���������ڵ���Ʒ
    void discardItems(int index);

    // �������ڵ���Ʒװ��
    void equipItem(int index);

    // ���±���UI
    void updateBagUI();

    // ��ֹ�������캯���͸�ֵ������
    BagManager(const BagManager&) = delete;
    BagManager& operator=(const BagManager&) = delete;
};

#endif // __BAG_MANAGER_H__
