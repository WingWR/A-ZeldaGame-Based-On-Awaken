#ifndef __Combat_System_H__
#define __Combat_System_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
struct Equipment {//���ɱ������
	int a;
};
struct Bonus {
	int exp;
	int object;
	Equipment equipment;
};

enum class State {
	IDLE, //���У���ֹ������Npc
	WALKING, //���ߣ����������Npc�͹���
	COMBATING // ս�������ڹ���
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
	
	State state;//ս��״̬
	Sprite* mySprite;//����
	Scene* scene;//���ڳ�����
public:
	Creature(string role,int hp, int mp, int atk,int atk_range, int def, int speed, int level,int x,int y,State state) :
		role(role),hp(hp), mp(mp), atk(atk),atk_range(atk_range), def(def), speed(speed), level(level),
		scene(nullptr),mySprite(nullptr),state(state) {
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
	void Die();
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
	Player(string name, int hp, int mp, int atk,int atk_range, int def, int speed, int level, int x, int y,State state) :
		Creature(name, hp, mp, atk,atk_range, def, speed, level, x, y,state),current_exp(0),next_level_exp(100) {
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
	 void GetBonus() {
		 ;
	 }
	 //ս��״̬
	 void IsInCombat();
};
//������
class Monster :public Creature {
private:
	int follow_range;
	Bonus bonus;//��ɱ����
	int base_exp;//����Ļ�������ֵ
	Node* target;
public:
	Monster(string name, int hp, int mp, int atk,int atk_range, int def, int speed, int level, int x, int y,State state,int exp,Bonus bonus,Player* player) :
		Creature(name, hp, mp, atk,atk_range, def, speed, level, x, y,state),base_exp(exp),bonus(bonus){
		Level_Bonus();
		;//�ݴ�
		target = player;
		this->scheduleUpdate();
	}
	void update(float dt)override;
	//����
	void Bonus();
	//����ս��
	void StartFight();
	//Ѱ·���ǻ�����ֹ

};

#endif// __Combat_System_H__
