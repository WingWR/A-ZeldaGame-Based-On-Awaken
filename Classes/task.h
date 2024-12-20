#pragma once
#ifndef __TASK_H__
#define __TASK_H__

#include "cocos2d.h"
#include <string>
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
using namespace std;
class task
{
public:
	string taskName; // ���������
	string description; // �����������
	bool isMainlineTask; // �Ƿ���������1��ʾ��������0��ʾ֧������
	bool isFinished; // �����Ƿ���ɣ�1��ʾ����ɣ�0��ʾδ���

	// ���캯��
	task(string name, string desc, bool isMainline, bool isFinished)
		: taskName(name), description(desc), isMainlineTask(isMainline), isFinished(isFinished) {
		// ʹ�ó�ʼ���б�ֵ������Ա����
	}
};
#endif