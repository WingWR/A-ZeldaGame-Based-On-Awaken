#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Creature.h"
#include "Item.h"

USING_NS_CC;
using namespace std;

struct Object {
	;
};

struct Bonus {
	//Object object;
	//������ʱע�͵�
	//Equipment equipment;
	int exp = 0;
};



class Player :public Creature {
private:
	int current_exp;       // ��ɫ���о���ֵ
	int next_level_exp;    // �ﵽ��һ�����辭��ֵ
protected:
	// ���������Creature�����Ѷ�����:(	

   //int x, y;       // ����
public:
	// ����//Creature������:( 

	/* ���캯�� */
	// who:���ΪPlayer1~Player5,NPCΪnpc1~npc5
	// ����:speedĬ����Ϊ50,atk_rangeĬ����100
	Player(std::string who, Scene* scene, int x, int y, float scale, int hp, int mp, int atk, int atk_range, int def, int speed, int level) :
		Creature(who, hp, mp, atk, atk_range, def, speed, level, x, y, scale, scene) {
		// ��ɫ���о���ֵ���ﵽ��һ�����辭��ֵ��ʼ�������ǵø�
		current_exp = 0;
		next_level_exp = 0;
		_weapon = nullptr;
		_armor = nullptr;
		_shoes = nullptr;
		_accessories = nullptr;
		coins = 1000;
	}
	// �����ù��캯��
	Player() {
		_weapon = nullptr;
		_armor = nullptr;
		_shoes = nullptr;
		_accessories = nullptr;
	}

	/* �ͷŹ������� */
	// dirΪ����:LEFT RIGHT UP DOWN,Ĭ��ΪDOWN
	// ���ڲ��ֹ���,�޷���һ˵:Monster1����
	// oppΪ��������
	//virtual void Attack(int dir = DOWN, Player* opp = nullptr);

	// ��ɫ������
	weapon* _weapon;

	// ��ɫ�Ļ���
	armor* _armor;

	// ��ɫ��Ь��
	shoes* _shoes;

	// ��ɫ����Ʒ
	accessories* _accessories;

	// ���ܣ�����ϼ���ʽ����
	//void Combo();

	//��ý���������Bonus�ṹ��,�ṹ�����躬�о���ֵ����Ʒ���ֽ�������
	void GetBonus(Bonus bonus);

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