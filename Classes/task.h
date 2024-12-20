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
	string taskName; // 任务的名称
	string description; // 对任务的描述
	bool isMainlineTask; // 是否主线任务，1表示主线任务，0表示支线任务
	bool isFinished; // 任务是否完成，1表示已完成，0表示未完成

	// 构造函数
	task(string name, string desc, bool isMainline, bool isFinished)
		: taskName(name), description(desc), isMainlineTask(isMainline), isFinished(isFinished) {
		// 使用初始化列表将值赋给成员变量
	}
};
#endif