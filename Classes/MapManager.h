#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MapManager :public Node {
private:
	int PlayerInWhichMap = 0;    //玩家所在的地图编号

	vector<TMXTiledMap*> MapList;     //储存已经加载的瓦片地图

	vector<Rect>ObstacleList;    //储存障碍物的矩形区域
	vector<Vec2>TeleportList;    //储存传送门的位置
	vector<Vec2>InteractionList;    //储存交互区域的位置

	vector<TMXLayer*> BlackFogList;    //储存黑雾的图层
	vector<bool> IsBlackFogVisible;    //黑雾是否可见
	vector<bool> IsRegionRevealed;    //是否已经显示过某个区域

	const int MapField = 1600;    //单张瓦片地图的大小
public:
	/*初始化地图障碍物*/
	void InitialObjects(TMXTiledMap* TiledMap, int mapIndex);
	
	/*初始化瓦片地图*/
	void InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene);
	
	/*返回某个瓦片地图*/
	TMXTiledMap* GetTiledMap(int MapID);

	/*设置整张瓦片地图的黑雾*/
	void SetBlackFogInMicroMap();

	/*获取黑雾列表的大小*/
	size_t GetBlackFogListSize();
	
	/*判断某个位置是否可以被移动到*/
	bool IsMoveable(const Vec2& pos);

	/*判断玩家所在的地图编号*/
	void PlayerPositionInWhichMap(Vec2& PlayerPosition);

	/*获取玩家所在的地图编号*/
	int GetPlayerInWhichMap()const;

	/*获取传送门的位置*/
	Vec2 GetTeleportPosition(int MapID)const;  

	/*解锁小地图以及其相应传送点*/
	void SetIsRegionRevealedTrue();

	/*设置黑雾是否可见*/
	void ReverseIsBlackFogVisible();

	/*瓦片地图坐标转场景坐标*/
	Vec2 tiledMapPosToScenePos(const Vec2& tiledMapPos, int mapIndex);

	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__