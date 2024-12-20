
#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include "Creature.h"
#include "Player.h"
USING_NS_CC;

using namespace std;


enum class State {
	IDLE, //空闲，静止，用于Npc
	WALKING, //行走，随机，用于Npc和怪物
	COMBATING // 战斗，用于怪物
};
enum class MonsterState {
	PATROLLING,//巡逻
	CHASE,//追踪
	ATTACK,//攻击
	FLEE//逃跑
};

//怪物AI类
class MonsterAI :Node {
private:
	MonsterState currentState;//怪物状态
	Player* target;
	Monster* monster;
	float distance;
public:
	friend class Monster;
	MonsterAI(Player* target, Monster* monster) : currentState(MonsterState::PATROLLING), target(target), monster(monster) {}//默认为巡逻
	//判断是否巡逻
	bool shouldPatrol();
	//判断是否追踪
	bool shouldChasePlayer();
	//判断是否攻击
	bool shouldAttackPlayer();
	//判断是否逃跑
	bool shouldFlee();
	//update函数
	void update(float dt) override;
	//返回现状态
	MonsterState GetState()const;
};

//怪物类
class Monster :public Creature {

private:
	
	int follow_range;
	Bonus bonus;//击杀奖励
	int base_exp;//怪物的基础经验值
	Player* target;
	MonsterAI* ai;
	MonsterState state;
	Vec2 direction;
public:
	
	Monster(string name, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y,
		int exp, Bonus bonus, Player* player, int follow_range, float scale, Scene* scene) :
		Creature(name, hp, mp, atk, atk_range, def, speed, level, x, y, scale, scene),
		base_exp(exp), bonus(bonus), follow_range(follow_range),
		ai(new MonsterAI(player, this)), state(MonsterState::PATROLLING) {
		ai->scheduleUpdate();
		levelBonus();
		bonus.exp = base_exp;
		;//暂待
		target = player;


		this->scheduleUpdate();
	}
	Monster() {
		role = "Monster2";
		hp = 100000;
		mp = 600;
		atk = 20;
		atk_range = 40;
		def = 20;
		speed = 100;
		level = 2;
		x = 1000;
		y = 100;
	}
	void update(float dt)override;
	void levelBonus()override;
	//死亡
	void Die()override;
	//攻击
	void Attack()override;
	// 执行巡逻逻辑
	void Patrol();
	// 追踪
	void Chase();
	//逃跑
	void Flee();
	//寻路，徘徊，或静止
	// 返回follow_range
	int GetFollowRange()const;

};
// 怪物刷新类
// 在此定义怪的种类
class MonsterRespawn:Node {
	vector<Monster*> monster;
	Monster* monster1;
	Monster* monster2;
public:
	
	MonsterRespawn(Player* player, Scene* scene) {
		// name,hp,mp,atk,atk_range,def,speed,level,x,y,exp,bonus,player,follow_range,scale,scene) :
		Bonus b;
		monster1 = new Monster("Monster1", 100000, 600, 20, 40, 20, 100, 2, 1000, 100, 0, b, player, 1000, 1, scene);
		monster2 = new Monster("Monster2", 100000, 600, 20, 40, 20, 100, 2, 1000, 100, 0, b, player, 1000, 1, scene);
		monster.push_back(monster1);
		monster.push_back(monster2);
		scene->addChild(monster1);
		scene->addChild(monster2);
		this->scheduleUpdate();
	}
	void update(float dt)override;
	vector<Monster*>GetMonster() {
		return monster;
	}
};
#endif __MONSTER_H__

