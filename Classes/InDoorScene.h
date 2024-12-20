#ifndef __INDOOR_SCENE_H__
#define __INDOOR_SCENE_H__

#include "MainGameScene.h"
#include "cocos2d.h"

class InDoorScene : public MainGameScene {
private:
	string _mapName;    //室内地图名称
	Vec2 _playerPos;    //室内角色初始位置
public:
	/****************************************************************/
	////////////////以下为本场景所有用到的初始化函数/////////////////
	/*构造函数，从上一个场景传入角色*/
	InDoorScene(Player* origin_player, string mapName, Vec2 playerPos);

	/*生成场景函数*/
	static cocos2d::Scene* createScene(Player* origin_player);

	/*初始化地图函数*/
	virtual bool init();

	/*加载地图，重写父类*/
	void LoadMapToScene() override;

	/*加载人物，重写父类*/
	void LoadPlayerToScene() override;

	/*加载怪物管理器，重写父类*/
	void LoadMonsterRespawnToScene() override;

	/*加载NPC，重写父类*/
	void LoadNPCToScene() override;
};

#endif // __INDOOR_SCENE_H__