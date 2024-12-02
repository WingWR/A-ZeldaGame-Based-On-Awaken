#include <iostream>
#include <string>
#include "Player.h"

/* ��ʾ��� */
void Player::showPlayer(std::string who, Scene* scene, float scale, int x, int y) {
    std::string str;
    str = "Role/Player/" + who + "/" + who + ".png";
    auto mySprite = Sprite::create(str);
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);
    scene->addChild(mySprite);
}

/* �������� */
void Player::PlayerAttack(std::string who, Scene* scene, int idx, float scale, int x, int y) {
    // ͼƬ��ǰ׺:����Ų���
    std::string s;
    if (idx == 1 || idx == 2)
        s = "Role/Player/" + who + "/attack" + std::to_string(idx) + "/" + who + "_atk" + std::to_string(idx) + "_";
    else if (idx == 3)
        s = "Role/Player/" + who + "/attack_final/" + who + "_final_";

    // �����ʼ��
    auto mySprite = Sprite::create(s + "0.png");
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);

    // ֡��
    int count = 0;  
    if (who == "Arthur") {
        if (idx == 1) 
            count = 10;   
        else if (idx == 2) 
            count = 12;
        else if (idx == 3) 
            count = 15;
    }
    else if (who == "Longbow") {
        if (idx == 1)
            count = 7;
        else if (idx == 2)
            count = 12;
        else if (idx == 3)
            count = 18;
    }
    Vector<SpriteFrame*> animFrames;
   
    // ģ�⶯��
    animFrames.reserve(count);
    for (int i = 1; i <= count; i++) {
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

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    Animate* animate = Animate::create(animation);
    // mySprite->runAction(RepeatForever::create(animate));
    mySprite->runAction(animate);  // ����һ��
    scene->addChild(mySprite);
}

/* ��·���� */
void Player::PlayerMove(std::string who, Scene* scene, float scale, int x, int y, int direction) {
    // ͼƬ��ǰ׺
    std::string s = "Role/Player/" + who + "/move/" + who + "_move_";

    // �����ʼ��
    auto mySprite = Sprite::create(s + "0.png");
    mySprite->setPosition(Vec2(x, y));
    mySprite->setScale(scale);


}