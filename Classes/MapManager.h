#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class MapManager :public Node {
private:
	int PlayerInWhichMap = 0;    //������ڵĵ�ͼ���

	vector<TMXTiledMap*> MapList;     //�����Ѿ����ص���Ƭ��ͼ

	vector<Rect>ObstacleList;    //�����ϰ���ľ�������
	vector<Vec2>TeleportList;    //���洫���ŵ�λ��
	vector<Vec2>InteractionList;    //���潻�������λ��

	vector<TMXLayer*> BlackFogList;    //���������ͼ��
	vector<bool> IsBlackFogVisible;    //�����Ƿ�ɼ�
	vector<bool> IsRegionRevealed;    //�Ƿ��Ѿ���ʾ��ĳ������

	const int MapField = 1600;    //������Ƭ��ͼ�Ĵ�С
public:
	/*��ʼ����ͼ�ϰ���*/
	void InitialObjects(TMXTiledMap* TiledMap);
	
	/*��ʼ����Ƭ��ͼ*/
	void InitialMap(const char* mapName, const Vec2& MapPosition, Scene* TargetScene);
	
	/*����ĳ�����ݵ�ͼ�ĺ���*/
	void SetBlackFogInMicroMap(TMXTiledMap* TiledMap);
	
	/*�ж�ĳ��λ���Ƿ���Ա��ƶ���*/
	bool IsMoveable(const Vec2& pos);

	/*�ж�������ڵĵ�ͼ���*/
	void PlayerPositionInWhichMap(Vec2& PlayerPosition);

	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__