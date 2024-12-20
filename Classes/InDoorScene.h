#ifndef __WINTER_HOUSE_H__
#define __WINTER_HOUSE_H__

#include "MainGameScene.h"
#include "cocos2d.h"

class WinterHouse : public MainGameScene {
private:
	Size VisibleSize;    // �ɼ���Ļ��С

	EventListenerKeyboard* _keyboardListener;    // ���̼�����
	EventListenerMouse* _mouseListener;    // ��������

	CameraManager* _cameraManager;    // �����������
	MapManager* _mapManager;    // ��ͼ������
	BagManager* _bagManager;    // ����������

	Player* PLAYER;     // �����û�
	MonsterRespawn* _monsterRespawn;    // ���������
	NPCManager* _npcManager;   // NPC������
	music* _musicManager; // ���ֹ�����

	vector<bool> isKeyPressed = { false,false,false,false };    // �����Ƿ���:W/S/A/D
public:
	/****************************************************************/
	////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
	/*���캯��������һ�����������ɫ*/
	WinterHouse(Player* origin_player);

	/*���ɳ�������*/
	static cocos2d::Scene* createScene(Player* origin_player);

	/*��ʼ����ͼ����*/
	virtual bool init();

	/*���ص�ͼ����д����*/
	void LoadMapToScene() override;

	/*���������д����*/
	void LoadPlayerToScene() override;

	/*���ع������������д����*/
	void LoadMonsterRespawnToScene() override;

	/*����NPC����д����*/
	void LoadNPCToScene() override;
};

#endif // __WINTER_HOUSE_H__