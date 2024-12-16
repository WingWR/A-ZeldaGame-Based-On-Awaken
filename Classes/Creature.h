#ifndef __CREATURE_H__
#define __CREATURE_H__
#include "cocos2d.h"
#include "ElementType.h"
USING_NS_CC;

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
	std::string role;   // ��ɫ��:���ڼ���ͼƬ�ز�

	bool isDead;      // ����״̬
	int hp;           // ������
	int current_hp;   // ������
	int mp;           // ��ħ��
	int current_mp;   // ��ħ��
	int atk;          // ��������ֵ
	int atk_range;    // ������Χ
	int def;          // ��������ֵ
	int speed;        // �ٶ�
	int level;        // �ȼ�
	int x, y;         // λ��
	ElementType elementType; // ����
	float scale;      // ���ű���
	Scene* scene;     // ����ָ��
public:
	Sprite* mySprite; // ����
	int face_to;      // �泯����

	/* ���캯�� */
	// who:���ΪPlayer1~Player5,NPCΪnpc1~npc5
	// ����:speedĬ����Ϊ50,atk_rangeĬ����100
	Creature(std::string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y, float scale, Scene* scene) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level), scale(scale),
		face_to(DOWN), isDead(false), scene(scene), mySprite(nullptr), current_hp(hp), current_mp(mp), x(x), y(y) {

		// �����ʼ��
		mySprite = Sprite::create("Role/" + role + "/1.png");
		mySprite->setPosition(Vec2(x, y));
		mySprite->setScale(scale);
		scene->addChild(mySprite);

		// ��ʼԪ��Ϊ��
		this->setElementType(NONE);

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
		current_hp = 1;
		mp = 1;
		current_mp = 1;
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
	virtual void Move(int dir);

	/* ת�䳡�� */
	//��Ҫ�޸ģ����ͼ�Խӣ���Ҫ��ͼ�෵��GetScene��ֵ��һ������ΪScene*��scene)
	virtual void ChangeScene(Scene* sc) { scene = sc; }

	/* �ȼ��ӳ� */
	virtual void levelBonus();

	/* �����˺� */
	int DamageCal(Creature*, Creature*);

	/* ���ر���ֵ */
	// �����ٶ�speed
	int getSpeed()const { return speed; }
	// ������hp
	int getHp()const { return hp; }
	// ������hp
	int getCurrentHp()const { return current_hp; }
	// ������mp
	int getMp()const { return mp; }
	// ������mp
	int getCurrentMp()const { return current_mp; }
	// ����atk
	int getAtk()const { return atk; }
	// ����def
	int getDef()const { return def; }
	// ���ع�����Χatk_range
	int getAtkRange()const { return atk_range; }
	// ��������
	void setElementType(ElementType _elementType);

	// ��������
	Vec2 getXY()const { return Vec2(mySprite->getPosition().x, mySprite->getPosition().y); }
};
#endif __CREATURE_H__
