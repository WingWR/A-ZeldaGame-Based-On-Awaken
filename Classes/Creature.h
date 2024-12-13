#ifndef __CREATURE_H__
#define __CREATURE_H__
#include "cocos2d.h"

USING_NS_CC;

/* 方向 */
enum dir {
	LEFT,    // 0
	RIGHT,   // 1
	UP,      // 2
	DOWN     // 3
};

/* 生物基类 */
class Creature :public Node {
protected:
	std::string role;   // 角色名:用于检索图片素材

	bool isDead;      // 生死状态
	int hp;           // 总生命
	int current_hp;   // 现生命
	int mp;           // 总魔力
	int current_mp;   // 现魔力
	int atk;          // 基础攻击值
	int atk_range;    // 攻击范围
	int def;          // 基础防御值
	int speed;        // 速度
	int level;        // 等级
	int x, y;         // 初始坐标

	float scale;      // 缩放比例
	Scene* scene;     // 场景指针
public:
	Sprite* mySprite; // 精灵
	int face_to;      // 面朝方向

	/* 构造函数 */
	// who:玩家为Player1~Player5,NPC为npc1~npc5
	// 建议:speed默认设为50,atk_range默认设100
	Creature(std::string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y, float scale, Scene* scene) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level), scale(scale),
		face_to(DOWN), isDead(false), scene(scene), mySprite(nullptr), current_hp(hp), current_mp(mp),x(x),y(y) {
		
		// 精灵初始化
		mySprite = Sprite::create("Role/" + role + "/1.png");
		mySprite->setPosition(Vec2(x, y));
		mySprite->setScale(scale);
		scene->addChild(mySprite);

		levelBonus();
	}

	// 空的构造函数，供调试
	Creature() {
		scale = 1.0f;
		scene = nullptr;
		face_to = DOWN;
		mySprite = nullptr;
		isDead = false;
		hp = 1;
		current_hp = 1;
		mp = 1;
		current_mp = 1;
		atk = 1;
		atk_range = 20;
		def = 1;
		speed = 10;
		level = 1;
	}

	/* 释放攻击技能 */
	// dir为方向:LEFT RIGHT UP DOWN,默认为DOWN
	// 对于部分怪物,无方向一说:Monster1树妖
	// opp为攻击对象
	virtual void Attack(int dir = DOWN, Creature* opp = nullptr);

	/* 受伤 */
	virtual void Hurt();

	/* 死亡 */
	// 死亡后移动、攻击技能均被锁定，直至复活
	virtual void Die();

	/* 复活 */
	virtual void Revive();

	/* 恢复 */
	virtual void Heal();

	/* 移动 */
	// Monster1:树妖,无法移动
	virtual void Move(int dir);

	/* 转变场景 */
	//需要修改，与地图对接，需要地图类返回GetScene的值（一个类型为Scene*的scene)
	virtual void ChangeScene(Scene* sc) { scene = sc; }

	/* 等级加成 */
	virtual void levelBonus();

	/* 计算伤害 */
	int DamageCal(Creature*, Creature*);
	
	/* 返回变量值 */
	// 返回速度speed
	int getSpeed()const { return speed; }
	// 返回总hp
	int getHp()const { return hp; }
	// 返回现hp
	int getCurrentHp()const{ return current_hp; }
	// 返回总mp
	int getMp()const{ return mp; }
	// 返回现mp
	int getCurrentMp()const{ return current_mp; }
	// 返回atk
	int getAtk()const{ return atk; }
	// 返回def
	int getDef()const{ return def; }
	// 返回攻击范围atk_range
	int getAtkRange()const { return atk_range; }

	// 返回坐标
	Vec2 getXY()const { return Vec2(mySprite->getPosition().x, mySprite->getPosition().y); }
	// 更新坐标
	void updateXY() {
		x = mySprite->getPosition().x;
		y = mySprite->getPosition().y;
	}
};
#endif __CREATURE_H__
