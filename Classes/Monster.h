
#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include "Creature.h"
#include "Player.h"
USING_NS_CC;

using namespace std;


enum class State {
	IDLE, //���У���ֹ������Npc
	WALKING, //���ߣ����������Npc�͹���
	COMBATING // ս�������ڹ���
};
enum class MonsterState {
	PATROLLING,//Ѳ��
	CHASE,//׷��
	ATTACK,//����
	FLEE//����
};

//����AI��
class MonsterAI :Node {
private:
	MonsterState currentState;//����״̬
	Player* target;
	Monster* monster;
	float distance;
public:
	friend class Monster;
	MonsterAI(Player* target, Monster* monster) : currentState(MonsterState::PATROLLING), target(target), monster(monster) {}//Ĭ��ΪѲ��
	//�ж��Ƿ�Ѳ��
	bool shouldPatrol();
	//�ж��Ƿ�׷��
	bool shouldChasePlayer();
	//�ж��Ƿ񹥻�
	bool shouldAttackPlayer();
	//�ж��Ƿ�����
	bool shouldFlee();
	//update����
	void update(float dt) override;
	//������״̬
	MonsterState GetState()const;
};

//������
class Monster :public Creature {

private:
	
	int follow_range;
	Bonus bonus;//��ɱ����
	int base_exp;//����Ļ�������ֵ
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
		;//�ݴ�
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
	//����
	void Die()override;
	//����
	void Attack()override;
	// ִ��Ѳ���߼�
	void Patrol();
	// ׷��
	void Chase();
	//����
	void Flee();
	//Ѱ·���ǻ�����ֹ
	// ����follow_range
	int GetFollowRange()const;

};
// ����ˢ����
// �ڴ˶���ֵ�����
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

