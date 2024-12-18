#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Creature.h"
#include "Item.h"

USING_NS_CC;
using namespace std;

// ��������
const int DIST = 150;

struct Bonus {
	//Object object;
	//������ʱע�͵�
	//Equipment equipment;
	int exp = 0;
};
class Monster;
class Player :public Creature {
private:
	int current_exp;       // ��ɫ���о���ֵ
	int next_level_exp;    // �ﵽ��һ�����辭��ֵ
	vector<Monster*> monster;
protected:

public:
	/* ���캯�� */
	Player(std::string who, Scene* scene, int x, int y, float scale, int hp, int mp, int atk, int atk_range, int def, int speed, int level) :
		Creature(who, hp, mp, atk, atk_range, def, speed, level, x, y, scale, scene) {
		// ��ɫ���о���ֵ���ﵽ��һ�����辭��ֵ��ʼ�������ǵø�
		current_exp = 0;
		next_level_exp = 100;
		_weapon = nullptr;
		_armor = nullptr;
		_shoes = nullptr;
		_accessories = nullptr;
		coins = 1000;
		scene->addChild(this);
		this->scheduleUpdate();
		log("player init success");
	}
	// �����ù��캯��
	Player() {
		_weapon = nullptr;
		_armor = nullptr;
		_shoes = nullptr;
		_accessories = nullptr;
	
	}
	
	/* ������� */
	void InitMonster(vector<Monster*>monster);
	
	/* �ͷŹ������� */
	// dirΪ����:LEFT RIGHT UP DOWN,Ĭ��ΪDOWN
	// ���ڲ��ֹ���,�޷���һ˵:Monster1����
	// oppΪ��������
	virtual Animate* Attack(int dir, vector<Monster*>monster);

	/* �жϽ�����Χ */
	virtual bool isTrigger(const Vec2& pos);

	// ���ܣ�����ϼ���ʽ����
	//void Combo();

	/* ������� */
	// ��ɫ������
	weapon* _weapon;
	// ��ɫ�Ļ���
	armor* _armor;
	// ��ɫ��Ь��
	shoes* _shoes;
	// ��ɫ����Ʒ
	accessories* _accessories;
	//��ý���������Bonus�ṹ��,�ṹ�����躬�о���ֵ����Ʒ���ֽ�������
	void GetBonus(Bonus bonus);
	// update override
	void update(float dt)override;
	// ��ɫ�Ľ����
	int coins;
	// ��ֵ���������
	Player& operator=(const Player& other)
	{
		if (this == &other)  // �Ը�ֵ���
			return *this;
		level = other.level;
		hp = other.hp;
		current_hp = other.current_hp;
		current_mp = other.current_mp;
		atk = other.atk;
		def = other.def;
		speed = other.speed;
		_weapon = other._weapon;
		_armor = other._armor;
		_shoes = other._shoes;
		_accessories = other._accessories;
		coins = other.coins;
		this->setElementType(other.elementType);
		if (other.mySprite != nullptr)
		{
			x = other.getXY().x;
			y = other.getXY().y;
		}
		if (mySprite == nullptr)
		{
			mySprite = Sprite::create("Role/" + other.role + "/1.png");
			mySprite->setVisible(false);
		}

		return *this;
	}
	friend class BagManager;
};

#endif __PLAYER_H__