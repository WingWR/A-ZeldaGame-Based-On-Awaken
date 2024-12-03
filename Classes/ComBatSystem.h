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
class Creature {
private:
	string name;//����name
	int hp;//��������
	int mp;//����ħ��
	int atk;//��������ֵ
	int atk_range;//������Χ
	int def;//��������ֵ
	int speed;//�ٶ�
	int level;//�ȼ�
	Scene* scene;//���ڳ�����
	int x;//����
	int y;
	Sprite* mySprite;//����

public:
	Creature(string name,int hp, int mp, int atk, int def, int speed, int level,int x,int y) :
		name(name),hp(hp), mp(mp), atk(atk), def(def), speed(speed), level(level) {//ȱ�ٶ�scene�ĳ�ʼ��
		Level_Bonus();
	}
	// �յĹ��캯����������
	Creature() {
		hp = 1;
		mp = 1;
		atk = 1;
		def = 1;
		speed = 10;
		level = 1;
	}
	// ����,��s��ֵʱ��ò�Ҫʹ��Player��Monster����Monster��ͼƬҲװ��role/player�ļ�����
	//s = "Role/     ->Player<-     /" + name + "/attack" + std::to_string(idx) + "/" + name + "_atk" + std::to_string(idx) + "_";
	//���¼���������ͬ
	virtual void Attack(Creature target,int idx);
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
	Player(string name, int hp, int mp, int atk, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk, def, speed, level, x, y) {
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
	Bonus bonus;
	int base_exp;//����Ļ�������ֵ
public:
	Monster(string name, int hp, int mp, int atk, int def, int speed, int level, int x, int y) :
		Creature(name, hp, mp, atk, def, speed, level, x, y) {
		Level_Bonus();
		;//�ݴ�
	}
	//����
	void Bonus();
	//����ս��
	void StartFight();
	//Ѱ·���ǻ�����ֹ

};

#endif// __Combat_System_H__
