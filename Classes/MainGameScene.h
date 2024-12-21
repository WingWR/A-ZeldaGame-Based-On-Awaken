#ifndef __MAIN_GAME_SCENE_H__
#define __MAIN_GAME_SCENE_H__

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
protected:
	int _NPC_choice;     // NPCѡ���־,���ز�ͬ��NPC
	int _Monster_choice; // ����ѡ���־,���ز�ͬ�Ĺ���
	int DoorID;          //�������⻹�����ڵ�ͼ��־�� 0Ϊ���⣬1Ϊ���ڣ�2Ϊս����Ĭ��Ϊ0
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
	MainGameScene(int _ODorID = 0, int _NPC_choice = 0, int _Monster_choice = 0);

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();
	Scene* MainGameScene::createScene(int _ODorID, int NPC_choice, int Monster_choice);

	/*��ʼ����ͼ����*/
	virtual bool init();

	/*��ʼ�������*/
	void LoadCameraToScene();

	/*��ʼ����ͼ*/
	void LoadMapToScene();

	/*��ʼ�������ͼ*/
	virtual void LoadOutDoorMapToScene();

	/*��ʼ�����ڵ�ͼ*/
	virtual void LoadInDoorMapToScene();

	/*��ʼ��ս����ͼ*/
	virtual void LoadFightMapToScene();

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

	/*�л������ⳡ��*/
	void ChangeScene(const int SceneName, const int NPCIndex, const int MonsterIndex);

	/**********************************************************************/
	////////////////����Ϊ�������������������صĻص�����/////////////////
	/*�����¼�����, ����M���л���ʾ΢��ͼ*/
	void KeyPressedForRevealMicroMap(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������B����/�رձ���*/
	void KeyPressedForBag(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������W/A/S/D���������ƶ�*/
	void KeyPressedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event);
	void KeyReleasedForPlayerMove(EventKeyboard::KeyCode keyCode, Event* event);    //����ƶ��ĸ����������ͷŰ������ֹͣ�ƶ�
	void HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction);    //����ƶ��ĸ�������

	/*�����¼���������J�������﹥��*/
	void KeyPressedForPlayerAttack(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C����NPC��������*/
	void KeyPressedForNPCInteract(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C���������͵�*/
	void KeyPressedForUnlockTeleport(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C���л������ⳡ��*/
	void KeyPressedForChangeScene(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼���������C���볡����������Ҫ�Ǵ�����*/
	void KeyPressedForInteraction(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼��������·��������С��ͼ����*/
	void KeyPressedForMicroMapMove(EventKeyboard::KeyCode keyCode, Event* event, Camera* camera, float MaxHeight, float MinHeight, float MaxWidth, float MinWidth, float ScrollSpeed);

	/*�����¼�������ESC����/�ر����ֿ��ƽ���*/
	void KeyPressedForBackgroundMusic(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼��������մ�����̰����¼�����*/
	virtual void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/*�����¼��������մ�������ͷ��¼�����*/
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	/*����¼������������ֿ��Ƶ�ͼ����*/
	void MouseScrollForCameraZoom(EventMouse* event, Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed);

	/*��괫���¼��������մ���������¼�����*/
	void MouseClickedForTeleport(EventMouse* event);

	/*����¼��������մ����������¼�����*/
	void MouseScroll(EventMouse* event);

	/*����¼��������մ���������¼�����*/
	void MouseClicked(EventMouse* event);

	/**********************************************************************/
	///////////////////����Ϊ��������������ת���ĸ�������///////////////////
	/*����Ļ����ת��Ϊ��������*/
	Vec2 ScreenToScene(const Vec2& screenPos);

	CREATE_FUNC(MainGameScene);
};

#endif // __MAIN_GAME_SCENE_H__