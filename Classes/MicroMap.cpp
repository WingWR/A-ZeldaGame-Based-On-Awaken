#include "MicroMap.h"

USING_NS_CC;

bool MicroMap::init() {
	if (!Layer::init()) {
		return false;
	}

	OnEnterMicroMap();     //��ʼ�����ͼ

	return true;
}

void MicroMap::OnEnterMicroMap() {
	// ��ȡ��Ļ�ߴ�
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//��ȡ��ǰ���ͼ�ߴ�
	Size MapSize = getContentSize();

	//�������ͼ����
	auto WorldMap = Sprite::create("Maps/MicroMap/WorldMap.png");

	//���ô��ͼ�����λ�úʹ�С
	WorldMap->setPosition(visibleSize / 2);
	WorldMap->setScale(3.0f);

	//��Ӵ��ͼ���鵽��
	this->addChild(WorldMap);

	//��ʼ�������������
	MapReign.push_back({ 0,MapSize.height / 2 ,MapSize.width / 2,MapSize.height / 2 });    //��ʼ����ɽ����
	MapReign.push_back({ 0,MapSize.height,MapSize.width / 2,MapSize.height / 2 });    //��ʼ��ɭ�ֺ���
	MapReign.push_back({ MapSize.width / 2,MapSize.height / 2,MapSize.width / 2,MapSize.height / 2 });    //��ʼ��ѩ�غ���
	MapReign.push_back({ MapSize.width / 2,MapSize.height,MapSize.width / 2,MapSize.height / 2 });    //��ʼ��ɳĮ����

	//��ʼ������������
	ReignName.push_back("ɭ������");
	ReignName.push_back("��ɽ����");
	ReignName.push_back("ɳĮ����");
	ReignName.push_back("ѩ������");

	// Ϊÿ���������ռ�,��������δ����ռ�ᷢ������Խ��
	BlackFogLayer.resize(MapReign.size()); 

	for (unsigned int i = 0; i < MapReign.size(); ++i) {
		//���������
		BlackFogLayer[i] = cocos2d::DrawNode::create();
		
		//����ÿ������ľ������Ͻ�
		cocos2d::Vec2 destination;
		destination.x = MapReign[i].origin.x + MapReign[i].size.width;
		destination.y = MapReign[i].origin.y - MapReign[i].size.height;

		//����ÿ���������
		BlackFogLayer[i]->drawSolidRect(MapReign[i].origin, destination, Color4F::BLACK);    //���ú������ɫΪ��ɫ,͸����Ϊ0
		BlackFogLayer[i]->drawRect(MapReign[i].origin, destination, Color4F::WHITE);    //���ð�ɫ�߿�
		IsBlackFogVisited.push_back(false);    //��ʼ������Ϊδ��̽����״̬

		this->addChild(BlackFogLayer[i]);    //��Ӻ�����
	}
}

void MicroMap::DisperseBlackFog(int ReignIndex) {
	//��ɢ����
	BlackFogLayer[ReignIndex]->setVisible(false);

    //���ú���Ϊ��̽����״̬
	IsBlackFogVisited[ReignIndex] = true;
}

void MicroMap::UnlockReign(int ReignIndex) {
	// ���ú���Ϊ��̽����״̬
	IsBlackFogVisited[ReignIndex] = true;

	// ��ɢ̽��ͼ�����
	DisperseBlackFog(ReignIndex);
}

void MicroMap::update(float dt) {
	// ��ʼ�� Label ��ʾ��������
	Label* RegionLabel = Label::createWithTTF("", "fonts/arial.ttf", 24);
	RegionLabel->setVisible(false);  // ��ʼʱ���ɼ�
	this->addChild(RegionLabel, 10);  // ��ӵ�����

	// ע������¼�������
	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseMove = [this, RegionLabel](Event* event) {
		EventMouse* e = static_cast<EventMouse*>(event);
		Vec2 mousePos = e->getLocationInView();  // ��ȡ���λ��

		// ת�����굽��Ļ����ϵ
		mousePos.y = Director::getInstance()->getVisibleSize().height - mousePos.y;

		bool InFogLayer = false;    // �Ƿ��ں������
		for (unsigned int i = 0; i < MapReign.size(); ++i) {
			// �ж�����Ƿ���ĳ��������
			if (MapReign[i].containsPoint(mousePos)) {
				RegionLabel->setString(ReignName[i]);    // ������������
				RegionLabel->setVisible(true);    // ��ʾ��������
				RegionLabel->setPosition(mousePos.x, mousePos.y);    // ����λ��

				InFogLayer = true;    // ��������
				break;
			}
		}

		if (!InFogLayer) {
			RegionLabel->setVisible(false);    // ������������
		}
		};
}