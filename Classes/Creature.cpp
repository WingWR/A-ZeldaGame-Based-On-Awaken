#include "Creature.h"

/* 初始化精灵 */
void Creature::initSprite() {
    // 精灵初始化
    /*mySprite = Sprite::create("Role/" + role + "/1.png");
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite);*/

    // 创建精灵
    mySprite = Sprite::create("Role/" + role + "/1.png");
    if (!mySprite) {
        CCLOG("Fail to create sprite.");
        return;
    }
    // 创建碰撞框
    PhysicsMaterial material;
    material.restitution = 0.0f;
    PhysicsBody* body = PhysicsBody::createBox(Size(0, 0), material); // 默认
    // 各人物碰撞框数值
    std::unordered_map<std::string, int> bodyMap = {
    {"Player1", 1},
    {"Player2", 2},
    {"Player3", 3},
    {"Player4", 4},
    {"Player5", 5},
    {"npc0", 14},
    {"npc1", 11},
    {"npc2", 12},
    {"npc3", 13},
    {"npc4", 14},
    {"npc5", 15},
    {"npc6", 16},
    {"npc7", 17}
    };

    switch (bodyMap[role]) {
    /***************** Player *****************/
    case(1):
    case(2):
    case(4):
        body = PhysicsBody::createBox(Size(80, 130), material);
        body->setPositionOffset(Vec2(0, -10));
        break;
    case(3):
    case(5):
        body = PhysicsBody::createBox(Size(80, 100), material);
        body->setPositionOffset(Vec2(0, -20));
        break;
    /****************** npc ******************/
    case(11):
        body = PhysicsBody::createBox(Size(60, 60), material);
        body->setPositionOffset(Vec2(0, -40));
        break;
    case(12):
    case(13):
    case(14):
    case(17):
        body = PhysicsBody::createBox(Size(80, 115), material);
        body->setPositionOffset(Vec2(0, -15));
        break;
    case(15):
    case(16):
        body = PhysicsBody::createBox(Size(80, 110), material);
        body->setPositionOffset(Vec2(0, -30));
        break;
        /************** Monster **************/

    default:
        break;
    }

    // 禁用旋转
    body->setRotationEnable(false);  
    // npc设为静止
    body->setDynamic(true);
    if (role == "npc0" || role == "npc1" || role == "npc2" || role == "npc3" || role == "npc4" || role == "npc5" || role == "npc6") {
        body->setDynamic(false);
    }
    // 将碰撞框添加到精灵身上
    if (body) {
        mySprite->setPhysicsBody(body);
    }
    // 添加精灵至场景中   
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite,0);
}

/* 攻击动画 */
Animate* Creature::Attack(int dir, Creature* opp) {
    // 死了,直接返回
    if (isDead)
        return nullptr;

    /* Monster1:树妖 */
    if (role == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(8);
        for (int i = 17; i <= 24; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + role + "/" + std::to_string(i) + ".png");
            float width = float(texture->getPixelsWide());
            float height = float(texture->getPixelsHigh());
            Rect rectInPixels(0, 0, width, height);
            auto spriteFrame = SpriteFrame::createWithTexture(
                texture,
                CC_RECT_PIXELS_TO_POINTS(rectInPixels)
            );
            animFrames.pushBack(spriteFrame);
        }
        // 播放
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Animate* animate = Animate::create(animation);
        mySprite->stopAllActions();    
        mySprite->runAction(animate);
        CCLOG("%s attack", role);
        // 对手受伤动画
        if (opp != nullptr) {
            opp->Hurt();
        }
        // 退出
        return animate;
    }

    /* 玩家角色+Monster2+Monster3 */
    // 更改面朝方向
    face_to = dir;
    // 图片名前缀:除编号部分
    std::string s = "Role/" + role + "atk/";
    // 根据方向确认第一张图片 
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;
    // 帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(9);
    for (int j = 0; j < 2; j++) {
        for (int i = start; i < start + 4; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(i) + ".png");
            float width = texture->getPixelsWide();
            float height = texture->getPixelsHigh();
            Rect rectInPixels(0, 0, width, height);
            auto spriteFrame = SpriteFrame::createWithTexture(
                texture,
                CC_RECT_PIXELS_TO_POINTS(rectInPixels)
            );
            animFrames.pushBack(spriteFrame);
        }
    }
    auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + role + "/" + std::to_string(start) + ".png");
    float width = texture->getPixelsWide();
    float height = texture->getPixelsHigh();
    Rect rectInPixels(0, 0, width, height);
    auto spriteFrame = SpriteFrame::createWithTexture(
        texture,
        CC_RECT_PIXELS_TO_POINTS(rectInPixels)
    );
    animFrames.pushBack(spriteFrame);
    // 播放
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    mySprite->stopAllActions();
    mySprite->runAction(animate);
    CCLOG("%s attack", role);
    // 对手受伤动画
    if (opp != nullptr) {
        opp->Hurt();
    }
    return animate;
}

/* 受伤动画 */
void Creature::Hurt() {
    // 死了,直接返回
    if (isDead) {
        return;
    }

    /* Monster1:树妖 */
    if (role == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(4);
        for (int i = 13; i <= 16; i++) {
            auto texture = Director::getInstance()->getTextureCache()->addImage("Role/" + role + "/" + std::to_string(i) + ".png");
            float width = texture->getPixelsWide();
            float height = texture->getPixelsHigh();
            Rect rectInPixels(0, 0, width, height);
            auto spriteFrame = SpriteFrame::createWithTexture(
                texture,
                CC_RECT_PIXELS_TO_POINTS(rectInPixels)
            );
            animFrames.pushBack(spriteFrame);
        }
        // 播放
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Animate* animate = Animate::create(animation);
        mySprite->stopAllActions();
        mySprite->runAction(animate);
        CCLOG("%s hurt", role);
        return;
    }

    /* 玩家角色+Monster2+Monster3 */
    std::string s = "Role/" + role + "atked/";
    // 根据方向确认第一张图片
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;
    // 帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    for (int i = start; i < start + 4; i++) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(i) + ".png");
        float width = texture->getPixelsWide();
        float height = texture->getPixelsHigh();
        Rect rectInPixels(0, 0, width, height);
        auto spriteFrame = SpriteFrame::createWithTexture(
            texture,
            CC_RECT_PIXELS_TO_POINTS(rectInPixels)
        );
        animFrames.pushBack(spriteFrame);
    }
    // 播放
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    Animate* animate = Animate::create(animation);
    mySprite->stopAllActions();
    mySprite->runAction(animate);

    CCLOG("%s hurt", role);
}

/* 恢复动画 */
void Creature::Heal() {
    // 死了,直接返回
    if (isDead) 
        return;
    // 不是玩家,直接返回
    if ((role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    /* 玩家角色 */
    std::string s = "Role/" + role + "atked/";
    // 根据方向确认第一张图片
    int start = 0;
    if (face_to == DOWN)
        start = 0;
    else if (face_to == LEFT)
        start = 1;
    else if (face_to == RIGHT)
        start = 2;
    else if (face_to == UP)
        start = 3;
    // 帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    std::vector<int> idx;
    idx.push_back(start * 4 + 2);
    idx.push_back(18 + start);
    idx.push_back(18 + start);
    idx.push_back(start * 4 + 2);
    for (int i = 0; i < 4; i++) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(idx[i]) + ".png");
        float width = texture->getPixelsWide();
        float height = texture->getPixelsHigh();
        Rect rectInPixels(0, 0, width, height);
        auto spriteFrame = SpriteFrame::createWithTexture(
            texture,
            CC_RECT_PIXELS_TO_POINTS(rectInPixels)
        );
        animFrames.pushBack(spriteFrame);
    }
    // 播放
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    mySprite->stopAllActions();
    mySprite->runAction(animate);

    CCLOG("%s heal", role);
}

/* 走路动画 */
Animate* Creature::Move(int dir) {
    // 死了,直接返回
    if (isDead) {
        return nullptr;
    }

    if (role == "Monster1")
        return nullptr;

    /* 更改面朝方向 */
    face_to = dir;
    log("face_to:%d", face_to);
    /* 图片名前缀:除编号部分 */
    std::string s = "Role/" + role + "/";

    /* 根据方向确认第一张图片及移动路径 */
    Vec2 moveBy;
    int start = 1;
    if (face_to == DOWN) {
        start = 1;



    }
    else if (face_to == LEFT) {
        start = 5;

    }

    else if (face_to == RIGHT) {
        start = 9;

    }

    else if (face_to == UP) {
        start = 13;


    }


    // 创建帧动画
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    for (int i = start + 1; i < start + 4; i++) {
        auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(i) + ".png");
        float width = texture->getPixelsWide();
        float height = texture->getPixelsHigh();
        Rect rectInPixels(0, 0, width, height);
        auto spriteFrame = SpriteFrame::createWithTexture(
            texture,
            CC_RECT_PIXELS_TO_POINTS(rectInPixels)
        );
        animFrames.pushBack(spriteFrame);
    }
    auto texture = Director::getInstance()->getTextureCache()->addImage(s + std::to_string(start) + ".png");
    float width = texture->getPixelsWide();
    float height = texture->getPixelsHigh();
    Rect rectInPixels(0, 0, width, height);
    auto spriteFrame = SpriteFrame::createWithTexture(
        texture,
        CC_RECT_PIXELS_TO_POINTS(rectInPixels)
    );
    animFrames.pushBack(spriteFrame);

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);

    // 创建移动动作
   // auto moveAction = MoveBy::create(0.8f, moveBy);
   //log("MoveBy:%f%f", moveBy.x, moveBy.y);
    // 同时执行动画和移动
    //auto moveAndAnimate = Spawn::createWithTwoActions(animate, moveAction);

    // 执行动作


    mySprite->runAction(animate);
    log("Move");
    return animate;

}

/* 死亡 */
void Creature::Die() {
    // 已经死了,直接返回
    if (isDead) {
        return;
    }

    isDead = true;
    face_to = DOWN;
    /* Monster1:树妖 */
    if (role == "Monster1") {
        mySprite->stopAllActions();
        mySprite->setTexture("Role/" + role + "/25.png");
        return;
    }
    /* 玩家角色 */
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y - 30));
}

/* 复活 */
void Creature::Revive() {
    // 还没死或者不是玩家
    if (!isDead || (role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    isDead = false;
    face_to = DOWN;
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y + 30));
}

/* 等级加成 */
void Creature::levelBonus() {
    speed = speed * (0.05 * level + 1);
    hp = hp * (0.05 * level + 1);
    mp = mp * (0.05 * level + 1);
    atk = atk * (0.05 * level + 1);
    def = def * (0.05 * level + 1);
}

/* 返回a对b的伤害 */
int Creature::DamageCal(Creature* a, Creature* b) {
    return a->getAtk() - b->getDef();
}
// 设置属性
void Creature::setElementType(ElementType _elementType)
{
    elementType = _elementType;
}
void Creature::ChangeXY(Vec2 change) {
    x += change.x;
    y += change.y;
}