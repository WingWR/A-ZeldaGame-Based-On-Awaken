#ifndef __SET_PLAYER_SCENE_H__
#define __SET_PLAYER_SCENE_H__

#include <string>
#include "cocos2d.h"
#include "Player.h"

class SetPlayerScene : public cocos2d::Scene {
public:
    /* �����Ϣ */
    std::string name;   // �������
    std::string who;            // ѡ��Ľ�ɫ
    //Player* PLAYER;
    /* �������� */
    static cocos2d::Scene* createScene();      
    
    virtual bool init();      // ��ʼ����:��������

    Scene* selectRoleScene(); // ѡ���ɫ
    // void selectRoleScene();   // ѡ���ɫ



    // ���̰��µĻص�����
    // void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    CREATE_FUNC(SetPlayerScene);
};

#endif // __SET_PLAYER_SCENE_H__
