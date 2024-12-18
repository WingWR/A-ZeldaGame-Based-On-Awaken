#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Creature.h"
#include "Item.h"

USING_NS_CC;
using namespace std;

// 触发距离
const int DIST = 150;

struct Bonus {
	//Object object;
	//报错，暂时注释掉
	//Equipment equipment;
	int exp = 0;
};
class Monster;
class Player :public Creature {
private:
	int current_exp;       // 角色现有经验值
	int next_level_exp;    // 达到下一级所需经验值
	vector<Monster*> monster;
protected:
	// 玩家名字在Creature类里已定义了:(	

    //int x, y;       // 坐标
public:
	// 精灵//Creature中有了:( 

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	Player(std::string who, Scene* scene, int x, int y, float scale, int hp, int mp, int atk, int atk_range, int def, int speed, int level) :
		Creature(who, hp, mp, atk, atk_range, def, speed, level, x, y, scale, scene) {
		// 角色现有经验值、达到下一级所需经验值初始化条件记得改
		current_exp = 0;
		next_level_exp = 100;
		_weapon = nullptr;
		_armor = nullptr;
		_shoes = nullptr;
		_accessories = nullptr;
		coins = 1000;
		scene->addChild(this);
		this->scheduleUpdate();
	}
	// 调试用构造函数
	Player() {
		_weapon = nullptr;
		_armor = nullptr;
		_shoes = nullptr;
		_accessories = nullptr;
	
	}
	
	/* 加入怪物 */
	void InitMonster(vector<Monster*>monster);
	
	/* 释放攻击技能 */
	// dir为方向:LEFT RIGHT UP DOWN,默认为DOWN
	// 对于部分怪物,无方向一说:Monster1树妖
	// opp为攻击对象
	virtual Animate* Attack(int dir, vector<Monster*>monster);

	/* 判断交互范围 */
	virtual bool isTrigger(const Vec2& pos);

	// 技能，以组合技形式出现
	//void Combo();

	/* 背包相关 */
	// 角色的武器
	weapon* _weapon;
	// 角色的护甲
	armor* _armor;
	// 角色的鞋子
	shoes* _shoes;
	// 角色的饰品
	accessories* _accessories;
	//获得奖励，参数Bonus结构体,结构体内需含有经验值，物品部分交给背包
	void GetBonus(Bonus bonus);
	// update override
	void update(float dt)override;
	// 角色的金币数
	int coins;
	// 赋值运算符重载
	Player& operator=(const Player& other)
	{
		if (this == &other)  // 自赋值检查
			return *this;
		level = other.level;
		hp = other.hp;
		current_hp = other.current_hp;
		current_mp = other.current_mp;
		atk = other.atk;
		def = other.def;
		speed = other.speed;
		_weapon = other._weapon;
		_armor = other._armor;
		_shoes = other._shoes;
		_accessories = other._accessories;
		coins = other.coins;
		this->setElementType(other.elementType);
		if (other.mySprite != nullptr)
		{
			x = other.getXY().x;
			y = other.getXY().y;
		}
		if (mySprite == nullptr)
		{
			mySprite = Sprite::create("Role/" + other.role + "/1.png");
			mySprite->setVisible(false);
		}

		return *this;
	}
	friend class BagManager;
};

#endif __PLAYER_H__
