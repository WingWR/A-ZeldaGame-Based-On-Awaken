#ifndef __LEARNING_SCENE_H__
#define __LEARNING_SCENE_H__

#include <iostream>
#include <cocos2d.h>
#include "Player.h"
#include "SetPlayerScene.h"

class LearningScene :public cocos2d::Scene {
private:
	Player* LEARNER;
public:
	/* ��ʼ������ */
	static cocos2d::Scene* createScene();
	virtual bool init();

	/* ��ӭ */
	virtual void welcome();

	/* ѧ��· */
	virtual void learnMove();


	CREATE_FUNC(LearningScene);
};



#endif // __LEARNING_SCENE_H__