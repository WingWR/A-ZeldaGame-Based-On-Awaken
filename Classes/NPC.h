#ifndef __NPC_H__
#define __NPC_H__
#include <vector>
#include <functional>
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

	/* ���� */
	void Chat();

	/* npc0:��ѧ�� */
	void npc0(std::function<void()> callback);

	/* npc1 */
	void npc1(std::function<void()> callback);

	
};

/* npc������ */
class NPCManager {
private:
    std::vector<NPC*> npcList;  // �洢����npc
    Player* player;             // ��Ҷ��������

public:
    /* ���캯�� */
    NPCManager(Player* playerRef) : player(playerRef) {}

    /* ��� NPC */
    void addNPC(std::string role, int x, int y, float scale, Scene* scene) {
        NPC* newNpc = new NPC(role, x, y, scale, scene, player);
        npcList.push_back(newNpc);
    }

    /* �Ƴ�npc */
    void removeNPC(NPC* npc) {
        npcList.erase(std::remove(npcList.begin(), npcList.end(), npc), npcList.end());
        delete npc; 
    }

    /* ȫ��npc������� */
    void checkTriggers() {
        for (auto npc : npcList) {
            if (npc->isTrigger()) {
                npc->Chat();
            }
        }
    }

    /* ִ��ȫ�ָ����߼����綯������Ϊ�� */
    void updateNPCs(float delta) {
        for (auto npc : npcList) {
            // ���磬�������������ÿ��NPC��״̬
        }
    }

    /* �������� NPC */
    void clearAllNPCs() {
        for (auto npc : npcList) {
            delete npc;
        }
        npcList.clear();
    }
};


#endif __NPC_H__