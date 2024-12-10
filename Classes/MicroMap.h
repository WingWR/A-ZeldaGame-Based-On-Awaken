#ifndef __MICRO_MAP_H__
#define __MICRO_MAP_H__

#include "cocos2d.h"

/*���������һ�������˲�ͬ����������Լ���ͬ��������ԣ���������
0��ɭ������1����ɽ����2��ɳĮ����3��ѩ������4����ʼ����*/

class MicroMap :public cocos2d::Layer {
private:
    cocos2d::Size visibleSize;    //��Ļ��С
    cocos2d::Sprite* MicroMapSprite;    //΢�����ͼ����
    cocos2d::Label* RegionLabel;    //�������Ʊ�ǩ

    std::vector<cocos2d::DrawNode*> BlackFogLayer;    //���ƺ����
    std::vector<cocos2d::Rect> MapReign;    //��ͼ������or������Ӧ����
   
    std::vector<std::string> ReignName;    //����������
    std::vector<bool> IsBlackFogVisited;    //�Ƿ��Ѿ����ʹ��ĺ����

    cocos2d::Vec2 PlayerPos;    //���λ��
    cocos2d::Sprite* PlayerSprite;    //��Ҿ���

public:

    /*��ʼ��΢�����ͼ*/
    virtual bool init();
   
    /*����΢�����ͼ�ĳ�ʼ������*/
    void OnEnterMicroMap();

    /*�����ͣ������ʱ�������¼�--�������͹����Լ���ʾ��������*/
    void OnMouseMove(cocos2d::Event* event);

    /*��ɢ�����*/
    void DisperseBlackFog(int ReignIndex);

    /*���������ͼ*/
    void UnlockReign(int ReignIndex);

    /*�ж�����Ƿ���ĳ��������,TypeIdΪ0ʱ��ʾΪ���Σ�TypeIdΪ1ʱ��ʾΪԲ��*/
    bool IsContainedReign(cocos2d::Rect& rect, cocos2d::Vec2& Pos, int TypeId);

   CREATE_FUNC(MicroMap);
};
#endif // __MICRO_MAP_H__