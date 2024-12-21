#pragma once
#ifndef __TASK_H__
#define __TASK_H__
#include <string>

class task
{
public:
	std::string taskName; // ���������
	std::string description; // �����������
	bool isMainlineTask; // �Ƿ���������1��ʾ��������0��ʾ֧������
	bool isFinished; // �����Ƿ���ɣ�1��ʾ����ɣ�0��ʾδ���

	// ���캯��
	task(std::string name, std::string desc, bool isMainline, bool isFinished)
		: taskName(name), description(desc), isMainlineTask(isMainline), isFinished(isFinished) {
		// ʹ�ó�ʼ���б�ֵ������Ա����
	}
};
#endif