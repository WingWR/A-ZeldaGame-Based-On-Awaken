#ifndef __SET_MAP_H__
#define __SET_MAP_H__

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

public:
	////////////////////////////////////////////////////////////////
	/* �����Ƿ���:W/S/A/D*/
	std::vector<bool> isKeyPressed = { false,false,false,false };
	// ���
	Player* PLAYER;
	// ����Monster1
	Monster* Monster1;
	Monster* Monster2;
	// NPC
	NPC* npc1;

	/* �󶨼���:Released */
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	/* �󶨼���:Pressed */
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	//////////////////////////////////////////////////////////////

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	// �����¼�����,����M���л���ʾ΢��ͼ
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/*�����������������ƶ�*/
	void CameraFollowController();

	/*��������ͼ�����������ƶ�*/
	void MainCameraFollowPlayer();

	/*����С��ͼ�����������ƶ�*/
	void MicroCameraFollowPlayer();

	/*��ʼ���ϰ���*/
	void InitialObstacle(cocos2d::TMXTiledMap* tileMap);

	/*�ж�ĳ��λ���Ƿ�����ƶ�*/
	bool IsMoveable(cocos2d::Vec2& pos);

	/*���ص�ͼ*/
	void LoadMap();

	/*��ʼ�������*/
	void InitalCamera();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__