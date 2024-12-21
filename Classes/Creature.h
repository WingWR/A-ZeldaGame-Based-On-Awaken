#ifndef __CREATURE_H__
#define __CREATURE_H__
#include "cocos2d.h"
#include <vector>
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
	/************************** protected **************************/
protected:
	std::string role; // ��ɫ��:���ڼ���ͼƬ�ز�

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
	bool is_moving;
	float scale;      // ���ű���
	Scene* scene;     // ����ָ��

	/************************** public **************************/
public:
	/* ������� */
	Sprite* mySprite; // ����
	int face_to;      // �泯����

	/* ��ײ��� */
	bool canMove = true;                   // �Ƿ���ƶ�
	Size collisionBoxSize = Size(0, 0);    // ��ײ���С
	Vec2 collisionBoxOffset = Vec2(0, 0);  // ��ײ��ƫ����
	Rect getCollisionRect() const;         // ��ȡ��ײ��
	bool isCollision(const Rect& rect1, const Rect& rect2);        // �ж���ײ
	void preventOverlap(Creature* creature1, Creature* creature2); // ��ֹ��ײ
	void Creature::drawCollisionBox();     // ����ײ��:������
	void editSizeOffset(Size size, Vec2 vec);

	/* ���캯�� */
	Creature(std::string role, int hp, int mp, int atk, int atk_range, int def, int speed, int level, int x, int y, float scale, Scene* scene) :
		role(role), hp(hp), mp(mp), atk(atk), atk_range(atk_range), def(def), speed(speed), level(level), scale(scale),
		face_to(DOWN), isDead(false), scene(scene), mySprite(nullptr), current_hp(hp), current_mp(mp), x(x), y(y) {
		// ��ʼ������
		initSprite();
		is_moving = false;
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

	/* ��ʼ������ */
	void initSprite();

	/* �ͷŹ������� */
	// oppΪ��������
	virtual void Attack();
	int getDir() { return face_to; }

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
	virtual void Move(int dir);
	virtual void learnMove(int dir);


	/* ת�䳡�� */
	//��Ҫ�޸ģ����ͼ�Խӣ���Ҫ��ͼ�෵��GetScene��ֵ��һ������ΪScene*��scene)
	virtual void ChangeScene(Scene* sc) { scene = sc; }

	/* �ȼ��ӳ� */
	virtual void levelBonus();

	/* �����˺� */
	int DamageCal(Creature*, Creature*);

	/* ���ر���ֵ */
	bool ChangeIsDead(bool change) { isDead = change; }
	bool getIsDead() { return isDead; }            // �����Ƿ�����
	int getSpeed()const { return speed; }          // �����ٶ�speed
	int getHp()const { return hp; }                // ������hp
	int getCurrentHp()const { return current_hp; } // ������hp
	int getMp()const { return mp; }                // ������mp
	int getCurrentMp()const { return current_mp; } // ������mp
	int getAtk()const { return atk; }              // ����atk
	int getDef()const { return def; }              // ����def
	int getAtkRange()const { return atk_range; }   // ���ع�����Χatk_range
	bool getIsDead()const { return isDead; }       // �����Ƿ�����
	/* �������� */
	void setElementType(ElementType _elementType);
	// �ı�XY
	void ChangeXY(Vec2 change);
	// ��������

	/* ������ز��� */

	Vec2 getXY()const { return Vec2(mySprite->getPosition().x, mySprite->getPosition().y); }
	//�ı�face_tp
	void ChangeFaceTo(int face_to) { this->face_to = face_to; }
	//��Ѫ
	void DecreaseHp(int damage) { current_hp -= damage; }
	void ReSetHp() { current_hp = hp; }
};

#endif __CREATURE_H__