#include "NPC.h"

USING_NS_CC;

/* ���캯�� */
NPCManager::NPCManager(Player* playerRef, BagManager* bagManager, Scene* scene, int idx) : player(playerRef), bag(bagManager), NPCscene(scene) {
    // ��ʼ���ص���޸�
    auto VisibleSize = Director::getInstance()->getVisibleSize();
    switch (idx) {
    // ��ʼ��ͼ
    case(0) :
        addNPC("npc1", VisibleSize.width / 2, VisibleSize.height / 2, 0.8f);
        addNPC("npc2", VisibleSize.width / 2 + 500, VisibleSize.height / 2, 0.6f);
        addNPC("npc3", VisibleSize.width / 2 + 500, VisibleSize.height / 2 + 500, 0.6f);
        addNPC("npc4", VisibleSize.width / 2 - 500, VisibleSize.height / 2, 0.6f);
        addNPC("npc5", VisibleSize.width / 2 - 500, VisibleSize.height / 2 - 500, 0.6f);
        break;
    // ���ڵ�ͼ1
    case(1) :
        addNPC("npc6", VisibleSize.width / 2 - 500, VisibleSize.height / 2 + 500, 0.6f);
        addNPC("npc7", VisibleSize.width / 2 + 500, VisibleSize.height / 2 - 500, 0.6f);
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