#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include"cocos2d.h"

class SetMap :public cocos2d::Scene {
public:
	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__