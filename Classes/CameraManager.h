#ifndef __CAMERA_MANAGER_H__
#define __CAMERA_MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class CameraManager :public Node {
private:
	Size VisibleSize;    //�ɼ������С

	Camera* MainCamera;    //����ͼ�����
	Camera* MicroCamera;    //С��ͼ�����
public:
	/*���캯��*/
	CameraManager();

	/*��ȡ����ͼ�����*/
	Camera* GetMainCamera() const { return MainCamera; }

   /*��ȡС��ͼ�����*/
	Camera* GetMicroCamera() const { return MicroCamera; }

	/*��ʼ������ͼ�����*/
	void InitialMainCamera(Scene* TargetScene);

	/*��ʼ��С��ͼ�����*/
	void InitialMicroCamera(Scene* TargetScene);

	/*�л�������ͼ�����*/
	void SwitchToMainCamera();

	/*�л���С��ͼ�����*/
	void SwitchToMicroCamera();

	/*���������λ��*/
	void UpdateCameraPosition(Camera* Camera, Vec2& Position, float Height);

	CREATE_FUNC(CameraManager);
};

#endif // __CAMERA_MANAGER_H__