#ifndef __CREATURE_H__
#define __CREATURE_H__
#include "cocos2d.h"
#include <vector>
#include "ElementType.h"

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
	/************************** protected **************************/
protected:
	std::string role; // 角色名:用于检索图片素材

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
	int x, y;         // 位置
	ElementType elementType; // 属性

	float scale;      // 缩放比例
	Scene* scene;     // 场景指针

	/************************** public **************************/
public:
	/* 精灵相关 */
	Sprite* mySprite; // 精灵
	int face_to;      // 面朝方向

	/* 碰撞相关 */
	bool canMove = true;                   // 是否可移动
	Size collisionBoxSize = Size(0, 0);    // 碰撞框大小
	Vec2 collisionBoxOffset = Vec2(0, 0);  // 碰撞框偏移量
	Rect getCollisionRect() const;         // 获取碰撞框
	bool isCollision(const Rect& rect1, const Rect& rect2);        // 判断碰撞
	void preventOverlap(Creature* creature1, Creature* creature2); // 防止碰撞
	void Creature::drawCollisionBox();     // 画碰撞框:调试用

	/* 构造函数 */
	Creature(std::string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y, float scale, Scene* scene) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level), scale(scale),
		face_to(DOWN), isDead(false), scene(scene), mySprite(nullptr), current_hp(hp), current_mp(mp), x(x), y(y) {
		// 初始化精灵
		initSprite();
		// 初始元素为无
		this->setElementType(NONE);
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

	/* 初始化精灵 */
	void initSprite();

	/* 释放攻击技能 */
	// opp为攻击对象
	
	virtual void Attack();
	int getDir() { return face_to; }

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
	virtual void Move(int dir);
	virtual void learnMove(int dir);


	/* 转变场景 */
	//需要修改，与地图对接，需要地图类返回GetScene的值（一个类型为Scene*的scene)
	virtual void ChangeScene(Scene* sc) { scene = sc; }

	/* 等级加成 */
	virtual void levelBonus();

	/* 计算伤害 */
	int DamageCal(Creature*, Creature*);

	/* 返回变量值 */
	bool ChangeIsDead(bool change) { isDead = change; }
	bool getIsDead() { return isDead; }            // 返回是否死亡
	int getSpeed()const { return speed; }          // 返回速度speed
	int getHp()const { return hp; }                // 返回总hp
	int getCurrentHp()const { return current_hp; } // 返回现hp
	int getMp()const { return mp; }                // 返回总mp
	int getCurrentMp()const { return current_mp; } // 返回现mp
	int getAtk()const { return atk; }              // 返回atk
	int getDef()const { return def; }              // 返回def
	int getAtkRange()const { return atk_range; }   // 返回攻击范围atk_range
	bool getIsDead()const { return isDead; }       // 返回是否死亡
	/* 设置属性 */
	void setElementType(ElementType _elementType);
	// 改变XY
	void ChangeXY(Vec2 change);
	// 返回坐标

	/* 坐标相关操作 */

	Vec2 getXY()const { return Vec2(mySprite->getPosition().x, mySprite->getPosition().y); }
	//改变face_tp
	void ChangeFaceTo(int face_to) { this->face_to = face_to; }
	//减血
	void DecreaseHp(int damage) { current_hp -= damage; }
};

#endif __CREATURE_H__