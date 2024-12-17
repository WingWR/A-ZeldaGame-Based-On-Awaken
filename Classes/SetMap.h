#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"
#include "NPC.h"
#include "Monster.h"
USING_NS_CC;

class SetMap :public cocos2d::Scene {
private:
	Size visibleSize;

	MicroMap* MicroMap;     // ΢��ͼ����
	bool IsMicroMapVisible;     // ΢��ͼ�Ƿ�ɼ�

	int PlayerInWhichMap;  // ��ǰ������ڵĵ�ͼ���

	std::vector<cocos2d::Rect>ObstacleList;  // �ϰ����б�

	Camera* camera;    // ����ͼ�����
	Camera* camera_in_micro_map;    // С��ͼ�����

	EventListenerMouse* mainMapListener = nullptr;     // ����ͼ������
	EventListenerMouse* microMapListener = nullptr;     // С��ͼ������

	const float ScrollSpeed = 40.0f;    // ���ֹ����ٶ�

	vector<TMXLayer*> BlackFogList;    //��������ͼ��
	vector<bool> IsBlackFogVisible;    //�����Ƿ�ɼ�
	vector<bool> IsRegionRevealed;    //�Ƿ��Ѿ���ʾ��ĳ������


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

	/*��ʼ���ϰ���*/
	void InitialObstacle(cocos2d::TMXTiledMap* tileMap);

	/*�ж�ĳ��λ���Ƿ�����ƶ�*/
	bool IsMoveable(cocos2d::Vec2& pos);

	/*��������ƶ�*/
	void HandlePlayerMove(const Vec2& moveBy, int keyIndex, const std::string& scheduleKey, dir direction);

	/*���ص�ͼ*/
	void LoadMap();

	/*��ʼ�������*/
	void InitalCamera();

	/*���ú�ɫ������С��ͼ������ɼ�*/
	void SetBlackFogInMicroMap();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__