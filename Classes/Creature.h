#ifndef __CREATURE_H__
#define __CREATURE_H__
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
/* ���� */
enum dir {
	LEFT,    // 0
	RIGHT,   // 1
	UP,      // 2
	DOWN     // 3
};


/* ������� */
class Creature :public Node {
protected:
	string role;     // ��ɫ��:���ڼ���ͼƬ�ز�

	bool isDead;     // ����״̬
	int hp;          // ������
	int current_hp;  // ������
	int mp;          // ��ħ��
	int current_mp;  // ��ħ��
	int atk;         // ��������ֵ
	int atk_range;   // ������Χ
	int def;         // ��������ֵ
	int speed;       // �ٶ�
	int level;       // �ȼ�

	float scale;     // ���ű���
	Scene* scene;    // ����ָ��
public:
	Sprite* mySprite; // ����
	int face_to;      // �泯����

	/* ���캯�� */
	// who:���ΪPlayer1~Player5,NPCΪnpc1~npc5
	// ����:speedĬ����Ϊ50,atk_rangeĬ����100
	Creature(string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y, float scale, Scene* scene) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level), scale(scale),
		face_to(DOWN), isDead(false), scene(scene), mySprite(nullptr) {
		// �����ʼ��
		mySprite = Sprite::create("Role/" + role + "/1.png");
		mySprite->setPosition(Vec2(x, y));
		mySprite->setScale(scale);
		scene->addChild(mySprite);

		levelBonus();
	}

	// �յĹ��캯����������
	Creature() {
		scale = 1.0f;
		scene = nullptr;
		face_to = DOWN;
		mySprite = nullptr;
		isDead = false;
		hp = 1;
		mp = 1;
		atk = 1;
		atk_range = 20;
		def = 1;
		speed = 10;
		level = 1;
	}

	/* �ͷŹ������� */
	// dirΪ����:LEFT RIGHT UP DOWN,Ĭ��ΪDOWN
	// ���ڲ��ֹ���,�޷���һ˵:Monster1����
	// oppΪ��������
	virtual void Attack(int dir = DOWN, Creature* opp = nullptr);

	/* ���� */
	virtual void Hurt();

	/* ���� */
	// �������ƶ����������ܾ���������ֱ������
	virtual void Die();

	/* ���� */
	virtual void Revive();

	/* �ָ� */
	virtual void Heal();

	/* �ƶ� */
	// Monster1:����,�޷��ƶ�
	// Monster2:�粼��,���ķ����ƶ�
	virtual void Move(int dir);

	virtual void levelBonus() {
		speed = speed * (0.05 * level + 1);
		hp = level * hp;
		mp = mp * level;
		atk = atk * level;
		def = def * level;
	}


	/* ת�䳡�� */
	virtual void ChangeScene(Scene* sc) { //��Ҫ�޸ģ����ͼ�Խӣ���Ҫ��ͼ�෵��GetScene��ֵ��һ������ΪScene*��scene)
		scene = sc;
	}
	// �����˺�
	int DamageCal(Creature*, Creature*);
	/* ��ȡ�ٶ�speed */
	int getSpeed()const { return speed; }
	// �����hp
	int getHp()const;
	// �����hp
	int getCurrentHp()const;
	// �����mp
	int getMp()const;
	// �����mp
	int getCurrentMp()const;
	// ���atk
	int getAtk()const;
	// ���def
	int getDef()const;
	/* ��ȡ������Χatk_range */
	int getAtkRange()const { return atk_range; }
};
#endif __CREATURE_H__