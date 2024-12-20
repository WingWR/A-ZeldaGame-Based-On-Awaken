#include "Creature.h"

/******************************* 碰撞相关 *************************************/
/* 初始化精灵 */
void Creature::initSprite() {
    // 创建精灵
    mySprite = Sprite::create("Role/" + role + "/1.png");
    if (!mySprite) {
        CCLOG("Fail to create sprite.");
        return;
    }

    // 创建碰撞框
    std::unordered_map<std::string, Size> bodySizeMap = {
        {"Player1", Size(40, 70)},//
        {"Player2", Size(40, 60)},
        {"Player3", Size(40, 70)},
        {"Player4", Size(40, 70)},
        {"Player5", Size(40, 70)},
        {"npc0", Size(60, 60)},
        {"npc1", Size(40, 60)},
        {"npc2", Size(50, 80)},
        {"npc3", Size(50, 80)},
        {"npc4", Size(50, 80)},
        {"npc5", Size(50, 65)}, 
        {"npc6", Size(50, 65)},
        {"npc7", Size(50, 75)}
    };

    if (bodySizeMap.find(role) != bodySizeMap.end()) {
        collisionBoxSize = bodySizeMap[role];  // 根据角色设置碰撞框大小
        if (role == "Player1" || role == "Player2" || role == "Player3" || role == "Player4" || role == "Player5")
            collisionBoxOffset = Vec2(0, 30);
        else if(role == "npc1" || role == "npc7")
            collisionBoxOffset = Vec2(0, -30);
        else if (role == "npc2" || role == "npc3" || role == "npc4" || role == "npc5" || role == "npc6")
            collisionBoxOffset = Vec2(0, -20);
    }

    // 添加精灵至场景中   
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite, 0);
   
    // 碰撞框
#if DEBUG
    drawCollisionBox();
#else
#endif
}

/* 更改碰撞框 */
void Creature::editSizeOffset(Size size, Vec2 vec) {
    collisionBoxSize = size;
    collisionBoxOffset = vec;
    //drawCollisionBox();
}


/* 防止碰撞 */
void Creature::preventOverlap(Creature* creature1, Creature* creature2) {
    Rect rect1 = creature1->getCollisionRect();
    Rect rect2 = creature2->getCollisionRect();
    // 检测是否重叠
    if (rect1.intersectsRect(rect2)) {
        CCLOG("Collision detected.");
        Vec2 pos1 = creature1->mySprite->getPosition();
        Vec2 pos2 = creature2->mySprite->getPosition();
        Vec2 separation = pos1 - pos2;
        separation.normalize(); 
        // 每次分离的距离
        float separationDistance = 3.0f;
        // 调整creature1的位置
        creature1->mySprite->setPosition(pos1 + separation * separationDistance);
    }
}

/* 碰撞检测 */
bool Creature::isCollision(const Rect& rect1, const Rect& rect2) {
    bool result = rect1.intersectsRect(rect2);
    if (result)
        canMove = false;
    else
        canMove = true;
    return result;
}

/* 获取碰撞框 */
Rect Creature::getCollisionRect() const {
    // 获取精灵当前的位置和尺寸
    Vec2 spritePosition = mySprite->getPosition();
    Size spriteSize = collisionBoxSize;

    // 计算碰撞框的 Rect
    Rect collisionRect(
        spritePosition.x - spriteSize.width / 2 + collisionBoxOffset.x,
        spritePosition.y - spriteSize.height / 2 + collisionBoxOffset.y,
        spriteSize.width,
        spriteSize.height
    );

    return collisionRect;
}

/* 画碰撞框 */
void Creature::drawCollisionBox() {
    auto drawNode = DrawNode::create();
    Vec2 rectOrigin(
        -collisionBoxSize.width / 2 + collisionBoxOffset.x,
        -collisionBoxSize.height / 2 + collisionBoxOffset.y
    );
    Vec2 rectEnd(
        collisionBoxSize.width / 2 + collisionBoxOffset.x,
        collisionBoxSize.height / 2 + collisionBoxOffset.y
    );
    // 设置矩形框的颜色和线条宽度
    drawNode->drawRect(rectOrigin, rectEnd, Color4F(1.0, 0.0, 0.0, 1.0)); // 红色边框
    drawNode->setPosition(mySprite->getPosition());
    scene->addChild(drawNode, 1);
}


/******************************* 动画相关 *************************************/
//攻击动画

void Creature::Attack() {
    // 死了,直接返回
    if (isDead)
        return;

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
        
        return;
    }

    /* 玩家角色+Monster2+Monster3 */
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
   
    return;
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


/******************************* 属性相关 *************************************/
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

/* 设置属性 */
void Creature::setElementType(ElementType _elementType){
    elementType = _elementType;
}

/* 更改坐标 */
void Creature::ChangeXY(Vec2 change) {
    x += change.x;
    y += change.y;
}