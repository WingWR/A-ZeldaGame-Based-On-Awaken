#include "Creature.h"

/* �������� */
void Creature::Attack(int dir, Creature* opp) {
    // ����,ֱ�ӷ���
    if (isDead)
        return;

    /* Monster1:���� */
    if (role == "Monster1") {
        Vector<SpriteFrame*> animFrames;
        animFrames.reserve(8);
        for (int i = 17; i <= 24; i++) {
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
        mySprite->stopAllActions();                        //player����Creature���е�mySprite
        mySprite->runAction(animate);
        CCLOG("%s attack", role);
        // �������˶���
        if (opp != nullptr) {
            opp->Hurt();
        }
        // �˳�
        return;
    }

    /* ��ҽ�ɫ */
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

    /* ��ҽ�ɫ */
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
    if (isDead) {
        return;
    }

    /* ��ҽ�ɫ */
    std::string s = "Role/" + role + "atked/";
    // ���ݷ���ȷ�ϵ�һ��ͼƬ
    int start = 2;
    if (face_to == DOWN)
        start = 2;
    else if (face_to == LEFT)
        start = 4;
    else if (face_to == RIGHT)
        start = 6;
    else if (face_to == UP)
        start = 8;
    // ֡����
    Vector<SpriteFrame*> animFrames;
    animFrames.reserve(4);
    vector<int> idx;
    idx.push_back(start);
    idx.push_back(17 + start / 2);
    idx.push_back(17 + start / 2);
    idx.push_back(start);
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
void Creature::Move(int dir) {
    // ����,ֱ�ӷ���
    if (isDead) {
        return;
    }

    /* �����泯���� */
    face_to = dir;

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
    animFrames.reserve(5);
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
    auto moveAction = MoveBy::create(0.3f, moveBy);


    // ͬʱִ�ж������ƶ�
    auto moveAndAnimate = Spawn::create(animate, moveAction, nullptr);

    // ִ�ж���
    mySprite->stopAllActions();
    mySprite->runAction(moveAndAnimate);

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
    if (!isDead) {
        return;
    }
    isDead = false;
    face_to = DOWN;
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "atked/17.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y + 30));
}
// ����a��b���˺�
int Creature::DamageCal(Creature* a, Creature* b) {
    return a->getAtk() - b->getDef();
}
// �����hp
int Creature::getHp()const {
    return hp;
}
// �����hp
int Creature::getCurrentHp()const {
    return current_hp;
}
// �����mp
int Creature::getMp()const {
    return mp;
}
// �����mp
int Creature::getCurrentMp()const {
    return current_mp;
}
// ���atk
int Creature::getAtk()const {
    return atk;
}
// ���def
int Creature::getDef()const {
    return def;
}