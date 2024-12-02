#pragma once

#include <iostream>
#include <string>
#include "cocos2d.h"

USING_NS_CC;

class Player {
public:
	/* ��ʾ��� */
	// who:��ɫ����
	//	   Arthur/Longbow
	// scene:����ָ��,Ҫ����ɫ��ӡ���ĸ�������
	// scale:���ű���
	// (x,y)��ӡ����
	void showPlayer(std::string who, Scene* scene, float scale, int x, int y);
	/* ����ͷŹ������� */
	// who:��ɫ����
	// scene:����ָ��,Ҫ����ɫ��ӡ���ĸ�������
	// idx:��������(1/2/3),1/2����ͨ����3�Ǵ���
	// scale:���ű���
	// (x,y)��ӡ����
	void PlayerAttack(std::string who, Scene* scene, int idx, float scale, int x, int y);
	/* ��·���� */
	void PlayerMove(std::string who, Scene* scene, float scale, int x, int y, int direction);
};