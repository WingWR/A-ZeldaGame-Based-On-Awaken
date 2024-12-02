#ifndef __MICRO_MAP_H__
#define __MICRO_MAP_H__

#include "cocos2d.h"

/*���������һ�������˲�ͬ����������Լ���ͬ��������ԣ���������
0����ʼ����1��ɭ������2����ɽ����3��ɳĮ����4��ѩ������*/

class MicroMap :public cocos2d::Layer {
private:
    cocos2d::Sprite* MicroMapSprite;    //΢�����ͼ����
    std::vector<cocos2d::Node*> BlackFogLayer;    //���ƺ����
    std::vector<cocos2d::Rect> MapReign;    //��ͼ������or������Ӧ����
    std::vector<std::string> ReignName;    //����������
    std::vector<bool> IsFogVisited;    //�Ƿ��Ѿ����ʹ��ĺ����
    cocos2d::Vec2 PlayerPos;    //���λ��
    cocos2d::Sprite* PlayerSprite;    //��Ҿ���

public:

    /*��ʼ��΢�����ͼ*/
    virtual bool init();
   
    /*�����ͣ������ʱ�������¼�--�������͹����Լ���ʾ��������*/
    void OnMouseOverReign();

    /*�������λ��*/
    void UpdatePlayerPos(cocos2d::Vec2& pos);

   CREATE_FUNC(MicroMap);
};

#endif // __MICRO_MAP_H__