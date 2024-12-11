#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"

class SetMap :public cocos2d::Scene {
private:
	MicroMap* MicroMap;     // ΢��ͼ����
	bool IsMicroMapVisible;     // ΢��ͼ�Ƿ�ɼ�

	int PlayerInWhichMap;  // ��ǰ������ڵĵ�ͼ���

	std::vector<cocos2d::Rect>ObstacleList;  // �ϰ����б�

public:
	////////////////////////////////////////////////////////////////
	// ���
	Player* PLAYER;
	// ����Monster1
	Player* Monster1;
	Player* Monster2;
	// NPC
	Player* npc1;
	// ������

	
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
		Vec2 moveBy;
		int speed = 1;

		if (keyCode == EventKeyboard::KeyCode::KEY_I)
			PLAYER->Attack(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_K)
			PLAYER->Attack(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
			PLAYER->Attack(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_L)
			PLAYER->Attack(RIGHT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		{
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

			if (IsMoveable(targetPosition))
				PLAYER->Move(DOWN);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

			if (IsMoveable(targetPosition))
				PLAYER->Move(UP);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		{
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

			if (IsMoveable(targetPosition))
				PLAYER->Move(LEFT);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		{ 
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;

			if (IsMoveable(targetPosition))
				PLAYER->Move(RIGHT);
		}
			// ����Monster1����Ч���ã��ǵ�ɾ
		else if (keyCode == EventKeyboard::KeyCode::KEY_T) {
			int dx = Monster1->mySprite->getPosition().x - PLAYER->mySprite->getPosition().x;
			int dy = Monster1->mySprite->getPosition().y - PLAYER->mySprite->getPosition().y;
			if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(Monster1->getAtkRange(), 2))
				Monster1->Attack(DOWN, PLAYER);
			else
				Monster1->Attack();
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_Y) {
			PLAYER->Heal();
			//PLAYER->Die();
		}

		// ����B��֮����߼�:����
		else if (keyCode == EventKeyboard::KeyCode::KEY_B) {
			
			if (BagManager::getInstance()->isBagVisible())
				// ���ر���
				BagManager::getInstance()->hideBag(*PLAYER);
			else
				// �򿪱���
				BagManager::getInstance()->showBag(*PLAYER);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_P)
		{
			goods _goods;
			if (BagManager::getInstance()->getItemsNum() % 5 == 0)
			{
				weapon* it1 = new weapon(_goods.icon_sword);
				BagManager::getInstance()->addItem(it1);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 1)
			{
				consumable* it2 = new consumable(_goods.pumkin);
				BagManager::getInstance()->addItem(it2);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 2)
			{
				accessories* it3 = new accessories(_goods.bomb);
				BagManager::getInstance()->addItem(it3);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 3)
			{
				armor* it4 = new armor(_goods.icon_conselet);
				BagManager::getInstance()->addItem(it4);
				return;
			}

			if (BagManager::getInstance()->getItemsNum() % 5 == 4)
			{
				shoes* it5 = new shoes(_goods.boots);
				BagManager::getInstance()->addItem(it5);
				return;
			}
		}
	}
	//////////////////////////////////////////////////////////////


	/*���ɳ�������*/
	static cocos2d::Scene* createScene();

	/*��ʼ����ͼ����*/
	virtual bool init();

	// �����¼�����,����M���л���ʾ΢��ͼ
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	/*�����������������ƶ�*/
	void CameraFollowPlayer();

	/*��ʼ���ϰ���*/
	void InitialObstacle(cocos2d::TMXTiledMap* tileMap);

	/*�ж�ĳ��λ���Ƿ�����ƶ�*/
	bool IsMoveable(cocos2d::Vec2& pos);

	CREATE_FUNC(SetMap);
};

#endif // __SET_MAP_H__