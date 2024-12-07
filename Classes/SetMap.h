#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"


class SetMap :public cocos2d::Scene {
private:


	MicroMap* MicroMap;     // ΢��ͼ����
	bool IsMicroMapVisible;     // ΢��ͼ�Ƿ�ɼ�

	int PlayerInWhichMap;  // ��ǰ������ڵĵ�ͼ���
public:
	Player* PLAYER;

	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
			PLAYER->Attack(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
			PLAYER->Attack(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
			PLAYER->Attack(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
			PLAYER->Attack(RIGHT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
			PLAYER->Move(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
			PLAYER->Move(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
			PLAYER->Move(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
			PLAYER->Move(RIGHT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_T)
			PLAYER->Hurt();
	}

	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	// �����¼�����,����M���л���ʾ΢��ͼ
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);


	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__