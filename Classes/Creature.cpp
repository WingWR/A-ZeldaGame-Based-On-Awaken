#include "Creature.h"

/* ��ʼ������ */
void Creature::initSprite() {
    // �����ʼ��
    /*mySprite = Sprite::create("Role/" + role + "/1.png");
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite);*/

    // ��������
    mySprite = Sprite::create("Role/" + role + "/1.png");
    if (!mySprite) {
        CCLOG("Fail to create sprite.");
        return;
    }
    // ������ײ��
    PhysicsMaterial material;
    material.restitution = 0.0f;
    PhysicsBody* body = PhysicsBody::createBox(Size(0, 0), material); // Ĭ��
    // ��������ײ����ֵ
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

    // ������ת
    body->setRotationEnable(false);  
    // npc��Ϊ��ֹ
    body->setDynamic(true);
    if (role == "npc0" || role == "npc1" || role == "npc2" || role == "npc3" || role == "npc4" || role == "npc5" || role == "npc6") {
        body->setDynamic(false);
    }
    // ����ײ����ӵ���������
    if (body) {
        mySprite->setPhysicsBody(body);
    }
    // ��Ӿ�����������   
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite,0);
}

/* �������� */
Animate* Creature::Attack(int dir, Creature* opp) {
    // ����,ֱ�ӷ���
    if (isDead)
        return nullptr;

    /* Monster1:���� */
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
        // ����
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Animate* animate = Animate::create(animation);
        mySprite->stopAllActions();    
        mySprite->runAction(animate);
        CCLOG("%s attack", role);
        // �������˶���
        if (opp != nullptr) {
            opp->Hurt();
        }
        // �˳�
        return animate;
    }

    /* ��ҽ�ɫ+Monster2+Monster3 */
    // �����泯����
    face_to = dir;
    // ͼƬ��ǰ׺:����Ų���
    std::string s = "Role/" + role + "atk/";
    // ���ݷ���ȷ�ϵ�һ��ͼƬ 
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;
    // ֡����
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
    // ����
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    mySprite->stopAllActions();
    mySprite->runAction(animate);
    CCLOG("%s attack", role);
    // �������˶���
    if (opp != nullptr) {
        opp->Hurt();
    }
    return animate;
}

/* ���˶��� */
void Creature::Hurt() {
    // ����,ֱ�ӷ���
    if (isDead) {
        return;
    }

    /* Monster1:���� */
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
        // ����
        Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
        Animate* animate = Animate::create(animation);
        mySprite->stopAllActions();
        mySprite->runAction(animate);
        CCLOG("%s hurt", role);
        return;
    }

    /* ��ҽ�ɫ+Monster2+Monster3 */
    std::string s = "Role/" + role + "atked/";
    // ���ݷ���ȷ�ϵ�һ��ͼƬ
    int start = 1;
    if (face_to == DOWN)
        start = 1;
    else if (face_to == LEFT)
        start = 5;
    else if (face_to == RIGHT)
        start = 9;
    else if (face_to == UP)
        start = 13;
    // ֡����
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
    // ����
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    Animate* animate = Animate::create(animation);
    mySprite->stopAllActions();
    mySprite->runAction(animate);

    CCLOG("%s hurt", role);
}

/* �ָ����� */
void Creature::Heal() {
    // ����,ֱ�ӷ���
    if (isDead) 
        return;
    // �������,ֱ�ӷ���
    if ((role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    /* ��ҽ�ɫ */
    std::string s = "Role/" + role + "atked/";
    // ���ݷ���ȷ�ϵ�һ��ͼƬ
    int start = 0;
    if (face_to == DOWN)
        start = 0;
    else if (face_to == LEFT)
        start = 1;
    else if (face_to == RIGHT)
        start = 2;
    else if (face_to == UP)
        start = 3;
    // ֡����
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
    // ����
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    mySprite->stopAllActions();
    mySprite->runAction(animate);

    CCLOG("%s heal", role);
}

/* ��·���� */
Animate* Creature::Move(int dir) {
    // ����,ֱ�ӷ���
    if (isDead) {
        return nullptr;
    }

    if (role == "Monster1")
        return nullptr;

    /* �����泯���� */
    face_to = dir;
    log("face_to:%d", face_to);
    /* ͼƬ��ǰ׺:����Ų��� */
    std::string s = "Role/" + role + "/";

    /* ���ݷ���ȷ�ϵ�һ��ͼƬ���ƶ�·�� */
    Vec2 moveBy;
    int start = 1;
    if (face_to == DOWN) {
        start = 1;
        moveBy = Vec2(0, -speed);
    }
    else if (face_to == LEFT) {
        start = 5;
        moveBy = Vec2(-speed, 0);
    }
    else if (face_to == RIGHT) {
        start = 9;
        moveBy = Vec2(speed, 0);
    }
    else if (face_to == UP) {
        start = 13;
        moveBy = Vec2(0, speed);
    }

    // ����֡����
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    for (int i = start+1; i < start + 4; i++) {
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

    // �����ƶ�����
    auto moveAction = MoveBy::create(0.8f, moveBy);
    log("MoveBy:%f%f", moveBy.x, moveBy.y);
    // ͬʱִ�ж������ƶ�
    auto moveAndAnimate = Spawn::createWithTwoActions(animate, moveAction);

    // ִ�ж���
    mySprite->stopAllActions();
    
    mySprite->runAction(moveAndAnimate);
    log("Move");
    return animate;
   
}

/* ���� */
void Creature::Die() {
    // �Ѿ�����,ֱ�ӷ���
    if (isDead) {
        return;
    }

    isDead = true;
    face_to = DOWN;
    /* Monster1:���� */
    if (role == "Monster1") {
        mySprite->stopAllActions();
        mySprite->setTexture("Role/" + role + "/25.png");
        return;
    }
    /* ��ҽ�ɫ */
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y - 30));
}

/* ���� */
void Creature::Revive() {
    // ��û�����߲������
    if (!isDead || (role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    isDead = false;
    face_to = DOWN;
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y + 30));
}

/* �ȼ��ӳ� */
void Creature::levelBonus() {
    speed = speed * (0.05 * level + 1);
    hp = hp * (0.05 * level + 1);
    mp = mp * (0.05 * level + 1);
    atk = atk * (0.05 * level + 1);
    def = def * (0.05 * level + 1);
}

/* ����a��b���˺� */
int Creature::DamageCal(Creature* a, Creature* b) {
    return a->getAtk() - b->getDef();
}
// ��������
void Creature::setElementType(ElementType _elementType)
{
    elementType = _elementType;
}