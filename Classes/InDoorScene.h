#ifndef __WINTER_HOUSE_H__
#define __WINTER_HOUSE_H__

#include "MainGameScene.h"
#include "cocos2d.h"

class InDoorScene : public MainGameScene {
private:
	string _mapName;    //���ڵ�ͼ����
	Vec2 _playerPos;    //���ڽ�ɫ��ʼλ��
public:
	/****************************************************************/
	////////////////����Ϊ�����������õ��ĳ�ʼ������/////////////////
	/*���캯��������һ�����������ɫ*/
	InDoorScene(Player* origin_player, string mapName, Vec2 playerPos);

	/*���ɳ�������*/
	static cocos2d::Scene* createScene(Player* origin_player);

	/*��ʼ����ͼ����*/
	virtual bool init();

	/*���ص�ͼ����д����*/
	void LoadMapToScene() override;

	/*���������д����*/
	void LoadPlayerToScene() override;

	/*���ع������������д����*/
	void LoadMonsterRespawnToScene() override;

	/*����NPC����д����*/
	void LoadNPCToScene() override;
};

#endif // __WINTER_HOUSE_H__