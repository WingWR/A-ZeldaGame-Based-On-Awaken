#ifndef __SET_PLAYER_SCENE_H__
#define __SET_PLAYER_SCENE_H__

#include <string>
#include "cocos2d.h"
#include "Player.h"

/* ��ɫ����:���ڱ�ʾѡ��Ľ�ɫ */
enum Who { Player1, Player2, Player3, Player4, Player5 };

class SetPlayerScene : public cocos2d::Scene {
public:
    /* �����Ϣ */
    std::string name;   // �������
    static int who;     // ѡ��Ľ�ɫ

    /* �������� */
    static cocos2d::Scene* createScene();      
    virtual bool init();        // ��ʼ����:��������
    Scene* selectRoleScene();   // ѡ���ɫ
 

    // ���̰��µĻص�����
    // void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    CREATE_FUNC(SetPlayerScene);
};

#endif // __SET_PLAYER_SCENE_H__
