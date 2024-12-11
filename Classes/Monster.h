
#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include "Creature.h"
#include "Player.h"
USING_NS_CC;
#define DELTATIME 1/60// Ĭ�ϵ�֡��
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
		MonsterState state, int exp, Bonus bonus, Player* player, int follow_range,float scale,Scene*scene) :
		Creature(name, hp, mp, atk, atk_range, def, speed, level, x, y,scale,scene),
		base_exp(exp), bonus(bonus), follow_range(follow_range),state(state) {
		levelBonus();
		bonus.exp = base_exp;
		;//�ݴ�
		target = player;
		//��ҪGameScene��������һ��
		// this->scheduleUpdate();
	}
	void update(float dt)override;
	void levelBonus()override;
	//����
	void Die()override;
	// ִ��Ѳ���߼�
	void Patrol();
	// ׷��
	void Chase();
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
#endif __MONSTER_H__

