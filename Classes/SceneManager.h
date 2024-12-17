#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class SceneManager:public Node {
public:
	void ChangeToNextScene(Scene* scene, float delay = 0.5f);    //�л�����һ���������ó���ջʵ�֣�������һ������
	void ChangeToPreviousScene(float delay = 0.5f);    //������һ������
};


#endif // __SCENE_MANAGER_H__