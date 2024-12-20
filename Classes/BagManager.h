#pragma once
#ifndef __BAG_MANAGER_H__
#define __BAG_MANAGER_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Item.h"
#include "player.h"
#include "task.h"
#include "ui/CocosGUI.h"

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
    void hideBag(Player& _player);

    // �жϱ����Ƿ�ɼ�
    bool isBagVisible() const { return _isBagOpen; }

    // ����Ʒ��ӵ�����
    void addItem(item* it);


    // ��ȡ��������Ʒ����
    int getItemsNum()
    {
        return items_num;
    }

    // ��������(type:1����/0֧��)
    void taskUnlock(const bool type, const int idx);

    // ��������״̬Ϊ�����(type:1����/0֧��)
    void taskFinish(const bool type, const int idx);

    task* Mtask1 = new task("Task 1", "This is the 1st Mtask.", 1, 0);
    task* Mtask2 = new task("Task 2", "This is the 2nd Mtask.", 1, 0);
    task* Mtask3 = new task("Task 3", "This is the 3rd Mtask.", 1, 0);
    task* Mtask4 = new task("Task 4", "This is the 4th Mtask.", 1, 0);
    task* Mtask5 = new task("Final Task", "This is the 5th Mtask.", 1, 0);

    task* Ltask1 = new task("Task 1", "This is the 1st Ltask.", 0, 0);
    task* Ltask2 = new task("Task 2", "This is the 2nd Ltask.", 0, 0);
    task* Ltask3 = new task("Task 3", "This is the 3rd Ltask.", 0, 0);
    task* Ltask4 = new task("Task 4", "This is the 4th Ltask.", 0, 0);
    task* Ltask5 = new task("Task 5", "This is the 5th Ltask.", 0, 0);
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

    // ������屳��
    cocos2d::Sprite* _taskBackground;

    // ��̬��Ա���������ڴ洢����ʵ��
    static BagManager* _instance;

    // ������������
    void createBagBackground();

    // ������ɫ���
    void createCharacterPanel();

    // ���ƽ�ɫ���UI
    void createCharacterPanelUI();

    // ��ʾ��ɫ��Ϣ
    void showCharacterInfo();

    // �����Ʒ���¼�
    void slot_click(Button* slot, int row, int col);

    // ���������ڵ���Ʒ
    void discardItems(int index);

    // �������ڵ���Ʒװ��
    void equipItem(int index);

    // ���±���UI
    void updateBagUI();

    // ������������尴ť
    void createTaskButton();

    // �����������
    void createTaskPanel();

    // ���� ScrollView
    void createScrollView(Vec2 position, vector<task*> myTask);

    // ����������Ϣ���
    void createTaskInfoPanel(vector<task*> myTask, int index);

    // ���ܵ���������
    vector<task*> myMainlineTask;
    
    // ���ܵ�֧������
    vector<task*> myLineQuest;

    // �����������UI
    void updateTaskUI();

    // ��ʾ�������
    void showcoins();

    // ��ʾ��������ı�ǩ
    cocos2d::Label* coinsLabel;

    // ��ֹ�������캯���͸�ֵ������
    BagManager(const BagManager&) = delete;
    BagManager& operator=(const BagManager&) = delete;
};

#endif  __BAG_MANAGER_H__
