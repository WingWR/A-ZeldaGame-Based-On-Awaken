#ifndef __NPC_H__
#define __NPC_H__
#include <vector>
#include <functional>
#include "cocos2d.h"
#include "Player.h"
#include "BagManager.h"

USING_NS_CC;

/************************ NPC�� ************************/
class NPC :public Creature {
private:
	Player* who;      // ���
    BagManager* bag;  // ��ұ���
    bool isChatting = false;  // �Ƿ����ڶԻ�
    std::vector<bool> Mtasks = { false,false,false,false,false};  // ���������Ƿ��ѽ���
public:
	/* ���캯�� */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player, BagManager* bagManager) :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) {
		who = player;
        bag = bagManager;
	}

    /* ��ҿ���:npc��ʾ(��ͼ) */
    inline void triggerTip() { mySprite->setTexture("Role/" + role + "/2.png"); }
    inline void trggerTipRemove(){ mySprite->setTexture("Role/" + role + "/1.png"); }
    void update();

	/* �ж��Ƿ��ڴ�����Χ�� */
	bool isTrigger();

    /* ���ضԻ�״̬ */
    bool getChattingState() { return isChatting; }
	
    /* ���� */
	void Chat();

	/* npc */
    // ��ѧnpc
	void npc0(std::function<void()> callback); 
    // ������������npc
	void npc1(std::function<void()> callback);
    void npc2(std::function<void()> callback);
    void npc3(std::function<void()> callback);
    void npc4(std::function<void()> callback);
    void npc5(std::function<void()> callback);
	// ����npc
    void npc6(std::function<void()> callback);
};
/********************** END/NPC�� **********************/


/********************** NPC������ **********************/
class NPCManager {
private:
    std::vector<NPC*> npcList;  // �洢����npc
    Player* player;             // ��Ҷ��������
    BagManager* bag;            // ��ұ���
public:
    /* ���캯�� */
    NPCManager(Player* playerRef, BagManager* bagManager) : player(playerRef), bag(bagManager) {  }

    /* ����npc */
    NPC* visitNPC(const int& idx) { return npcList[idx]; }
    vector<NPC*> visitNPC() { return npcList; }

    /* ���npc */
    void addNPC(std::string role, int x, int y, float scale, Scene* scene) {
        NPC* newNpc = new NPC(role, x, y, scale, scene, player, bag);
        npcList.push_back(newNpc);
    }

    /* �Ƴ�npc */
    void removeNPC(NPC* npc) {
        npcList.erase(std::remove(npcList.begin(), npcList.end(), npc), npcList.end());
        npc->removeFromParent(); //?
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

    /* ���Ի�״̬ */
    bool getChattingStates() {
        for (auto npc : npcList) {
            if (npc->getChattingState())
                return true;
        }
        return false;
    }
    /* ��������NPC */
    void clearAllNPCs() {
        for (auto npc : npcList) {
            delete npc;
        }
        npcList.clear();
    }
};
/******************** END/NPC������ ********************/

#endif __NPC_H__