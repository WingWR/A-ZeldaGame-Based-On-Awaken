/*
#ifndef __Combat_System_H__
#define __Combat_System_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

struct Equipment {//���ɱ������
	int a;
};
struct Object {
	;
};
struct Bonus {
	Object object;
	Equipment equipment;
	int exp=0;
};
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
class Creature:public Node {
protected:
	string role;//����name
	int hp;//��������
	int mp;//����ħ��
	int atk;//��������ֵ
	int atk_range;//������Χ
	int def;//��������ֵ
	int speed;//�ٶ�
	int level;//�ȼ�
	int x;//����
	int y;
	
	Sprite* mySprite;//����
	Scene* scene;//���ڳ�����
public:
	Creature(string role,int hp, int mp, int atk,int atk_range, int def, int speed, int level,int x,int y) :
		role(role),hp(hp), mp(mp), atk(atk),atk_range(atk_range), def(def), speed(speed), level(level),
		scene(nullptr),mySprite(nullptr) {
		Level_Bonus();
	}
	// �յĹ��캯����������
	Creature() {
		hp = 1;
		mp = 1;
		atk = 1;
		atk_range = 20;
		def = 1;
		speed = 10;
		level = 1;
	}
	// ����,��s��ֵʱ��ò�Ҫʹ��Player��Monster����Monster��ͼƬҲװ��role/player�ļ�����
	//s = "Role/     ->Player<-     /" + name + "/attack" + std::to_string(idx) + "/" + name + "_atk" + std::to_string(idx) + "_";
	//���¼���������ͬ
	virtual void Attack(Node* target,int idx);
	//����
	void Hurt(int atk);
	//����
	virtual void Die();
	//�ָ�
	virtual void Heal();
	// ��ֹ
	virtual void Show();
	//�ƶ�
	virtual void Move();
	//�ȼ��ӳ�
	virtual void Level_Bonus();
	// ת�䳡��
	virtual void ChangeScene(Scene* sc)  {//��Ҫ�޸ģ����ͼ�Խӣ���Ҫ��ͼ�෵��GetScene��ֵ��һ������ΪScene*��scene)
		scene = sc;
	}
};
//��ɫ��
class Player :public Creature {
private:
	int current_exp;//��ɫ���о���ֵ
	int next_level_exp;//�ﵽ��һ�����辭��ֵ
public:
	Player(string name, int hp, int mp, int atk,int atk_range, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk,atk_range, def, speed, level, x, y),current_exp(0),next_level_exp(100) {
		string s = "Role/Player/" + name + "/" + name;
		auto mySprite = Sprite::create(s + ".png");
		mySprite->setPosition(Vec2(x, y));
		Level_Bonus();
	}
	//װ�����ӳ���ֵ����������ͼ,��Ҫ�뱳���Խ�,������һ��Equipment�ṹ�壬�ṹ������Ҫ��atk��def���������ͷ���
	void Equipment() {
		;
	}
	// ���ܣ�����ϼ���ʽ����
	 void Combo();
	 //��ý���������Bonus�ṹ��,�ṹ�����躬�о���ֵ����Ʒ���ֽ�������
	 void GetBonus(Bonus bonus);
	 //ս��״̬
	 void IsInCombat();
};
//������
class Monster :public Creature {
private:
	int follow_range;
	Bonus bonus;//��ɱ����
	int base_exp;//����Ļ�������ֵ
	Player* target;
	MonsterAI ai = MonsterAI(target);
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
};
//����AI��
class MonsterAI {
private:
	MonsterState currentState;//����״̬
	Player* target;
	
public:
	MonsterAI(Player* target) : currentState(MonsterState::PATROLLING), target(target) {}//Ĭ��ΪѲ��
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

*/