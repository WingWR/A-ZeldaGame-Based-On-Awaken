#include <string>
#include "Player.h"
#include "Monster.h"

// update
void Player::update(float dt) {
    x = getXY().x;
    y = getXY().y;
    Vec2 pos = mySprite->getPosition();
    static int nums = 50;
    if (nums < 60) {
        nums++;
    }
    else {
        nums = 0;
      
        
        log("player**********************************");
        log("position:%f %f", pos.x, pos.y);
        log("hp:%d", hp);
        log("mp:%d", mp);
        log("atk:%d", atk);
        log("def:%d", def);
        
    }
    Vec2 move_by;

   

    if (is_moving) {
        if (face_to == 0) {
            move_by.set(-speed / 60.0, 0);
        }
        else if (face_to == 1) {
            move_by.set(speed / 60.0, 0);
        }
        else if (face_to == 2) {
            move_by.set(0, speed / 60.0);
        }
        else if (face_to == 3) {
            move_by.set(0, -speed / 60.0);
        }
        Vec2 targetPosition = mySprite->getPosition() + move_by;

        if (map_manager->IsMoveable(targetPosition)) {
            if (face_to == 0) {
                mySprite->setPosition(x + move_by.x, y + move_by.y);

            }
            else if (face_to == 1) {
                mySprite->setPosition(x + move_by.x, y + move_by.y);

            }
            else if (face_to == 2) {
                mySprite->setPosition(x + move_by.x, y + move_by.y);

            }
            else if (face_to == 3) {
                mySprite->setPosition(x + move_by.x, y + move_by.y);

            }
            ChangeXY(move_by);
        }
    }

    // 计算血量占总血量的比例
    float healthPercentage = (float)current_hp / (float)hp;

    // 获取当前血条的宽度
    Size healthBarSize = healthBar->getContentSize();
    healthBar->setScaleX(healthPercentage);  // 调整血条的横向缩放比例

    // 更新hp值
    hpLabel->setString("hp:" + to_string(current_hp));
}

void Player::Init(vector<Monster*>monster, MapManager* map_manager) {
    this->monster = monster;
    this->map_manager = map_manager;
}
// 人物攻击
// 攻击范围是扇形
void Player::Attack(vector<Monster*> monster) {
    int dir = getDir();
    Vec2 pos_player = mySprite->getPosition();
    for (int i = 0; i < monster.size(); i++) {
        Vec2 pos_monster = monster[i]->mySprite->getPosition();
        float distance = pos_monster.distance(pos_player);
        if (distance < atk_range) {
            Vec2 direction = pos_monster - pos_player;// 人物指向怪物
            float k = (direction.x + 1.0 - 1.0) / direction.y;// 斜率
            if (dir == 0 && k<1 && k>-1 && direction.x < 0) {// 向左
                log("player attack左&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&");
                monster[i]->Hurt();
                monster[i]->DecreaseHp(DamageCal(this, monster[i]));
            }
            else if (dir == 1 && k<1 && k>-1 && direction.x > 0) {// ��
                monster[i]->Hurt();
                monster[i]->DecreaseHp(DamageCal(this, monster[i]));
            }
            else if (dir == 2 && (k < -1 || k>1) && direction.y > 0) {// ��
                monster[i]->Hurt();
                monster[i]->DecreaseHp(DamageCal(this, monster[i]));
            }
            else if (dir == 3 && (k < -1 || k>1) && direction.y < 0) {// ��
                monster[i]->Hurt();
                monster[i]->DecreaseHp(DamageCal(this, monster[i]));
            }
        }
    }
    Creature::Attack();
    return;
}
void Player::Skill(int skill_num,vector<Monster*>monster) {
    if (skill_num == 1) {
        //技能1
        Skill_Animate1();
        //技能1的攻击范围是圆形
        Vec2 pos_player = mySprite->getPosition();
        for (int i = 0; i < monster.size(); i++) {
            Vec2 pos_monster = monster[i]->mySprite->getPosition();
            float distance = pos_monster.distance(pos_player);
            if (distance < 100) {
                monster[i]->Hurt();
                monster[i]->DecreaseHp(DamageCal(this, monster[i]));
            }
        }
    }
    else if (skill_num == 2) {
        //技能2
        Skill_Animate2();
        //技能2的攻击范围是扇形
        int dir = getDir();
        Vec2 pos_player = mySprite->getPosition();
        for (int i = 0; i < monster.size(); i++) {
            Vec2 pos_monster = monster[i]->mySprite->getPosition();
            float distance = pos_monster.distance(pos_player);
            if (distance < atk_range) {
                Vec2 direction = pos_monster - pos_player;// 人物指向怪物
                float k = (direction.x + 1.0 - 1.0) / direction.y;// 斜率
                if (dir == 0 && k<1 && k>-1 && direction.x < 0) {// 向左
                    monster[i]->Hurt();
                    monster[i]->DecreaseHp(DamageCal(this, monster[i]));
                }
                else if (dir == 1 && k<1 && k>-1 && direction.x > 0) {// 右
                    monster[i]->Hurt();
                    monster[i]->DecreaseHp(DamageCal(this, monster[i]));
                }
                else if (dir == 2 && (k < -1 || k>1) && direction.y > 0) {// 上
                    monster[i]->Hurt();
                    monster[i]->DecreaseHp(DamageCal(this, monster[i]));
                }
                else if (dir == 3 && (k < -1 || k>1) && direction.y < 0) {// 下
                    monster[i]->Hurt();
                    monster[i]->DecreaseHp(DamageCal(this, monster[i]));
                }
            }
        }
    }
}
//
void Player::Skill_Animate1() {
    //技能1的动画
    auto particleSystem = ParticleSystemQuad::create("Aura.plist");

    // 设置粒子系统的位置
    particleSystem->setPosition(mySprite->getPosition());

    // 设置粒子系统其他属性
    particleSystem->setLife(1.0f); // 粒子生命周期
    particleSystem->setLifeVar(0.5f); // 生命周期变化
    particleSystem->setSpeed(200); // 粒子速度
    particleSystem->setSpeedVar(50); // 速度变化
    particleSystem->setEmissionRate(1000); // 发射率
    particleSystem->setGravity(Vec2(0, -200)); // 重力

    // 设置粒子图片
    particleSystem->setTexture(Director::getInstance()->getTextureCache()->addImage("Aura.png"));

    // 将粒子系统添加到人物节点
    mySprite->addChild(particleSystem);

    // 启动粒子系统
    particleSystem->resetSystem();
}
//技能2的动画
void Player::Skill_Animate2() {

}
// Player获得奖励
void Player::GetBonus(Bonus bonus) {
    //经验奖励
    current_exp += bonus.exp;
    //升级
    while (current_exp >= next_level_exp) {
        current_exp -= next_level_exp;
        level++;
        next_level_exp *= (1 + level * 0.1);
    }

    //物品奖励
    //暂待，需物品和装备

}

// 判断交互范围
bool Player::isTrigger(const Vec2& pos) {

    int dx = mySprite->getPosition().x - pos.x;
    int dy = mySprite->getPosition().y - pos.y;

    return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);

}
// 改变is_moving
void Player::ChangeIsMoving() {
    if (is_moving == 1) {
        is_moving = 0;
    }
    else {
        is_moving = 1;
    }
}
