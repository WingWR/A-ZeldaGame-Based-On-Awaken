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
    auto InitialMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
   

    auto LayerWall = InitialMap->getLayer("StructWall");
    auto LayerDecorations = InitialMap->getLayer("Decoration");
    LayerWall->setVisible(true);
    LayerDecorations->setVisible(true);

    addChild(InitialMap);

    return true;
}