#include "SceneManager.h"

void SceneManager::ChangeToNextScene(Scene* scene, float delay) {
	if (scene == nullptr) {
		return;
	}

	//�½�һ�����ɳ���������ǰ����������������һ������
	auto transitionScene = TransitionFade::create(delay, scene, Color3B::BLACK);

	//�����ɳ�������Director�ĳ���ջ
	Director::getInstance()->pushScene(transitionScene);
}

void SceneManager::ChangeToPreviousScene(float delay) {
	//����Director�ĳ���ջ
	Director::getInstance()->popScene();
}