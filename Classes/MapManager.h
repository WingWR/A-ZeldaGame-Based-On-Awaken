#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

const int MapField = 1843;    //单张瓦片地图的大小
const Vec2 RTPos = Vec2(258.5f, 1568.5f + 720.0f - 647.0f + 720.0f - 647.0f-32.0f);    //RebirthTemple左上角的场景坐标，720.0f - 647.0f是消除误差的修正
const float MapToSceneRatio = 1.151875f;    //瓦片地图坐标转场景坐标的比例

class MapManager :public Node {
private:
	int PlayerInWhichMap = 0;    //玩家所在的地图编号

	vector<TMXTiledMap*> MapList;     //储存已经加载的瓦片地图

	vector<Rect>ObstacleList;    //储存障碍物的矩形区域
	vector<Vec2>TeleportList;    //储存传送门的位置
	vector<pair<Vec2,string>>InDoorList;    //储存地图内的门的位置以及对应的场景
	vector<Vec2>InteractionList;    //储存交互区域的位置

	vector<TMXLayer*> BlackFogList;    //储存黑雾的图层
	vector<bool> IsBlackFogVisible;    //黑雾是否可见
	vector<bool> IsRegionRevealed;    //是否已经显示过某个区域

public:
	/*初始化地图障碍物*/
	void InitialObjects(TMXTiledMap* TiledMap, int mapIndex);
	
	/*初始化瓦片地图*/
	void InitialMap(const string mapName, const Vec2& MapPosition, Scene* TargetScene);
	
	/*返回某个瓦片地图*/
	TMXTiledMap* GetTiledMap(int MapID);

	/*设置整张瓦片地图的黑雾*/
	void SetBlackFogInMicroMap();

	/*获取黑雾列表的大小*/
	size_t GetBlackFogListSize();
	
	/*判断某个位置是否可以被移动到*/
	bool IsMoveable(const Vec2& pos);

	/*判断某个位置是否可以被交互*/
	bool IsInteractable(const Vec2& pos);

	/*判断某个某个位置是否可以解锁传送点*/
	bool IsTeleportUnlockable(const Vec2& pos);

	/*判断某个位置是否可以进入某个门*/
	bool IsDoorIntoable(const Vec2& pos, string& SceneName);

	/*判断玩家所在的地图编号*/
	void PlayerPositionInWhichMap(Vec2& PlayerPosition);

	/*获取玩家所在的地图编号*/
	int GetPlayerInWhichMap()const;

	/*获取传送门的位置*/
	Vec2 GetTeleportPosition(int MapID)const;

	/*获取相应传送点是否已经被解锁*/
	bool GetIsRegionRevealed(int MapID)const;

	/*获取相应传送点是否已经被解锁*/
	bool GetIsRegionRevealed(int MapID)const;

	/*解锁小地图以及其相应传送点*/
	void SetIsRegionRevealedTrue();

	/*设置黑雾是否可见*/
	void ReverseIsBlackFogVisible();

	/*瓦片地图坐标转场景坐标*/
	Vec2 TiledMapPosToScenePos(const Vec2& tiledMapPos, int mapIndex);

	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__