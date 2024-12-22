#include "Creature.h"

/******************************* ��ײ��� *************************************/
/* ��ʼ������ */
void Creature::initSprite() {
    // ��������
    mySprite = Sprite::create("Role/" + role + "/1.png");
    if (!mySprite) {
        return;
    }

    // ������ײ��
    std::unordered_map<std::string, Size> bodySizeMap = {
        {"Player1", Size(40, 70)},
        {"Player2", Size(40, 60)},
        {"Player3", Size(40, 50)},
        {"Player4", Size(40, 70)},
        {"Player5", Size(40, 70)},
        {"npc0", Size(60, 60)},
        {"npc1", Size(40, 60)},
        {"npc2", Size(50, 80)},
        {"npc3", Size(50, 80)},
        {"npc4", Size(50, 80)},
        {"npc5", Size(50, 65)},
        {"npc6", Size(50, 65)},
        {"npc7", Size(50, 75)},
        {"npc8", Size(50, 80)},
        {"npc9", Size(50, 80)},
        {"npc10", Size(50, 80)}
        /*,
        {"Monster1", Size(90, 80)},
        {"Monster2", Size(90, 80)},
        {"Monster3", Size(90, 80)},
        {"Monster4", Size(50, 80)},
        {"Monster5", Size(50, 65)},
        {"Monster6", Size(50, 65)},
        {"Monster7", Size(50, 75)}*/
    };

    if (bodySizeMap.find(role) != bodySizeMap.end()) {
        collisionBoxSize = bodySizeMap[role];  // ���ݽ�ɫ������ײ���С
        if (role == "Player1" || role == "Player2" || role == "Player3" || role == "Player4" || role == "Player5")
            collisionBoxOffset = Vec2(0, -20);
        else if (role == "npc1" || role == "npc7")
            collisionBoxOffset = Vec2(0, -30);
        else if (role == "npc2" || role == "npc3" || role == "npc4" || role == "npc5" || role == "npc6" || role == "npc8" || role == "npc9" || role == "npc10")
            collisionBoxOffset = Vec2(0, -20);
    }

    // ��Ӿ�����������   
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite, 0);

    // ��ײ��
    // drawCollisionBox();
}

/* ������ײ�� */
void Creature::editSizeOffset(Size size, Vec2 vec) {
    collisionBoxSize = size;
    collisionBoxOffset = vec;
    //drawCollisionBox();
}


/* ��ֹ��ײ */
void Creature::preventOverlap(Creature* creature1, Creature* creature2) {
    Rect rect1 = creature1->getCollisionRect();
    Rect rect2 = creature2->getCollisionRect();
    // ����Ƿ��ص�
    if (rect1.intersectsRect(rect2)) {
        Vec2 pos1 = creature1->mySprite->getPosition();
        Vec2 pos2 = creature2->mySprite->getPosition();
        Vec2 separation = pos1 - pos2;
        separation.normalize(); 
        // ÿ�η���ľ���
        float separationDistance = 3.0f;
        // ����creature1��λ��
        creature1->mySprite->setPosition(pos1 + separation * separationDistance);
    }
}

/* ��ײ��� */
bool Creature::isCollision(const Rect& rect1, const Rect& rect2) {
    bool result = rect1.intersectsRect(rect2);
    if (result)
        canMove = false;
    else
        canMove = true;
    return result;
}

/* ��ȡ��ײ�� */
Rect Creature::getCollisionRect() const {
    // ��ȡ���鵱ǰ��λ�úͳߴ�
    Vec2 spritePosition = mySprite->getPosition();
    Size spriteSize = collisionBoxSize;

    // ������ײ��� Rect
    Rect collisionRect(
        spritePosition.x - spriteSize.width / 2 + collisionBoxOffset.x,
        spritePosition.y - spriteSize.height / 2 + collisionBoxOffset.y,
        spriteSize.width,
        spriteSize.height
    );

    return collisionRect;
}

/* ����ײ�� */
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
    // ���þ��ο����ɫ���������
    drawNode->drawRect(rectOrigin, rectEnd, Color4F(1.0, 0.0, 0.0, 1.0)); // ��ɫ�߿�
    drawNode->setPosition(mySprite->getPosition());
    scene->addChild(drawNode, 1);
}


/******************************* ������� *************************************/
//��������

void Creature::Attack() {
    // ����,ֱ�ӷ���
    if (isDead)
        return;

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
        
        return;
    }

    /* ��ҽ�ɫ+Monster2+Monster3 */
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
   
    return;
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

}

/* �ָ����� */
void Creature::Heal() {
    static int nums = 0;
    if (nums < 60) {
        return;
    }
    else {
        nums = 0;
        current_hp += (hp + 1.0 - 1.0) / 50;
    }
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

}

/* ��·���� */
void  Creature::Move(int dir) {
    // ����,ֱ�ӷ���
    if (isDead) {
        return ;
    }

    if (role == "Monster1")
        return ;

    /* �����泯���� */
    face_to = dir;
    /* ͼƬ��ǰ׺:����Ų��� */
    std::string s = "Role/" + role + "/";

    /* ���ݷ���ȷ�ϵ�һ��ͼƬ���ƶ�·�� */
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


    // ����֡����
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

    // ִ�ж���
    mySprite->runAction(animate);
    return ;
}

void Creature::learnMove(int dir) {
    // ����,ֱ�ӷ���
    if (isDead)
        return;
    if (role == "Monster1")
        return;

    /* �����泯���� */
    face_to = dir;

    /* ͼƬ��ǰ׺:����Ų��� */
    std::string s = "Role/" + role + "/";

    /* ���ݷ���ȷ�ϵ�һ��ͼƬ���ƶ�·�� */
    speed = 50;
    Vec2 moveBy;
    int start = 1;
    if (face_to == DOWN) {
        moveBy = Vec2(0, -speed);
        start = 1;
    }
    else if (face_to == LEFT) {
        moveBy = Vec2(-speed, 0);
        start = 5;
    }
    else if (face_to == RIGHT) {
        moveBy = Vec2(speed, 0);
        start = 9;
    }
    else if (face_to == UP) {
        start = 13;
        moveBy = Vec2(0, speed);
    }

    // ����֡����
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

    auto moveAction = MoveBy::create(0.8f, moveBy);
    auto moveAndAnimate = Spawn::createWithTwoActions(animate, moveAction);

    // ִ�ж���
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
    // ��û�����߲������
    if (!isDead || (role != "Player1" && role != "Player2" && role != "Player3" && role != "Player4" && role != "Player5"))
        return;

    isDead = false;
    face_to = DOWN;
    mySprite->stopAllActions();
    mySprite->setTexture("Role/" + role + "/1.png");
    mySprite->setPosition(Vec2(mySprite->getPosition().x, mySprite->getPosition().y + 30));
}


/******************************* ������� *************************************/
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

/* �������� */
void Creature::setElementType(ElementType _elementType){
    elementType = _elementType;
}

/* �������� */
void Creature::ChangeXY(Vec2 change) {
    x += change.x;
    y += change.y;
}