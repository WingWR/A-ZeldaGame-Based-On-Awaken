#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <vector>
#include "cocos2d.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"
#include "NPC.h"
#include "Monster.h"
#include "MapManager.h"
#include "CameraManager.h"
#include "EventManager.h"
USING_NS_CC;

class SetMap :public cocos2d::Scene {
private:
	Size VisibleSize;    // �ɼ���Ļ��С
	
	CameraManager* _cameraManager;    // �����������
	EventManager* _eventManager;    // �¼�������
	MapManager* _mapManager;    // ��ͼ������
	BagManager* _bagManager;    // ����������

	Player* PLAYER;     // �����û�
	MonsterRespawn* _monsterRespawn;    // ���������
	NPC* npc1;    // NPC1

	vector<bool> isKeyPressed = { false,false,false,false };    // �����Ƿ���:W/S/A/D
public:
	/****************************************************************/
	////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
	/* ���캯������ȡ��Ļ�Ĵ�С*/
	SetMap(); 

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	/*��ʼ�������*/
	void LoadCameraToScene();

	/*��ʼ����ͼ*/
	void LoadMapToScene();

	/*��ʼ����������*/
	void LoadBagToScene();

	/*��ʼ���ٿؽ�ɫ*/
	void LoadPlayerToScene();

	/*��ʼ�����������*/
	void LoadMonsterRespawnToScene();

	/*��ʼ��NPC*/
	void LoadNPCToScene();

	/****************************************************************/
	////////////////����Ϊ�����������ı��������й��ܺ���/////////////////
	/*�����������������ƶ�*/
	void CameraFollowController();

	/*��������ͼ�����������ƶ�*/
	void MainCameraFollowPlayer();

	/*����С��ͼ�����������ƶ�*/
	void MicroCameraFollowPlayer();

	/*������ͼ���͵�*/
	void UnlockMapTeleport(int MapID);

	/*����Ҵ��͵�ѡ��Ĵ��͵�*/
	void TeleportPlayer(int MapID);

	/**********************************************************************/
	////////////////����Ϊ�������������������صĻص�����/////////////////
	/*�����¼�����, ����M���л���ʾ΢��ͼ*/
	void KeyPressedForRevealMicroMap(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������B���򿪱���*/
	void KeyPressedForBag(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������W/A/S/D���������ƶ�*/
	void KeyPressedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event);
	void KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event);    //����ƶ��ĸ����������ͷŰ������ֹͣ�ƶ�
	void HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction);    //����ƶ��ĸ�������

	/*�����¼���������I/J/K/L�������﹥��*/
	void KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C����NPC��������*/
	void KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event);

	/*����¼������������ֿ��Ƶ�ͼ����*/
	void MouseScrollForCameraZoom(EventMouse* event, Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed);

	/*�����¼��������·��������С��ͼ����*/
	void KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed);

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__