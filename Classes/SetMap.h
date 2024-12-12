#ifndef __SET_MAP_H__
#define __SET_MAP_H__

#include <vector>
#include "cocos2d.h"
#include "MicroMap.h"
#include "Player.h"
#include "SetPlayerScene.h"
#include "BagManager.h"

USING_NS_CC;

class SetMap :public cocos2d::Scene {
private:
	MicroMap* MicroMap;     // ΢��ͼ����
	bool IsMicroMapVisible;     // ΢��ͼ�Ƿ�ɼ�

	int PlayerInWhichMap;  // ��ǰ������ڵĵ�ͼ���

	std::vector<cocos2d::Rect>ObstacleList;  // �ϰ����б�

public:
	////////////////////////////////////////////////////////////////
	/* �����Ƿ���:W/S/A/D*/
	std::vector<bool> isKeyPressed = { false,false,false,false };
	// ���
	Player* PLAYER;
	// ����Monster1
	Player* Monster1;
	Player* Monster2;
	// NPC
	Player* npc1;


	
	
	void KeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			if (isKeyPressed[0]) {
				isKeyPressed[0] = false;
				this->unschedule("MoveUP");
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			if (isKeyPressed[1]) {
				isKeyPressed[1] = false;
				this->unschedule("MoveDOWN");
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			if (isKeyPressed[2]) {
				isKeyPressed[2] = false;
				this->unschedule("MoveLEFT");
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			if (isKeyPressed[3]) {
				isKeyPressed[3] = false;
				this->unschedule("MoveRIGHT");
			}
		}
	}

	// ������
	void KeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
		Vec2 moveBy;
		int speed = 1;
		/* ����:I/K/J/L */
		if (keyCode == EventKeyboard::KeyCode::KEY_I)
			PLAYER->Attack(UP);
		else if (keyCode == EventKeyboard::KeyCode::KEY_K)
			PLAYER->Attack(DOWN);
		else if (keyCode == EventKeyboard::KeyCode::KEY_J)
			PLAYER->Attack(LEFT);
		else if (keyCode == EventKeyboard::KeyCode::KEY_L)
			PLAYER->Attack(RIGHT);
		/* �ƶ�:W/S/A/D */
		else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[0]) {
					isKeyPressed[0] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(UP);
						}, 0.34f, "MoveUP");
				}
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_S){
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[1]) {
					isKeyPressed[1] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(DOWN);
						}, 0.34f, "MoveDOWN");
				}
			}	
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_A){
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[2]) {
					isKeyPressed[2] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(LEFT);
						}, 0.34f, "MoveLEFT");
				}
			}
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D){ 
			moveBy = Vec2(0, -speed);
			Vec2 targetPosition = PLAYER->mySprite->getPosition() + moveBy;
			if (IsMoveable(targetPosition)) {
				if (!isKeyPressed[3]) {
					isKeyPressed[3] = true;
					this->schedule([&](float dt) {
						PLAYER->Move(RIGHT);
						}, 0.34f, "MoveRIGHT");
				}
			}
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
			Monster2->Attack(UP);
			//PLAYER->Heal();
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
		else if (keyCode == EventKeyboard::KeyCode::KEY_P){
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