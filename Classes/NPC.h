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
    task* npc_task;
public:
	/* ���캯�� */
	NPC(std::string role, int x, int y, float scale, Scene* scene, Player* player, BagManager* bagManager) 
        :Creature(role, 0, 0, 0, 0, 0, 0, 0, x, y, scale, scene) {
		who = player;
        bag = bagManager;
        setTasks();
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

    /* npc��Ӧ���� */
    void setTasks();

    /* �������� */
    // idx:1����/0֧��
    void NPCunlockTask(bool idx);

    /* ������� */
    void NPCfinishTask();

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
    void npc7(std::function<void()> callback);
    void npc8(std::function<void()> callback);
    void npc9(std::function<void()> callback);
    void npc10(std::function<void()> callback);
};
/********************** END/NPC�� **********************/


/********************** NPC������ **********************/
class NPCManager {
private:
    std::vector<NPC*> npcList;  // �洢����npc
    Player* player;             // ��Ҷ��������
    BagManager* bag;            // ��ұ���
    Scene* NPCscene;
public:
    /* ���캯�� */
    //idx:����
    NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx);

    /* �������� */
    ~NPCManager();

    /* ����npc */
    vector<NPC*> visitNPC() { return npcList; }

    /* ���npc */
    void addNPC(std::string role, int x, int y, float scale);

    /* ȫ��npc������� */
    void checkTriggers();

    /* ���Ի�״̬ */
    bool getChattingStates();
   
    /* ��������NPC */
    void clearAllNPCs();

};
/******************** END/NPC������ ********************/

#endif __NPC_H__