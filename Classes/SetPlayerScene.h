#ifndef __SET_PLAYER_SCENE_H__
#define __SET_PLAYER_SCENE_H__

#include <string>
#include "cocos2d.h"
#include "Player.h"

class SetPlayerScene : public cocos2d::Scene {
public:
    /* 玩家信息 */
    std::string name;   // 玩家姓名
    std::string who;            // 选择的角色
    //Player* PLAYER;
    /* 场景函数 */
    static cocos2d::Scene* createScene();      
    
    virtual bool init();      // 初始场景:输入姓名

    Scene* selectRoleScene(); // 选择角色
    // void selectRoleScene();   // 选择角色



    // 键盘按下的回调函数
    // void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

    CREATE_FUNC(SetPlayerScene);
};

#endif // __SET_PLAYER_SCENE_H__
