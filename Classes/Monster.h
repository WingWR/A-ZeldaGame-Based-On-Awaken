#ifndef __MONSTER_H__
#define __MONSTER_H__
#include "cocos2d.h"
#include "Creature.h"
#include "Player.h"
#include "MapManager.h"
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
	MapManager* mapManager;
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
	void Init(MapManager* mapManager) {
		this->mapManager = mapManager;
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
// ���ｱ��
class MonsterBonus {
public:
	friend class MonsterRespawn;
	Bonus monster_bonus1;
	Bonus monster_bonus2;
	Bonus monster_bonus3;
	Bonus monster_bonus4;
	Bonus monster_bonus5;
	Bonus monster_bonus6;
	Bonus monster_bonus7;
	Bonus monster_bonus8;
public:
	MonsterBonus() {
		monster_bonus1.exp = 100;
		monster_bonus2.exp = 200;
		monster_bonus3.exp = 300;
		monster_bonus4.exp = 400;
		monster_bonus5.exp = 500;
		monster_bonus6.exp = 100;
		monster_bonus7.exp = 200;
		monster_bonus8.exp = 300;
		monster_bonus1.coin = 100;
		monster_bonus2.coin = 200;
		monster_bonus3.coin = 300;
		monster_bonus4.coin = 400;
		monster_bonus5.coin = 500;
		monster_bonus6.coin = 100;
		monster_bonus7.coin = 200;
		monster_bonus8.coin = 300;
	}
};
// ����ˢ����
// �ڴ˶���ֵ�����
class MonsterRespawn:Node {
	vector<Monster*> monster;
	vector<Vec2> monster_pos;
	Monster* monster1;
	Monster* monster2;
	Monster* monster3;
	Monster* monster4;
	Monster* monster5;
	Monster* monster6;
	Monster* monster7;
	Monster* monster8;
	MapManager* mapManager;
	int DoorID;

public:
	
	MonsterRespawn(Player* player, Scene* scene,MapManager*mapManager,int DoorID) {
		Size VisibleSize = Director::getInstance()->getVisibleSize();
		// name,hp,mp,atk,atk_range,def,speed,level,x,y,exp,bonus,player,follow_range,scale,scene) :
		MonsterBonus bonus;
		if (DoorID == 0) {
			//��ɽ����
			monster5 = new Monster("Monster5", 1000, 600, 20, 100, 5, 100, 2, -1230.8f, 3366.5f, 100, bonus.monster_bonus5, player, 500, 1.0f, scene);
			monster5->Init(mapManager);
			monster.push_back(monster5);
			monster_pos.push_back(Vec2(-1230.8f, 3366.5f));
			scene->addChild(monster5);

			//ɭ�ֹ���
			monster1 = new Monster("Monster1", 100, 600, 20, 100, 5, 100, 2, -517.39, -1547.87, 100, bonus.monster_bonus1, player, 500, 0.5, scene);
			monster1->Init(mapManager);
			monster.push_back(monster1);
			monster_pos.push_back(Vec2(-517.39, -1547.87));
			scene->addChild(monster1);

			//ɳĮ����
			monster8 = new Monster("Monster8", 100, 600, 20, 100, 5, 100, 2, 2153.66, -1298.14, 100, bonus.monster_bonus8, player, 500, 0.5, scene);
			monster8->Init(mapManager);
			monster.push_back(monster8);
			monster_pos.push_back(Vec2(2153.66, -1298.14));
			scene->addChild(monster8);

			//ѩ�ع���
			monster2 = new Monster("Monster2", 100, 600, 20, 100, 5, 100, 2, 2209.15, 3217.27, 100, bonus.monster_bonus2, player, 500, 0.5, scene);
			monster2->Init(mapManager);
			monster.push_back(monster2);
			monster_pos.push_back(Vec2(2209.15, 3217.27));
			scene->addChild(monster2);
		}
		if (DoorID == 9) {
			monster6 = new Monster("Monster6", 3000, 600, 20, 100, 5, 100, 2, 100, 100, 100, bonus.monster_bonus6, player, 500, 1.5f, scene);
			monster6->Init(mapManager);
			monster_pos.push_back(Vec2(VisibleSize.width / 2 + 160, VisibleSize.height / 2));
			monster.push_back(monster6);
			scene->addChild(monster6);
		}
		else if (DoorID == 21) {
			monster4 = new Monster("Monster4", 1000, 600, 20, 100, 5, 100, 2, 100, 100, 100, bonus.monster_bonus4, player, 500, 1.0f, scene);
			monster4->Init(mapManager);
			monster_pos.push_back(Vec2(VisibleSize.width / 2 + 160, VisibleSize.height / 2));
			monster.push_back(monster4);
			scene->addChild(monster4);
		}
		else if (DoorID == 31) {
			monster3 = new Monster("Monster3", 1000, 600, 20, 100, 5, 100, 2, VisibleSize.width / 2 + 160, VisibleSize.height / 2, 100, bonus.monster_bonus3, player, 500, 1.0f, scene);
			monster3->Init(mapManager);
			monster_pos.push_back(Vec2(VisibleSize.width / 2 + 160, VisibleSize.height / 2));
			monster.push_back(monster3);
			scene->addChild(monster3);
		}
		else if (DoorID == 41) {
			monster7 = new Monster("Monster7", 1000, 600, 20, 100, 5, 100, 2, VisibleSize.width / 2 + 160, VisibleSize.height / 2, 100, bonus.monster_bonus7, player, 500, 1.0f, scene);
			monster7->Init(mapManager);
			monster_pos.push_back(Vec2(VisibleSize.width / 2 + 160, VisibleSize.height / 2));
			monster.push_back(monster7);
			scene->addChild(monster7);
		}

		this->scheduleUpdate();
	}
	void update(float dt)override;
	vector<Monster*>GetMonster() {
		return monster;
	}
};

#endif __MONSTER_H__