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

    //// ����Ѫ��ռ��Ѫ���ı���
    //float healthPercentage = (float)current_hp / (float)hp;

    //// ��ȡ��ǰѪ���Ŀ��
    //Size healthBarSize = healthBar->getContentSize();
    //healthBar->setScaleX(healthPercentage);  // ����Ѫ���ĺ������ű���

    //// ����hpֵ
    //hpLabel->setString("hp:" + to_string(current_hp));
}

void Player::Init(vector<Monster*>monster, MapManager* map_manager) {
    this->monster = monster;
    this->map_manager = map_manager;
}
// ���﹥��
// ������Χ������
Animate* Player::Attack(vector<Monster*> monster) {
    int dir = getDir();
    Vec2 pos_player = mySprite->getPosition();
    for (int i = 0; i < monster.size(); i++) {
        Vec2 pos_monster = monster[i]->mySprite->getPosition();
        float distance = pos_monster.distance(pos_player);
        if (distance < atk_range) {
            Vec2 direction = pos_monster - pos_player;// ����ָ�����
            float k = (direction.x + 1.0 - 1.0) / direction.y;// б��
            if (dir == 0 && k<1 && k>-1 && direction.x < 0) {// ����
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
    return nullptr;
}

// Player��ý���
void Player::GetBonus(Bonus bonus) {
    //���齱��
    current_exp += bonus.exp;
    //����
    while (current_exp >= next_level_exp) {
        current_exp -= next_level_exp;
        level++;
        next_level_exp *= (1 + level * 0.1);
    }

    //��Ʒ����
    //�ݴ�������Ʒ��װ��

}

// �жϽ�����Χ
bool Player::isTrigger(const Vec2& pos) {

    int dx = mySprite->getPosition().x - pos.x;
    int dy = mySprite->getPosition().y - pos.y;

    return std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2);

}
// �ı�is_moving
void Player::ChangeIsMoving() {
    if (is_moving == 1) {
        is_moving = 0;
    }
    else {
        is_moving = 1;
    }
}
