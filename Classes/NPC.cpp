#include <NPC.h>

/* �ж��Ƿ��ڴ�����Χ�� */
bool NPC::isTrigger() {
	if (who == nullptr)
		return false;

	int dx = who->mySprite->getPosition().x - x;
	int dy = who->mySprite->getPosition().y - y;

	if (std::pow(dx, 2) + std::pow(dy, 2) <= std::pow(DIST, 2)) {
		return true;
	}
	return false;
}

/* ��NPC���� */
void NPC::Chat() {
	/* �ж��Ƿ��ڴ�����Χ�� */
	if (!isTrigger())
		return;

    /* ����͸����ɫ���� */
    //auto backRect = cocos2d::DrawNode::create();

    ////cocos2d::Vec2 worldPosition = scene->convertToWorldSpace(who->getPosition());
    //cocos2d::Vec2 Position = Director::getInstance()->convertToGL(who->getPosition());
    //cocos2d::Color4F color(1.0f, 1.0f, 1.0f, 0.7);
    //float width = 800.0f;
    //float height = 488.0f;
    //backRect->drawSolidRect(
    //    cocos2d::Vec2(Position.x - width / 2, Position.y - height / 2),
    //    cocos2d::Vec2(Position.x + width / 2, Position.y + height / 2),
    //    color
    //);
    //scene->addChild(backRect, 1);


}

