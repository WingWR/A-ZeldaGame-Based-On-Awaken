#include "MicroMap.h"

USING_NS_CC;

bool MicroMap::init() {
	if (!Layer::init()) {
		return false;
	}

	this->OnEnterMicroMap();     //��ʼ�����ͼ

	RegionLabel = Label::createWithTTF("", "fonts/arial.ttf", 48);
	RegionLabel->setTextColor(cocos2d::Color4B::WHITE);
	this->addChild(RegionLabel);

	// ע������¼�������
	if(this->isVisible()){
	auto MouseListener = EventListenerMouse::create();
	MouseListener->onMouseMove = CC_CALLBACK_1(MicroMap::OnMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(MouseListener, this);
	}
	return true;  
}

void MicroMap::OnEnterMicroMap() {
	// ��ȡ��Ļ�ߴ�
	visibleSize = Director::getInstance()->getVisibleSize();
	
	//�������ͼ����
	auto WorldMap = Sprite::create("Maps/MicroMap/WorldMap.png");

	//���ô��ͼ�����λ�úʹ�С
	WorldMap->setPosition(visibleSize / 2);
	WorldMap->setScale(3.0f);

	//��Ӵ��ͼ���鵽��
	this->addChild(WorldMap);

	//��ʼ�������������
	//�˴������ϸ��յ�ͼ������˳���ʼ����������������Ĵ���
	MapReign.push_back({ 0,visibleSize.height,visibleSize.width / 2,visibleSize.height / 2 });    //��ʼ��ɭ�ֺ���
	MapReign.push_back({ 0,visibleSize.height / 2 ,visibleSize.width / 2,visibleSize.height / 2 });    //��ʼ����ɽ����
	MapReign.push_back({ visibleSize.width / 2,visibleSize.height,visibleSize.width / 2,visibleSize.height / 2 });    //��ʼ��ɳĮ����
	MapReign.push_back({ visibleSize.width / 2,visibleSize.height / 2,visibleSize.width / 2,visibleSize.height / 2 });    //��ʼ��ѩ�غ���

	MapReign.push_back({ visibleSize.width / 2,visibleSize.height / 2,visibleSize.height / 4,0 });    //��ʼ����ʼ�����������ǰ������¼����Բ������


	//��ʼ������������
	ReignName.push_back("ForestArea");
	ReignName.push_back("VolcanoArea");
	ReignName.push_back("DesertArea");
	ReignName.push_back("SnowyArea");
	ReignName.push_back("RebirthTemple");

	// Ϊÿ���������ռ�,��������δ����ռ�ᷢ������Խ��
	BlackFogLayer.resize(MapReign.size()); 
	for (unsigned int i = 0; i < MapReign.size(); ++i) {
		//���������
		BlackFogLayer[i] = cocos2d::DrawNode::create();
		
		if (i < 4) {    //ǰ�ĸ�Ϊ����
			//����ÿ������ľ������Ͻ�
			cocos2d::Vec2 destination;
			destination.x = MapReign[i].origin.x + MapReign[i].size.width;
			destination.y = MapReign[i].origin.y - MapReign[i].size.height;

			//����ÿ���������
			BlackFogLayer[i]->drawSolidRect(MapReign[i].origin, destination, Color4F::BLACK);    //���ú������ɫΪ��ɫ,͸����Ϊ0
			BlackFogLayer[i]->drawRect(MapReign[i].origin, destination, Color4F::WHITE);    //���ð�ɫ�߿�
		}
		else {    //��ʼ����ΪԲ��
			BlackFogLayer[i]->drawSolidCircle(MapReign[i].origin, MapReign[i].size.width, 0, 360, Color4F::BLACK);    //���ú������ɫΪ��ɫ,͸����Ϊ0
			BlackFogLayer[i]->drawCircle(MapReign[i].origin, MapReign[i].size.width, 0, 360, false, Color4F::WHITE);    //���ð�ɫ�߿�
		}

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
	this->DisperseBlackFog(ReignIndex);
}

bool MicroMap::IsContainedReign(cocos2d::Rect& rect, cocos2d::Vec2& Pos, int TypeId) {
	if (TypeId == 0) {
		//�ж�Pos�Ƿ���rect��
		if (Pos.x >= rect.origin.x && Pos.x <= rect.origin.x + rect.size.width &&
			Pos.y <= rect.origin.y && Pos.y >= rect.origin.y - rect.size.height)
			return true;
		else
			return false;
	}
	else {
		//�ж�Pos�Ƿ���Բ��
		return rect.origin.distance(Pos) <= rect.size.width;    //�����жϣ�����ΪԲ�İ뾶
	}
}

void MicroMap::OnMouseMove(Event* event) {
	//��ȡ���λ��
	auto mouseEvent = dynamic_cast<cocos2d::EventMouse*>(event);
	float mouseX = mouseEvent->getCursorX();
	float mouseY = mouseEvent->getCursorY();

	//����Ļ����ת��Ϊ�������꣬�ǳ���Ҫ��
	//��Ļ���������Ͻ�Ϊԭ�㣬���������������½�Ϊԭ�㣬����Ҫ��������ת��
	//����Ļ��С��ȥ���λ�ã��õ���������
	Vec2 ScreenSize;
	ScreenSize.x = mouseX;
	ScreenSize.y = visibleSize.height - mouseY;

	for (unsigned int i = 0; i < MapReign.size(); ++i) {
		int TypeId = 0;
		if (i == 4)
			TypeId = 1;    //��i����4��ʱ��˵���ǳ�ʼ���򣬳�ʼ����ΪԲ��

		if (IsBlackFogVisited[i]) {
			if (i < 4) {
				if (IsContainedReign(MapReign[i], ScreenSize, TypeId) && !IsContainedReign(MapReign[4], ScreenSize, 1)) {
					RegionLabel->setString(ReignName[i]);
					break;
				}
			}
			else
				if (IsContainedReign(MapReign[i], ScreenSize, TypeId)) {
					RegionLabel->setString(ReignName[i]);
					break;
				}
		}
	}

	RegionLabel->setPosition(mouseX, mouseY + 20);
}