
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
	goods goods;
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
		monster_bonus1.c = goods.pumkin;
		monster_bonus1.w = goods.icon_sword;
		monster_bonus1.a = goods.icon_conselet;
		monster_bonus1.s = goods.boots;
		monster_bonus1.ac = goods.forest_ring;
		monster_bonus1.exp = 100;
		monster_bonus1.coin = 100;

		monster_bonus2.c = goods.apple;
		monster_bonus2.w = goods.great_sword;
		monster_bonus2.a = goods.shield;
		monster_bonus2.s = goods.diamond_shoes;
		monster_bonus2.ac = goods.ice_nacklace;
		monster_bonus2.exp = 100;
		monster_bonus2.coin = 100;

		monster_bonus3.c = goods.chess;
		monster_bonus3.w = goods.long_sword;
		monster_bonus3.a = goods.helmet;
		monster_bonus3.s = goods.final_shoes;
		monster_bonus3.ac = goods.rack_cape;
		monster_bonus3.exp = 100;
		monster_bonus3.coin = 100;

		monster_bonus4.c = goods.chicken;
		monster_bonus4.w = goods.dagger;
		monster_bonus4.a = goods.final_armor;
		monster_bonus4.s = goods.boots;
		monster_bonus4.ac = goods.fire_ring;
		monster_bonus4.exp = 100;
		monster_bonus4.coin = 100;

		monster_bonus5.c = goods.beer;
		monster_bonus5.w = goods.final_sword;
		monster_bonus5.a = goods.icon_conselet;
		monster_bonus5.s = goods.diamond_shoes;
		monster_bonus5.ac = goods.ice_nacklace;
		monster_bonus5.exp = 100;
		monster_bonus5.coin = 100;

		monster_bonus6.c = goods.life_potion;
		monster_bonus6.w = goods.iron_sword;
		monster_bonus6.a = goods.shield;
		monster_bonus6.s = goods.final_shoes;
		monster_bonus6.ac = goods.forest_scepter;
		monster_bonus6.exp = 100;
		monster_bonus6.coin = 100;

		monster_bonus7.c = goods.pumkin;
		monster_bonus7.w = goods.great_sword;
		monster_bonus7.a = goods.helmet;
		monster_bonus7.s = goods.boots;
		monster_bonus7.ac = goods.rack_cape;
		monster_bonus7.exp = 100;
		monster_bonus7.coin = 100;

		monster_bonus8.c = goods.apple;
		monster_bonus8.w = goods.long_sword;
		monster_bonus8.a = goods.final_armor;
		monster_bonus8.s = goods.diamond_shoes;
		monster_bonus8.ac = goods.fire_ring;
		monster_bonus8.exp = 100;
		monster_bonus8.coin = 100;
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
		// name,hp,mp,atk,atk_range,def,speed,level,x,y,exp,bonus,player,follow_range,scale,scene) :
		MonsterBonus bonus;
		if (DoorID == 0) {
			monster1 = new Monster("Monster1", 100, 600, 20, 100, 5, 100, 2, 1000, 100, 100, bonus.monster_bonus1, player, 500, 0.5, scene);
			//��
			monster2 = new Monster("Monster2", 100, 600, 20, 100, 5, 100, 2, 3000, 2000, 100, bonus.monster_bonus2, player, 500, 0.5, scene);

			monster3 = new Monster("Monster3", 100, 600, 20, 100, 5, 100, 2, 500, 100, 100, bonus.monster_bonus3, player, 500, 0.5, scene);
			monster4 = new Monster("Monster4", 100, 600, 20, 100, 5, 100, 2, 600, 200, 100, bonus.monster_bonus4, player, 500, 0.5, scene);
			//��
			monster5 = new Monster("Monster5", 100, 600, 20, 100, 5, 100, 2, -1899, 2600, 100, bonus.monster_bonus5, player, 500, 0.5, scene);
			monster1->Init(mapManager);
			monster2->Init(mapManager);
			monster3->Init(mapManager);
			monster4->Init(mapManager);
			monster5->Init(mapManager);
			monster.push_back(monster1);
			monster.push_back(monster2);
			monster.push_back(monster3);
			monster.push_back(monster4);
			monster.push_back(monster5);
			monster_pos.push_back(Vec2(1000, 100));
			monster_pos.push_back(Vec2(3000, 2000));
			monster_pos.push_back(Vec2(500, -100));
			monster_pos.push_back(Vec2(600, -200));
			monster_pos.push_back(Vec2(-500, 100));
			scene->addChild(monster1);
			scene->addChild(monster2);
			scene->addChild(monster3);
			scene->addChild(monster4);
			scene->addChild(monster5);
		}
		else if (DoorID == 2) {
			monster6 = new Monster("Monster6", 100, 600, 20, 100, 5, 100, 2, 100, 100, 100, bonus.monster_bonus6, player, 500, 0.5, scene);
			monster7 = new Monster("Monster7", 100, 600, 20, 100, 5, 100, 2, 1500, 1200, 100, bonus.monster_bonus7, player, 500, 0.5, scene);
			monster8 = new Monster("Monster8", 100, 600, 20, 100, 5, 100, 2, 600, 400, 100, bonus.monster_bonus8, player, 500, 0.5, scene);
			monster6->Init(mapManager);
			monster7->Init(mapManager);
			monster8->Init(mapManager);
			monster.push_back(monster6);
			monster.push_back(monster7);
			monster.push_back(monster8);
			monster_pos.push_back(Vec2(-100, -100));
			monster_pos.push_back(Vec2(1500, 1200));
			monster_pos.push_back(Vec2(600, 400));

			scene->addChild(monster6);
			scene->addChild(monster7);
			scene->addChild(monster8);
		}

		this->scheduleUpdate();
	}
	void update(float dt)override;
	vector<Monster*>GetMonster() {
		return monster;
	}
};

#endif __MONSTER_H__

