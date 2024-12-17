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
USING_NS_CC;

class SetMap :public cocos2d::Scene {
private:
	Size visibleSize;

	bool IsMicroMapVisible;     // ΢��ͼ�Ƿ�ɼ�

	CameraManager* _cameraManager;    // �����������

	EventListenerMouse* mainMapListener = nullptr;     // ����ͼ������
	EventListenerMouse* microMapListener = nullptr;     // С��ͼ������

	MapManager* _mapManager;    // ��ͼ������

	const float ScrollSpeed = 40.0f;    // ���ֹ����ٶ�
public:
	/* ���� */
	// ���
	Player* PLAYER;
	// ����
	MonsterRespawn* monster_respawn;
	// NPC
	NPC* npc1;

	/* �󶨼��� */
	std::vector<bool> isKeyPressed = { false,false,false,false }; // �����Ƿ���:W/S/A/D
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	/*�����¼�����, ����M���л���ʾ΢��ͼ*/
	void KeyPressedForMicroMap(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/*�����¼�����������Ӧ�����ƶ���ͼ*/
	void createKeyboardListenerForCamera(Camera* camera, float moveSpeed, float MaxWidth, float MinWidth, float MaxHeigth, float MinHeigth);

	/*����¼������������ֿ��Ƶ�ͼ����*/
	EventListenerMouse* createMouseListenerForCameraScroll(Camera* camera, float MaxHeight, float MinHeight, float ScrollSpeed);

	/*�����������������ƶ�*/
	void CameraFollowController();

	/*��������ͼ�����������ƶ�*/
	void MainCameraFollowPlayer();

	/*����С��ͼ�����������ƶ�*/
	void MicroCameraFollowPlayer();

	/*�����������λ��*/
	void UpdateCameraPosition(Camera* camera, Vec2& TargetPos, float Height);

	/*��������ƶ�*/
	void HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction);

	/*��ʼ�������*/
	virtual void InitialCamera();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__