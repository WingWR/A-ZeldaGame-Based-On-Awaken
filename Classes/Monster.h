
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
class Monster;
//����AI��
class MonsterAI:Node {
private:
	MonsterState currentState;//����״̬
	Player* target;
	Monster* monster;

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
	void update(float dt)override;
	void levelBonus()override;
	//����
	void Die()override;
	//����
	void Attack();
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

#endif __MONSTER_H__

