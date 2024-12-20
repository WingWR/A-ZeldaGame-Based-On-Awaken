#include "MapManager.h"

void MapManager::InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene) {
	auto TiledMap = TMXTiledMap::create(mapName);    //创建地图对象
	TiledMap->setAnchorPoint(Vec2(0.5f, 0.5f));    //设置地图的锚点为中心点
	TiledMap->setPosition(MapPosition);    //设置地图的位置
	TargetScene->addChild(TiledMap);    //将地图添加到场景中

	MapList.push_back(TiledMap);    //将地图添加到已经创建的地图列表中
	InitialObjects(TiledMap, (int)MapList.size() - 1);    //初始化障碍物

	BlackFogList.push_back(TiledMap->getLayer("BlackFog"));    //初始化黑色雾列表
	IsBlackFogVisible.push_back(false);    //初始化黑色雾的可见性为false
	IsRegionRevealed.push_back(false);    //初始化地图区域是否被揭示为false
}

void MapManager::PlayerPositionInWhichMap(Vec2& PlayerPosition) {
	for (int i = 0; i < (int)MapList.size(); i++) {
		if (MapList[i]->getBoundingBox().containsPoint(PlayerPosition)) {    //判断玩家是否在某个地图的范围内
			PlayerInWhichMap = i;    //将玩家所在的地图的索引保存到PlayerInWhichMap变量中
			return;
		}
	}	
}

TMXTiledMap* MapManager::GetTiledMap(int MapID) {
	return MapList[MapID];
}

int MapManager::GetPlayerInWhichMap() const { 
	return PlayerInWhichMap;
}

void MapManager::InitialObjects(TMXTiledMap* TiledMap, int mapID) {
	TMXObjectGroup* ObjectLayer = TiledMap->getObjectGroup("Obstacles");    //获取障碍物层
	if (ObjectLayer) {
		//遍历障碍物组，获取障碍物的位置信息
		auto Obstacles = ObjectLayer->getObjects();
		for (auto& Object : Obstacles) {
			ValueMap obstacle = Object.asValueMap();     //获取障碍物的属性
			
			auto objectType=obstacle["type"].asString();    //获取障碍物的类型

			if (objectType == "") {
				// 根据对象类型读取其属性
				// 障碍物全为矩形
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();
				float width = obstacle["Width"].asFloat() * MapToSceneRatio;
				float height = obstacle["Height"].asFloat() * MapToSceneRatio;
				
				// 创建矩形区域
				Rect obstacleRect(TiledMapPosToScenePos(Vec2(x, y), mapID).x, TiledMapPosToScenePos(Vec2(x, y), mapID).y - height, width, height);

				// 这里可以存储或使用这个区域来进行碰撞检测
				// 比如添加到一个障碍物列表中
				ObstacleList.push_back(obstacleRect);
			}
			else if (objectType == "TeleportPoint") {
				// 根据对象类型读取其属性
				// 传送点
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();
				// 保存传送点坐标
				TeleportList.push_back(TiledMapPosToScenePos(Vec2(x, y), mapID));
			}
			else if (objectType == "Interaction") {
				// 根据对象类型读取其属性
				// 可交互区域
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();

				// 保存可交互区域坐标
				InteractionList.push_back(TiledMapPosToScenePos(Vec2(x, y), mapID));
			}
			else if (objectType == "InDoorPoint") {
				// 根据对象类型读取其属性
				// 门
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();
				// 对应场景的名称
				string SceneName = obstacle["SceneName"].asString();

				// 保存门坐标
				InDoorList.push_back({ TiledMapPosToScenePos(Vec2(x, y), mapID), SceneName });
			}
		}
	}
}

void MapManager::SetBlackFogInMicroMap() {
	for (int i = 0; i < (int)BlackFogList.size(); i++) {
		if (!BlackFogList[i]->getParent()) {
			this->addChild(BlackFogList[i]);
		}
		BlackFogList[i]->setLocalZOrder(100);    //设置黑色雾的图层优先级足够高，保证它在地图上显示在其他元素之上
		// 如果此区域已经被揭示，则隐藏黑色雾，否则在小地图上显示黑色雾
		BlackFogList[i]->setVisible(IsRegionRevealed[i] == true ? false : IsBlackFogVisible[i]);
	}
}

size_t MapManager::GetBlackFogListSize() {
	return BlackFogList.size();
}

bool MapManager::IsMoveable(const Vec2& Position) {
	//遍历障碍物列表中的每一个障碍物
	for (const auto& obstacle : ObstacleList) {
		if (obstacle.containsPoint(Position)) {

			/// 如果人物的碰撞箱在障碍物范围内，则不可移动
			return false;
		}
	}

	// 如果位置不在障碍物范围内，则可移动
	return true;
}

bool MapManager::IsInteractable(const Vec2& Position) {
	//遍历可交互区域列表中的每一个可交互区域
	for (const auto& interactpos: InteractionList) {
		if (Position.distance(interactpos) < 32.0f) {

			// 如果玩家在可交互区域内，则可交互
			return true;
		}
	}

	// 如果位置不在可交互区域范围内，则不可交互
	return false;
}

bool MapManager::IsTeleportUnlockable(const Vec2& pos) {
	//遍历传送点列表中的每一个传送点
	for (const auto& teleport : TeleportList) {
		if (pos.distance(teleport) < 32.0f) {

			// 如果玩家在传送点范围内，则传送点可使用
			return true;
		}
	}

	// 如果位置不在传送点范围内，则传送点不可使用
	return false;
}

bool MapManager::IsDoorIntoable(const Vec2& pos,string& SceneName) {
	//遍历传送点列表中的每一个传送点
	for (const auto& teleport : InDoorList) {
		if (pos.distance(teleport.first) < 32.0f) {

			// 如果玩家在传送点范围内，则传送点可使用
			SceneName = teleport.second;
			return true;
		}
	}

	// 如果位置不在传送点范围内，则传送点不可使用
	return false;
}

Vec2 MapManager::GetTeleportPosition(int mapID)const {
	// 获取指定地图的传送点坐标
	if (mapID < 0 || mapID >= (int)TeleportList.size()) {
		return Vec2(-10000, -10000);
	}
	if (mapID == 0) { //RebirthTemple
		return TeleportList[0];
	}
	else if (mapID == 1) { //volcano
		return TeleportList[1];
	}
	else if (mapID == 2) { //SnowyWinter
		return TeleportList[2];
	}
	else if (mapID == 3) { //DeathDesert
		return TeleportList[3];
	}
	else if (mapID == 4) { //BrightForest
		return TeleportList[4];
	}
	else
		return Vec2(-10000,-10000);
}

void MapManager::ReverseIsBlackFogVisible() {
	// 反转黑色雾的可见性
	for (int i = 0; i < (int)IsBlackFogVisible.size(); i++) {
		IsBlackFogVisible[i] = !IsBlackFogVisible[i];
	}
}

void MapManager::SetIsRegionRevealedTrue() {
	// 解锁小地图以及其相应传送点
	if (IsRegionRevealed[PlayerInWhichMap] == false) {
		IsRegionRevealed[PlayerInWhichMap] = true;
		if (PlayerInWhichMap == 0) { //RebirthTemple
			;
		}
		else if (PlayerInWhichMap == 1) { //volcano
			IsRegionRevealed[6] = true;
		}
		else if (PlayerInWhichMap == 2) { //SnowyWinter
			IsRegionRevealed[5] = true;
		}
		else if (PlayerInWhichMap == 3) { //DeathDesert
			IsRegionRevealed[7] = true;
		}
		else if (PlayerInWhichMap == 4) { //BrightForest
			IsRegionRevealed[8] = true;
		}
	}
}

bool MapManager::GetIsRegionRevealed(int MapID)const {
	// 获取指定地图的区域是否被揭示
	return IsRegionRevealed[MapID];
}

Vec2 MapManager::TiledMapPosToScenePos(const Vec2& tiledMapPos, int mapIndex) {
	// 将瓦片地图坐标系中的位置转换为场景坐标系中的位置
	// 瓦片地图坐标系的原点在左上角，而场景坐标系的原点在左下角
	if (mapIndex < 0 || mapIndex >= (int)MapList.size()) {
		return Vec2::ZERO;
	}
	Vec2 scenePos;
	Vec2 tiledMapPosRect = tiledMapPos * MapToSceneRatio; // 瓦片地图坐标系中的位置乘以缩放比例
	tiledMapPosRect.y = -tiledMapPosRect.y;               // y轴方向需要反向转换
	if (mapIndex == 0) { //RebirthTemple
		scenePos.x = tiledMapPosRect.x + RTPos.x;
		scenePos.y = tiledMapPosRect.y + RTPos.y;
	}
	else if (mapIndex == 1) { //volcano
		scenePos.x = tiledMapPosRect.x + RTPos.x - MapField ;
		scenePos.y = tiledMapPosRect.y + RTPos.y + MapField;
	}
	else if (mapIndex == 2) { //SnowyWinter
		scenePos.x = tiledMapPosRect.x + RTPos.x + MapField;
		scenePos.y = tiledMapPosRect.y + RTPos.y + MapField;
	}
	else if (mapIndex == 3) { //DeathDesert
		scenePos.x = tiledMapPosRect.x + RTPos.y + MapField;
		scenePos.y = tiledMapPosRect.y + RTPos.y - MapField;
	}
	else if (mapIndex == 4) { //BrightForest
		scenePos.x = tiledMapPosRect.x + RTPos.x - MapField;
		scenePos.y = tiledMapPosRect.y + RTPos.y - MapField;
	}
	else if (mapIndex == 5) { //Vol_Snow
		scenePos.x = tiledMapPosRect.x + RTPos.x;
		scenePos.y = tiledMapPosRect.y + RTPos.y + MapField;
	}
	else if (mapIndex == 6) { //Vol_Forest
		scenePos.x = tiledMapPosRect.x + RTPos.x - MapField;
		scenePos.y = tiledMapPosRect.y + RTPos.y;
	}
	else if (mapIndex == 7) { //Snow_Desert
		scenePos.x = tiledMapPosRect.x + RTPos.x + MapField;
		scenePos.y = tiledMapPosRect.y + RTPos.y;
	}
	else if (mapIndex == 8) { //Forest_Desert
		scenePos.x = tiledMapPosRect.x + RTPos.x;
		scenePos.y = tiledMapPosRect.y + RTPos.y - MapField;
	}
	else
		scenePos = Vec2::ZERO;

	return scenePos;
}