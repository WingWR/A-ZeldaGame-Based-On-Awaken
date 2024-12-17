#include "MapManager.h"

void MapManager::InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene) {
	auto TiledMap = TMXTiledMap::create(mapName);    //������ͼ����
	TiledMap->setAnchorPoint(Vec2(0.5f, 0.5f));    //���õ�ͼ��ê��Ϊ���ĵ�
	TiledMap->setPosition(MapPosition);    //���õ�ͼ��λ��
	//this->InitialObstacles(TiledMap);    //��ʼ���ϰ���
	TargetScene->addChild(TiledMap);    //����ͼ��ӵ�������

	MapList.push_back(TiledMap);    //����ͼ��ӵ��Ѿ������ĵ�ͼ�б���
	IsBlackFogVisible.push_back(true);    //��ʼ����ɫ��Ŀɼ���Ϊfalse
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

void MapManager::InitialObjects(TMXTiledMap* TiledMap) {
	TMXObjectGroup* ObjectLayer = TiledMap->getObjectGroup("Obstacles");    //��ȡ�ϰ����
	if (ObjectLayer) {
		//�����ϰ����飬��ȡ�ϰ����λ����Ϣ
		auto Obstacles = ObjectLayer->getObjects();
		for (auto& Object : Obstacles) {
			ValueMap obstacle = Object.asValueMap();     //��ȡ�ϰ��������
			
			auto objectType=obstacle["type"].asString();    //��ȡ�ϰ��������
			
			if (objectType == "rectangle") {
				// ���ݶ������Ͷ�ȡ������
				// �ϰ���ȫΪ����
				float x = obstacle["x"].asFloat();
				float y = obstacle["y"].asFloat();
				float width = obstacle["width"].asFloat();
				float height = obstacle["height"].asFloat();

				// ������������
				Rect obstacleRect(x, y, width, height);

				// ������Դ洢��ʹ�����������������ײ���
				// ������ӵ�һ���ϰ����б���
				ObstacleList.push_back(obstacleRect);
			}
		}
	}
}

void MapManager::SetBlackFogInMicroMap(TMXTiledMap* TiledMap) {
	for (int i = 0; i < (int)BlackFogList.size(); i++) {
		if (!BlackFogList[i]->getParent()) {
			this->addChild(BlackFogList[i]);
		}
		BlackFogList[i]->setLocalZOrder(100);    //���ú�ɫ���ͼ�����ȼ��㹻�ߣ���֤���ڵ�ͼ����ʾ������Ԫ��֮��
		// ����������Ѿ�����ʾ�������غ�ɫ��������С��ͼ����ʾ��ɫ��
		BlackFogList[i]->setVisible(IsRegionRevealed[i] == true ? false : IsBlackFogVisible[i]);
	}
}

bool MapManager::IsMoveable(const Vec2& Position) {
	//�����ϰ����б��е�ÿһ���ϰ���
	for (const auto& obstacle : ObstacleList) {
		if (obstacle.containsPoint(Position)) {
			/// ���λ�����ϰ��ﷶΧ�ڣ��򲻿��ƶ�
			return false;
		}
	}

	// ���λ�ò����ϰ��ﷶΧ�ڣ�����ƶ�
	return true;
}