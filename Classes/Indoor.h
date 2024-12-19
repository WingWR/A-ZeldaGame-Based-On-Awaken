#ifndef __IN_DOOR_H__
#define __IN_DOOR_H__

#include "MainGameScene.h"
#include "cocos2d.h"

class Indoor :public MainGameScene {
private:
	Size VisibleSize;    // �ɼ������С

	EventListenerKeyboard* _keyboardListener;    // ���̼�����
	EventListenerMouse* _mouseListener;    // ��������

	CameraManager* _cameraManager;    // �����������
	MapManager* _mapManager;    // ��ͼ������
	BagManager* _bagManager;    // ����������

	Player* PLAYER;     // �����û�
	MonsterRespawn* _monsterRespawn;    // ���������
	NPC* npc1;    // NPC1

	vector<bool> isKeyPressed = { false,false,false,false };    // �����Ƿ���:W/S/A/D
public:
	/****************************************************************/
	////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
	/*���캯��������һ�����������ɫ*/
	Indoor(Player* origin_player);

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

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

#endif // __IN_DOOR_H__
