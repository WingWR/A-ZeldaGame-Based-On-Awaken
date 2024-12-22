#include "NPC.h"

USING_NS_CC;

/* ���캯�� */
NPCManager::NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx) : player(playerRef), bag(bagManager), NPCscene(scene) {
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    switch (idx) {
    /* ��ʼ��ͼ */
    case(0) :
        // ��������
        addNPC("npc1", 1298.5f, 1354.7, 0.8f);    // ������������
        addNPC("npc6", 577.0f, 455.8f, 0.6f);     // ��ʳ��
        npcList[1]->NPCunlockTask(0);             // ����֧������
        // ��ɽ
        addNPC("npc2", -1230.8f, 3366.5f, 0.6f);  // ������������
        // ѩ��
        addNPC("npc3", 2880.0f, 2726.9f, 0.6f);   // ������������
        // ɭ��
        addNPC("npc4", -1013.5, -395.0f, 0.6f);   // ������������
        break;
    /* ɳĮ����1 */
    case(31) :
        addNPC("npc5", 1357.0f, 871.0f, 0.6f);    // ������������
        break;
    /* ɳĮ����2 */
    case(32):
        addNPC("npc7", 1357.0f, 871.0f, 0.6f);    // ������
        npcList[6]->NPCunlockTask(0);             // ����֧������
        break;
    /* ɭ������1 */
    case(41):
        addNPC("npc8", 1357.0f, 871.0f, 0.6f);   
        break; 
    /* ɭ������2 */
    case(42):
        addNPC("npc9", 1357.0f, 871.0f, 0.6f);
        break;
    /* ѩ������ */
    case(21):
        addNPC("npc10", 1357.0f, 871.0f, 0.6f);
        break;
    default:
        break;
    }
    
    // ���npc�Ƿ�����Ч������Χ��
    NPCscene->schedule([=](float dt) {
        for (auto npc : npcList) {
            npc->update();
        }
        }, 0.1f, "npc_check_scheduler");
}

/* �������� */
NPCManager::~NPCManager() {
    clearAllNPCs();
}

/* ���NPC */
void NPCManager::addNPC(std::string role, int x, int y, float scale) {
    NPC* newNpc = new NPC(role, x, y, scale, NPCscene, player, bag);
    npcList.push_back(newNpc);
}

/* ȫ��npc������� */
void NPCManager::checkTriggers() {
    for (auto npc : npcList) {
        if (npc->isTrigger()) {
            npc->Chat();
        }
    }
}

/* ���Ի�״̬ */
bool NPCManager::getChattingStates() {
    for (auto npc : npcList) {
        if (npc->getChattingState())
            return true;
    }
    return false;
}

/* ��������NPC */
void NPCManager::clearAllNPCs() {
    for (auto npc : npcList) {
        delete npc;
    }
    npcList.clear();
}