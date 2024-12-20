#pragma once
#ifndef __BAG_MANAGER_H__
#define __BAG_MANAGER_H__

#include "cocos2d.h"
#include <string>
#include <vector>
#include "Item.h"
#include "player.h"
#include "task.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class BagManager : public cocos2d::Node 
{
public:
    // 获取单例实例
    static BagManager* getInstance();

    // 显示背包
    void showBag(Player& _player);

    // 隐藏背包
    void hideBag(Player& _player);

    // 判断背包是否可见
    bool isBagVisible() const { return _isBagOpen; }

    // 将物品添加到背包
    void addItem(item* it);


    // 获取背包内物品数量
    int getItemsNum()
    {
        return items_num;
    }

    /**********************lq-edit**********************/
    // 解锁任务(type:1主线/0支线)
    void taskUnlock(const bool type, const int idx);

    // 设置任务状态为已完成(type:1主线/0支线)
    void taskFinish(const bool type, const int idx);

    /************************end************************/
private:
    // 初始化背包管理器
    bool init();

    // 私有构造函数，禁止外部直接实例化
    BagManager();

    // 析构函数
    ~BagManager();

    // 使用背包的角色
    Player player;

    // 背包的显示状态
    bool _isBagOpen;

    // 背包内的物品
    item* items[40];

    // 背包内物品数量
    int items_num;

    // 背包的UI面板
    cocos2d::Node* _bagPanel;

    // 背包背景
    cocos2d::Sprite* _bagBackground;

    // 角色面板背景
    cocos2d::Sprite* _characterBackground;

    // 任务面板背景
    cocos2d::Sprite* _taskBackground;

    // 静态成员变量，用于存储单例实例
    static BagManager* _instance;

    // 创建背包背景
    void createBagBackground();

    // 创建角色面板
    void createCharacterPanel();

    // 点击物品栏事件
    void slot_click(Button* slot, int row, int col);

    // 丢弃背包内的物品
    void discardItems(int index);

    // 将背包内的物品装备
    void equipItem(int index);

    // 更新背包UI
    void updateBagUI();

    // 创建打开任务面板按钮
    void createTaskButton();

    // 创建任务面板
    void createTaskPanel();

    // 接受的主线任务
    vector<task*> myMainlineTask;
    
    // 接受的支线任务
    vector<task*> myLineQuest;

    // 更新任务界面UI
    void updateTaskUI();

    // 显示金币数量
    void showcoins();

    // 显示金币数量的标签
    cocos2d::Label* coinsLabel;

    // 禁止拷贝构造函数和赋值操作符
    BagManager(const BagManager&) = delete;
    BagManager& operator=(const BagManager&) = delete;
};

#endif  __BAG_MANAGER_H__
