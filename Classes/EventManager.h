#ifndef __EVENT_MANAGER_H__
#define __EVENT_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class EventManager :public Node {
private:
	vector<EventListenerMouse*> MouseListenerList;    //�����洢����¼�������
	vector<EventListenerKeyboard*> KeyBoardListenerList;    //�����洢�����¼�������

public:
	/* ��Ӽ����¼������������¼��̵�ʱ�����ɿ����̵�ʱ�򶼻ᴥ���ص����� */
	void AddKeyBoardListener(Node* TargetNode,
		function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed,
		function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyReleased);

	/* ��Ӽ����¼���������ֻ�ڰ��¼��̵�ʱ�򴥷��ص����� */
	void AddKeyBoardListener(Node* TargetNode,
		function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed);

	/* �������¼�������, ��������ʱ�򴥷��ص����� */
	void AddMouseListener(Node* TargetNode,
		function<void(EventMouse*)> OperationWhenMouseScroll);

	/*�Ƴ�����ĳ���ڵ�����м�����*/
	void RemoveAllListenersInTheNode(Node* TargetNode);

	CREATE_FUNC(EventManager);
}

#endif // __EVENT_MANAGER_H__