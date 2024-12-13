#ifndef __NPC_H__
#define __NPC_H__
#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

/* �������� */
const int DIST = 100;

class NPC :public Creature {
private:
	Player* who;   // ���
public:
	/* ���캯�� */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player) :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) { 
		who = player;
	}

	/* �ж��Ƿ��ڴ�����Χ�� */
	bool isTrigger();

	void Chat();
};


#endif __NPC_H__