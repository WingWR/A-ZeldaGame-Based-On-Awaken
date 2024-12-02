
#ifndef __MapScene_H__
#define __MapScene_H__

#include "cocos2d.h"

USING_NS_CC;
class MapScene : public Scene {
public:
    static Scene* createScene() {
        return MapScene::create();
    }

    virtual bool init() override {
        // ���� TMX �ļ�
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();

  
        // ���� TMX �ļ�
        auto tileMap = TMXTiledMap::create("D:/cocos2d-x-4.0/project/Zelda/Resources/Maps/RebirthTemple/RebirthTemple.tmx");
        tileMap->setAnchorPoint(Vec2(0.5, 0.5));
        tileMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        tileMap->setRotation3D(Vec3(-30, 0, 0));
        tileMap->setScale(1.0f);

        // ����ͼ��ӵ�������
        this->addChild(tileMap);

        // ������������һЩ��������ã�������ӱ������֡�UI �ؼ���
        
        return true;
    }
    CREATE_FUNC(MapScene);
};
#endif // __MapScene_H__