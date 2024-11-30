#ifndef __SET_PLAYER_SCENE_H__
#define __SET_PLAYER_SCENE_H__

#include <string>
#include "cocos2d.h"

class SetPlayerScene : public cocos2d::Scene {
public:
    /* �����Ϣ */
    std::string name;   // �������

    /* �������� */
    static cocos2d::Scene* createScene();      
    
    virtual bool init();      // ��ʼ����:��������

    Scene* selectRoleScene(); // ѡ���ɫ
    // void selectRoleScene();   // ѡ���ɫ

    void ChangeToInitMap();  // �л�����ʼ��ͼ

    CREATE_FUNC(SetPlayerScene);
};

#endif // __SET_PLAYER_SCENE_H__
