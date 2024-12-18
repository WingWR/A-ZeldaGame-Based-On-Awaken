#include "CameraManager.h"

CameraManager::CameraManager() {
	//����������Ļ��С
	VisibleSize = Director::getInstance()->getVisibleSize();
}

void CameraManager::InitialMainCamera(Scene* TargetScene) {
	//����ͼ�������ʼ��ΪĬ�������
	MainCamera = TargetScene->getDefaultCamera();
}

void CameraManager::InitialMicroCamera(Scene* TargetScene) {
	//С��ͼ�������ʼ��Ϊ͸������������������ƶ�
	MicroCamera = Camera::createPerspective(60.0f, VisibleSize.width / VisibleSize.height, 100.0f, 4000.0f);    //�������Ϊ���������С�߶Ⱥ����߶�

	//С��ͼ�����Ĭ������Ϊ���ɼ�
	MicroCamera->setVisible(false);

	//��С��ͼ�������ӵ�������
	TargetScene->addChild(MicroCamera);
}

void CameraManager::SwitchToMainCamera() {
	//С��ͼ���������Ϊ���ɼ�
	MicroCamera->setVisible(false);

	//����ͼ���������Ϊ�ɼ�
	MainCamera->setVisible(true);
}

void CameraManager::SwitchToMicroCamera() {
	//����ͼ���������Ϊ���ɼ�
	MainCamera->setVisible(false);

	//С��ͼ���������Ϊ�ɼ�
	MicroCamera->setVisible(true);	
}

void CameraManager::UpdateCameraPosition(Camera* Camera, Vec2& Position, float Height) {
	//�����������λ��
	Camera->setPosition3D(Vec3(Position.x, Position.y, Height));
}

bool CameraManager::IsInMicroMap() {
	//�жϵ�ǰ�Ƿ���С��ͼ�������
	return MicroCamera->isVisible();
}