#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include "cocos2d.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"
#include "NPC.h"
#include "Monster.h"
#include "MapManager.h"
#include "CameraManager.h"
#include "BackgroundMusic.h"
USING_NS_CC;

class MainGameScene :public cocos2d::Scene {
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
	/* ���캯������ȡ��Ļ�Ĵ�С*/
	MainGameScene(); 

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	/*��ʼ�������*/
	void LoadCameraToScene();

	/*��ʼ����ͼ*/
	virtual void LoadMapToScene();

	/*��ʼ����������*/
	void LoadBagToScene();

	/*��ʼ���ٿؽ�ɫ*/
	virtual void LoadPlayerToScene();

	/*��ʼ�����������*/
	virtual void LoadMonsterRespawnToScene();

	/*��ʼ��NPC*/
	virtual void LoadNPCToScene();

	/*��ʼ���������ֹ�����*/
	virtual void LoadBackgroundMusicToScene();

	/****************************************************************/
	////////////////����Ϊ�����������ı��������й��ܺ���/////////////////
	/*�����������������ƶ�*/
	void CameraFollowController();

	/*��������ͼ�����������ƶ�*/
	void MainCameraFollowPlayer();

	/*����С��ͼ�����������ƶ�*/
	void MicroCameraFollowPlayer();

	/*������ͼ���͵�*/
	void UnlockMapTeleport();

	/*����Ҵ��͵�ѡ��Ĵ��͵�*/
	void TeleportPlayer(int MapID);

	/*�������ڳ���*/
	void ChangeToInDoorScene(const string SceneName);

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

	/*�����¼���������C���������͵�*/
	void KeyPressedForUnlockTeleport(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C���������ڳ���*/
	void KeyPressedForGetInDoor(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C���볡����������Ҫ�Ǵ�����*/
	void KeyPressedForInteraction(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼��������·��������С��ͼ����*/
	void KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed);

	/*�����¼��������մ�����̰����¼�����*/
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼��������մ�������ͷ��¼�����*/
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	/*����¼������������ֿ��Ƶ�ͼ����*/
	void MouseScrollForCameraZoom(EventMouse* event, Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed);

	/*����¼��������մ����������¼�����*/
	void MouseScroll(EventMouse* event);

	/*��괫���¼��������մ���������¼�����*/
	void MouseClickedForTeleport(EventMouse* event);

	/*����¼��������մ���������¼�����*/
	void MouseClicked(EventMouse* event);

	/**********************************************************************/
	///////////////////����Ϊ��������������ת���ĸ�������///////////////////
	/*����Ļ����ת��Ϊ��������*/
	Vec2 ScreenToScene(const Vec2& screenPos);

	CREATE_FUNC(MainGameScene);
};

#endif // __SET_MAP_H__