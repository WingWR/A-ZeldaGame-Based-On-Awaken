#include "CameraFollowScene.h"

Scene* CameraFollowScene::createScene() {
    return CameraFollowScene::create();
}

bool CameraFollowScene::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 1. ���ص�ͼ
    TMXTiledMap* tileMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    Size mapSize = tileMap->getContentSize(); // ��ȡ��ͼ��С

    // 2. ����ͼ��ӵ�������
    tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    tileMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));  // ����ͼ������Ļ����
    this->addChild(tileMap);

    

    // 3. ������Ҿ���
    Sprite* player = Sprite::create("pama.png");
    player->setScale(0.1);
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPosition(Vec2(450, 620));  // ����ҷ�����Ļ����
    this->addChild(player);

    
    // 4. ��ȡĬ�������
    Camera* camera = getDefaultCamera();


    // 5. ����������ĳ�ʼλ��
    Vec3 cameraPosition(player->getPosition().x, player->getPosition().y, 200);
    camera->setPosition3D(cameraPosition);
    camera->lookAt(Vec3(player->getPosition().x, player->getPosition().y, 0));/**/

    
    
    // 6. ��ÿһ֡����ʱ���������λ�ò������䷶Χ���������
    /*schedule([=](float dt) {
        // ��ȡ��ҵĵ�ǰλ��
        Vec3 playerPos = player->getPosition3D();

        // �������������λ��
        float cameraX = std::min(std::max(playerPos.x, Director::getInstance()->getVisibleSize().width / 2),
            mapSize.width - Director::getInstance()->getVisibleSize().width / 2);
        float cameraY = std::min(std::max(playerPos.y, Director::getInstance()->getVisibleSize().height / 2),
            mapSize.height - Director::getInstance()->getVisibleSize().height / 2);

        // ���������λ��
        camera->setPosition3D(Vec3(cameraX, cameraY, cameraPosition.z));

       // �������ʼ�տ������
         camera->lookAt(Vec3(playerPos.x, playerPos.y, 0));
        }, "camera_update_key");*/
    return true;
}