
#ifndef __Combat_System_H__
#define __Combat_System_H__
#include "cocos2d.h"
#include "Player.h"
USING_NS_CC;
#define deltatime 1/60// Ĭ�ϵ�֡��
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


//������
class Monster :public Creature {
private:
	int follow_range;
	Bonus bonus;//��ɱ����
	int base_exp;//����Ļ�������ֵ
	Player* target;
	MonsterAI ai{ target,this };
	MonsterState state;
public:
	Monster(string name, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y,
		MonsterState state, int exp, Bonus bonus, Player* player, int follow_range) :
		Creature(name, hp, mp, atk, atk_range, def, speed, level, x, y),
		base_exp(exp), bonus(bonus), follow_range(follow_range),state(state) {
		Level_Bonus();
		bonus.exp = base_exp;
		;//�ݴ�
		target = player;
		//��ҪGameScene��������һ��
		// this->scheduleUpdate();
	}
	void update(float dt)override;
	void Level_Bonus()override;
	//����
	void Die()override;
	// ִ��Ѳ���߼�
	void Patrol();
	// ׷��
	void Chase();
	// �������
	void Attack();
	//Ѱ·���ǻ�����ֹ
	// ����follow_range
	int GetFollowRange()const;

};
//����AI��
class MonsterAI {
private:
	MonsterState currentState;//����״̬
	Player* target;
	Monster* monster;

public:
	MonsterAI(Player* target,Monster*monster) : currentState(MonsterState::PATROLLING), target(target),monster(monster) {}//Ĭ��ΪѲ��
	//�ж��Ƿ�׷��
	bool shouldChasePlayer();
	//�ж��Ƿ񹥻�
	bool shouldAttackPlayer();
	//�ж��Ƿ�����
	bool shouldFlee();
	//update����
	void update(float dt);
	//������״̬
	MonsterState GetState()const;
};
#endif// __Combat_System_H__

