#include "MapManager.h"

void MapManager::InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene) {
	auto TiledMap = TMXTiledMap::create(mapName);    //������ͼ����
	TiledMap->setAnchorPoint(Vec2(0.5f, 0.5f));    //���õ�ͼ��ê��Ϊ���ĵ�
	TiledMap->setPosition(MapPosition);    //���õ�ͼ��λ��
	TargetScene->addChild(TiledMap);    //����ͼ��ӵ�������

	MapList.push_back(TiledMap);    //����ͼ��ӵ��Ѿ������ĵ�ͼ�б���
	InitialObjects(TiledMap, (int)MapList.size() - 1);    //��ʼ���ϰ���

	BlackFogList.push_back(TiledMap->getLayer("BlackFog"));    //��ʼ����ɫ���б�
	IsBlackFogVisible.push_back(false);    //��ʼ����ɫ��Ŀɼ���Ϊfalse
	IsRegionRevealed.push_back(false);    //��ʼ����ͼ�����Ƿ񱻽�ʾΪfalse
}

void MapManager::PlayerPositionInWhichMap(Vec2& PlayerPosition) {
	for (int i = 0; i < (int)MapList.size(); i++) {
		if (MapList[i]->getBoundingBox().containsPoint(PlayerPosition)) {    //�ж�����Ƿ���ĳ����ͼ�ķ�Χ��
			PlayerInWhichMap = i;    //��������ڵĵ�ͼ���������浽PlayerInWhichMap������
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
	TMXObjectGroup* ObjectLayer = TiledMap->getObjectGroup("Obstacles");    //��ȡ�ϰ����
	if (ObjectLayer) {
		//�����ϰ����飬��ȡ�ϰ����λ����Ϣ
		auto Obstacles = ObjectLayer->getObjects();
		for (auto& Object : Obstacles) {
			ValueMap obstacle = Object.asValueMap();     //��ȡ�ϰ��������
			
			auto objectType=obstacle["type"].asString();    //��ȡ�ϰ��������

			if (objectType == "") {
				// ���ݶ������Ͷ�ȡ������
				// �ϰ���ȫΪ����
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();
				float width = obstacle["Width"].asFloat() * MapToSceneRatio;
				float height = obstacle["Height"].asFloat() * MapToSceneRatio;
				
				// ������������
				Rect obstacleRect(TiledMapPosToScenePos(Vec2(x, y), mapID).x, TiledMapPosToScenePos(Vec2(x, y), mapID).y - height, width, height);

				// ������Դ洢��ʹ�����������������ײ���
				// ������ӵ�һ���ϰ����б���
				ObstacleList.push_back(obstacleRect);
			}
			else if (objectType == "TeleportPoint") {
				// ���ݶ������Ͷ�ȡ������
				// ���͵�
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();
				// ���洫�͵�����
				TeleportList.push_back(TiledMapPosToScenePos(Vec2(x, y), mapID));
			}
			else if (objectType == "Interaction") {
				// ���ݶ������Ͷ�ȡ������
				// �ɽ�������
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();

				// ����ɽ�����������
				InteractionList.push_back(TiledMapPosToScenePos(Vec2(x, y), mapID));
			}
			else if (objectType == "InDoorPoint") {
				// ���ݶ������Ͷ�ȡ������
				// ��
				float x = obstacle["X"].asFloat();
				float y = obstacle["Y"].asFloat();
				// ��Ӧ����������
				string SceneName = obstacle["SceneName"].asString();

				// ����������
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
		BlackFogList[i]->setLocalZOrder(100);    //���ú�ɫ���ͼ�����ȼ��㹻�ߣ���֤���ڵ�ͼ����ʾ������Ԫ��֮��
		// ����������Ѿ�����ʾ�������غ�ɫ��������С��ͼ����ʾ��ɫ��
		BlackFogList[i]->setVisible(IsRegionRevealed[i] == true ? false : IsBlackFogVisible[i]);
	}
}

size_t MapManager::GetBlackFogListSize() {
	return BlackFogList.size();
}

bool MapManager::IsMoveable(const Vec2& Position) {
	//�����ϰ����б��е�ÿһ���ϰ���
	for (const auto& obstacle : ObstacleList) {
		if (obstacle.containsPoint(Position)) {

			/// ����������ײ�����ϰ��ﷶΧ�ڣ��򲻿��ƶ�
			return false;
		}
	}

	// ���λ�ò����ϰ��ﷶΧ�ڣ�����ƶ�
	return true;
}

bool MapManager::IsInteractable(const Vec2& Position) {
	//�����ɽ��������б��е�ÿһ���ɽ�������
	for (const auto& interactpos: InteractionList) {
		if (Position.distance(interactpos) < 32.0f) {

			// �������ڿɽ��������ڣ���ɽ���
			return true;
		}
	}

	// ���λ�ò��ڿɽ�������Χ�ڣ��򲻿ɽ���
	return false;
}

bool MapManager::IsTeleportUnlockable(const Vec2& pos) {
	//�������͵��б��е�ÿһ�����͵�
	for (const auto& teleport : TeleportList) {
		if (pos.distance(teleport) < 32.0f) {

			// �������ڴ��͵㷶Χ�ڣ����͵��ʹ��
			return true;
		}
	}

	// ���λ�ò��ڴ��͵㷶Χ�ڣ����͵㲻��ʹ��
	return false;
}

bool MapManager::IsDoorIntoable(const Vec2& pos,string& SceneName) {
	//�������͵��б��е�ÿһ�����͵�
	for (const auto& teleport : InDoorList) {
		if (pos.distance(teleport.first) < 32.0f) {

			// �������ڴ��͵㷶Χ�ڣ����͵��ʹ��
			SceneName = teleport.second;
			return true;
		}
	}

	// ���λ�ò��ڴ��͵㷶Χ�ڣ����͵㲻��ʹ��
	return false;
}

Vec2 MapManager::GetTeleportPosition(int mapID)const {
	// ��ȡָ����ͼ�Ĵ��͵�����
	if (IsRegionRevealed[PlayerInWhichMap] == false) {
		// ������͵��б�Ϊ�ջ���Ҳ��ڴ��͵��б��У��򷵻�Vec2::ZERO
		return Vec2::ZERO;
	}
	return TeleportList[PlayerInWhichMap];
}

void MapManager::ReverseIsBlackFogVisible() {
	// ��ת��ɫ��Ŀɼ���
	for (int i = 0; i < (int)IsBlackFogVisible.size(); i++) {
		IsBlackFogVisible[i] = !IsBlackFogVisible[i];
	}
}

void MapManager::SetIsRegionRevealedTrue() {
	// ����С��ͼ�Լ�����Ӧ���͵�
	if (IsRegionRevealed[PlayerInWhichMap] == false) {
		IsRegionRevealed[PlayerInWhichMap] = true;
	}
}

Vec2 MapManager::TiledMapPosToScenePos(const Vec2& tiledMapPos, int mapIndex) {
	// ����Ƭ��ͼ����ϵ�е�λ��ת��Ϊ��������ϵ�е�λ��
	// ��Ƭ��ͼ����ϵ��ԭ�������Ͻǣ�����������ϵ��ԭ�������½�
	if (mapIndex < 0 || mapIndex >= (int)MapList.size()) {
		return Vec2::ZERO;
	}
	Vec2 scenePos;
	Vec2 tiledMapPosRect = tiledMapPos * MapToSceneRatio; // ��Ƭ��ͼ����ϵ�е�λ�ó������ű���
	tiledMapPosRect.y = -tiledMapPosRect.y;               // y�᷽����Ҫ����ת��
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