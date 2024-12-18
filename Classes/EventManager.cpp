#include "EventManager.h"

void EventManager::AddKeyBoardListener(Node* TargetNode,
	function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed,
	function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyReleased) {

	if (!TargetNode)
		return;    //���Ŀ��ڵ���߼�����Ϊ�գ���ֱ�ӷ���

	//�������̼�����
	auto Listener = EventListenerKeyboard::create();

	//���ü������Ļص�����
	Listener->onKeyPressed = OperationWhenKeyPressed;
	Listener->onKeyReleased = OperationWhenKeyReleased;

	//��Ӽ�������Ŀ��ڵ㲢�Ұ󶨵�����ͼ�����ȼ�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, TargetNode);

	//����������ӵ������¼��������б���
	KeyBoardListenerList.push_back(Listener);
}

void EventManager::AddKeyBoardListener(Node* TargetNode,
	function<void(EventKeyboard::KeyCode, Event*)> OperationWhenKeyPressed) {
	if (!TargetNode)
		return;    //���Ŀ��ڵ���߼�����Ϊ�գ���ֱ�ӷ���

	//�������̼�����
	auto Listener = EventListenerKeyboard::create();

	//���ü������Ļص�����
	Listener->onKeyPressed = OperationWhenKeyPressed;

	//��Ӽ�������Ŀ��ڵ㲢�Ұ󶨵�����ͼ�����ȼ�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, TargetNode);

	//����������ӵ������¼��������б���
	KeyBoardListenerList.push_back(Listener);
}

void EventManager::AddMouseListener(Node* TargetNode,function<void(EventMouse*)> OperationWhenMouseScroll) {
	if (!TargetNode)
		return;    //���Ŀ��ڵ���߼�����Ϊ�գ���ֱ�ӷ���

	//������������
	auto Listener = EventListenerMouse::create();

	//���ü������Ļص�����
	Listener->onMouseScroll = OperationWhenMouseScroll;

	//��Ӽ�������Ŀ��ڵ㲢�Ұ󶨵�����ͼ�����ȼ�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(Listener, TargetNode);

	//����������ӵ�����¼��������б���
	MouseListenerList.push_back(Listener);
}

void EventManager::RemoveAllListenersInTheNode(Node* TargetNode) {
	if (!TargetNode) 
		return;    //

	// �Ƴ���ڵ�󶨵����м�����
	_eventDispatcher->removeEventListenersForTarget(TargetNode);
}