#include "CameraFollowScene.h"

Scene* CameraFollowScene::createScene() {
    return CameraFollowScene::create();
}

bool CameraFollowScene::init(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ���ص�ͼ
    TMXTiledMap* tileMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    Size mapSize = tileMap->getContentSize(); // ��ȡ��ͼ��С

    // ����ͼ��ӵ�������
    tileMap->setAnchorPoint(Vec2(0.5, 0.5));
    tileMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));  // ����ͼ������Ļ����
    this->addChild(tileMap);

    

    // ������Ҿ���
    Sprite* player = Sprite::create("pama.png");
    player->setScale(0.1);
    player->setAnchorPoint(Vec2(0.5, 0.5));
    player->setPosition(Vec2(600, 620));  // ������ҳ�ʼλ��
    this->addChild(player);

    
    // ��ȡĬ�������
    Camera* camera = getDefaultCamera();


    // ����������ĳ�ʼλ��
    float cameraZ = 300;
    Vec3 cameraPosition(player->getPosition().x, player->getPosition().y, cameraZ);
    camera->setPosition3D(cameraPosition);
    //camera->lookAt(Vec3(player->getPosition().x, player->getPosition().y, 0));

    // ע���������¼�
    auto listener = EventListenerMouse::create();
    listener->onMouseScroll = [=](EventMouse* event) {
        // ��ȡ���ֵĹ�������
        float scrollY = event->getScrollY();

        // ��ȡ��ǰ�������λ��
        Vec3 cameraPosition = camera->getPosition3D();

        // ���ݹ��ֵķ���ı��������Z��߶�
        // ���Ϲ�����Z��ֵ���ӣ��������ǰ
        // ���¹�����Z��ֵ���٣���������
        cameraPosition.z += scrollY * 10.0f;  // 10.0f�ǿ��ƹ��������ȵ�ϵ�������Ե���

        // ����������ĸ߶ȣ�Z�᷶Χ��
        cameraPosition.z = std::min(cameraPosition.z, 600.0f);  // ���߶�
        cameraPosition.z = std::max(cameraPosition.z, 200.0f);  // ��С�߶�

        // �����������λ��
        camera->setPosition3D(cameraPosition);
        
        CCLOG("Camera Position: %f, %f, %f", cameraPosition.x, cameraPosition.y, cameraPosition.z);
        };

    // ��ȡ�¼�����������Ӽ�����
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    // ��ÿһ֡����ʱ���������λ�ò������䷶Χ
    schedule([=](float dt) {
        // ��ȡ��ǰ�������λ��
            Vec3 cameraPosition = camera->getPosition3D();
        
        // �������λ�ø����������λ��
        camera->setPosition3D(Vec3(player->getPosition().x, player->getPosition().y, cameraPosition.z));
        }, "camera_update_key");
    return true;
}