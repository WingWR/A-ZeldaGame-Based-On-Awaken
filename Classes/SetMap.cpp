#include "SetMap.h"

USING_NS_CC;

Scene* SetMap::createScene() {
    return SetMap::create();
}

bool SetMap::init() {
    if (!Scene::init()) {
        return false;
    }

    /*���س�ʼ��ͼ*/
    auto InitialMap = TMXTiledMap::create("Maps/DeathDesert/DeathDesert.tmx");
    this->addChild(InitialMap);


    return true;
}