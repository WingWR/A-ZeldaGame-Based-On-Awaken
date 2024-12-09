#include "SetMap.h"
#include "Player.h"
#include "SetPlayerScene.h"

USING_NS_CC;

Scene* SetMap::createScene() {
    return SetMap::create();
}

bool SetMap::init() {
    if (!Scene::init()) {
        return false;
    }

    PlayerInWhichMap = 0;     //��ʼ�����λ���ڳ�ʼ����

    //���������С��ͼ����ͼ����
    MicroMap = MicroMap::create();
    MicroMap->setVisible(false);    //��ʼ����С��ͼ
    MicroMap->setScale(1.0f);    //����С��ͼ���ű���
    this->addChild(MicroMap, 100);     //���С��ͼ������,С��ͼ��ͼ�����ȼ����

    IsMicroMapVisible = false;    //��ʼ��С��ͼ״̬����

    //��Ӽ��̼�����������M��С��ͼ
    auto KeyListener = EventListenerKeyboard::create();
    KeyListener->onKeyPressed = CC_CALLBACK_2(SetMap::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(KeyListener, this);

    // ���� TMX �ļ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*���س�ʼ��ͼ*/
    auto InitialMap = TMXTiledMap::create("Maps/RebirthTemple/RebirthTemple.tmx");
    InitialMap->setAnchorPoint(Vec2(0.5, 0.5));
    InitialMap->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    InitialMap->setScale(1.0f);

    //��ӳ�ʼ��ͼ������
    this->addChild(InitialMap);

    ///////////////////////
    // lq�ӵĵ���С��
    
    PLAYER = new Player("Player"+std::to_string(SetPlayerScene::who+1), this, visibleSize.width / 2, visibleSize.height / 2, 1.0f, 100, 50, 20, 50, 10, 50, 1);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(SetMap::KeyPressed, this); 
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    // �Ӹ�npc
    npc1 = new Player("npc1", this, 600, 300, 1.0f, 0, 0, 0, 0, 0, 50, 0);
    //�Ӹ�����
    Monster1 = new Player("Monster1", this, 1000, 600, 1.0f, 0, 0, 0, 100, 0, 50, 0);
    //�Ӹ��粼��
    Monster2 = new Player("Monster2", this, 1500, 800, 3.0f, 0, 0, 0, 100, 0, 50, 0);
    ///////////////////////


    return true;
}



void SetMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_M) {
        // �л�С��ͼ��ʾ״̬
        IsMicroMapVisible = !IsMicroMapVisible;

        /*�˴��л�С��ͼ��ʾ������С��ͼʱ�������س�ʼ��ͼ���˳�С��ͼ֮������ʾ��ʼ��ͼ
          ������ڽ���С��ͼ֮ǰ����ͣ��Ϸ���˳�С��ͼ֮���ٻָ���Ϸ����ֹ����ڴ򿪵�ͼ��ʱ��������*/
        if (IsMicroMapVisible) {
            //����С��ͼ��ͣ��Ϸ
            Director::getInstance()->pause();
            MicroMap->setVisible(IsMicroMapVisible);    //�л���ʾС��ͼ
        }   
        else {
			MicroMap->setVisible(IsMicroMapVisible);    //�л���ʾС��ͼ
			Director::getInstance()->resume();    //�˳�С��ͼ�ָ���Ϸ
		}
    }
}