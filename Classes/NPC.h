#ifndef __NPC_H__
#define __NPC_H__
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "Player.h"
#include "BagManager.h"

USING_NS_CC;

/* �������� */
const int DIST = 150;

class NPC :public Creature {
private:
	Player* who;   // ���
public:
	/* ���캯�� */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player) :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) { 
		who = player;
        this->scheduleUpdate();
	}

    /* ��ҿ���:npc��ʾ(��ͼ) */
    inline void triggerTip() { mySprite->setTexture("Role/" + role + "/2.png"); }
    inline void trggerTipRemove(){ mySprite->setTexture("Role/" + role + "/1.png"); }
    void update(float dt = 0.3f);

    
	/* �ж��Ƿ��ڴ�����Χ�� */
	bool isTrigger();

	/* ���� */
	void Chat();

	/* npc */
	void npc0(std::function<void()> callback);  // ��ѧ��
	void npc1(std::function<void()> callback);
    void npc2(std::function<void()> callback);

	
};




/* npc������ */
class NPCManager {
private:
    std::vector<NPC*> npcList;  // �洢����npc
    Player* player;             // ��Ҷ��������

public:
    /* ���캯�� */
    NPCManager(Player* playerRef) : player(playerRef) {  }

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