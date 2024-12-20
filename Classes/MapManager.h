#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

const int MapField = 1843;    //������Ƭ��ͼ�Ĵ�С
const Vec2 RTPos = Vec2(258.5f, 1568.5f + 720.0f - 647.0f + 720.0f - 647.0f-32.0f);    //RebirthTemple���Ͻǵĳ������꣬720.0f - 647.0f��������������
const float MapToSceneRatio = 1.151875f;    //��Ƭ��ͼ����ת��������ı���

class MapManager :public Node {
private:
	int PlayerInWhichMap = 0;    //������ڵĵ�ͼ���

	vector<TMXTiledMap*> MapList;     //�����Ѿ����ص���Ƭ��ͼ

	vector<Rect>ObstacleList;    //�����ϰ���ľ�������
	vector<Vec2>TeleportList;    //���洫���ŵ�λ��
	vector<pair<Vec2,string>>InDoorList;    //�����ͼ�ڵ��ŵ�λ���Լ���Ӧ�ĳ���
	vector<Vec2>InteractionList;    //���潻�������λ��

	vector<TMXLayer*> BlackFogList;    //��������ͼ��
	vector<bool> IsBlackFogVisible;    //�����Ƿ�ɼ�
	vector<bool> IsRegionRevealed;    //�Ƿ��Ѿ���ʾ��ĳ������

public:
	/*��ʼ����ͼ�ϰ���*/
	void InitialObjects(TMXTiledMap* TiledMap, int mapIndex);
	
	/*��ʼ����Ƭ��ͼ*/
	void InitialMap(const string mapName, const Vec2& MapPosition, Scene* TargetScene);
	
	/*����ĳ����Ƭ��ͼ*/
	TMXTiledMap* GetTiledMap(int MapID);

	/*����������Ƭ��ͼ�ĺ���*/
	void SetBlackFogInMicroMap();

	/*��ȡ�����б�Ĵ�С*/
	size_t GetBlackFogListSize();
	
	/*�ж�ĳ��λ���Ƿ���Ա��ƶ���*/
	bool IsMoveable(const Vec2& pos);

	/*�ж�ĳ��λ���Ƿ���Ա�����*/
	bool IsInteractable(const Vec2& pos);

	/*�ж�ĳ��ĳ��λ���Ƿ���Խ������͵�*/
	bool IsTeleportUnlockable(const Vec2& pos);

	/*�ж�ĳ��λ���Ƿ���Խ���ĳ����*/
	bool IsDoorIntoable(const Vec2& pos, string& SceneName);

	/*�ж�������ڵĵ�ͼ���*/
	void PlayerPositionInWhichMap(Vec2& PlayerPosition);

	/*��ȡ������ڵĵ�ͼ���*/
	int GetPlayerInWhichMap()const;

	/*��ȡ�����ŵ�λ��*/
	Vec2 GetTeleportPosition(int MapID)const;  

	/*��ȡ��Ӧ���͵��Ƿ��Ѿ�������*/
	bool GetIsRegionRevealed(int MapID)const;

	/*����С��ͼ�Լ�����Ӧ���͵�*/
	void SetIsRegionRevealedTrue();

	/*���ú����Ƿ�ɼ�*/
	void ReverseIsBlackFogVisible();

	/*��Ƭ��ͼ����ת��������*/
	Vec2 TiledMapPosToScenePos(const Vec2& tiledMapPos, int mapIndex);

	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__