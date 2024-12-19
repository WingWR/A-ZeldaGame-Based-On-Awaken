#ifndef __LEARNING_SCENE_H__
#define __LEARNING_SCENE_H__

#include <iostream>
#include <cocos2d.h>
#include "Player.h"
#include "SetPlayerScene.h"
#include "NPC.h"
#include "BagManager.h"
#include "MainGameScene.h"

class LearningScene :public cocos2d::Scene {
private:
	Player* LEARNER;
	NPC* CHATNPC;
public:
	/* ��ʼ������ */
	static cocos2d::Scene* createScene();
	virtual bool init();

	/* ��ӭ */
	virtual void welcome();

	/* ѧ��· */
	virtual void learnMove_1();
	virtual void learnMove_2();
	// ���̼���
	void MoveKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	// �����Ƿ���:W/S/A/D
	std::vector<bool> isKeyPressed = { false,false,false,false };

	/* ѧ���� */
	virtual void learnAttack_1();
	virtual void learnAttack_2();
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/* ѧ���� */
	virtual void learnChat_1();
	virtual void learnChat_2();
	void ChatKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/* ѧ���� */
	virtual void learnBag_1();
	virtual void learnBag_2();
	void BagKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	/* ��ɽ̳���ʾ */
	virtual void finish();

	CREATE_FUNC(LearningScene);
};



#endif // __LEARNING_SCENE_H__