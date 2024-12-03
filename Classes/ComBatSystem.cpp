#include "CombatSystem.h"
USING_NS_CC;


// ��������
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));


//����
void Creature::Attack(Creature target,int idx) {
	//���㹥����Χ
	//���target�ڹ�����Χ��
	//target.Hurt(atk);
	//����ʵ��
	// ͼƬ��ǰ׺:����Ų���
	string s;
	if (idx == 1 || idx == 2)
		s = "Role/Player/" + name + "/attack" + std::to_string(idx) + "/" + name + "_atk" + std::to_string(idx) + "_";
	else if (idx == 3)
		s = "Role/Player/" + name + "/attack_final/" + name + "_final_";
	// ֡��
	int count = 0;
	if (name == "Arthur") {
		if (idx == 1)
			count = 10;
		else if (idx == 2)
			count = 12;
		else if (idx == 3)
			count = 15;
	}
	else if (name == "Longbow") {
		if (idx == 1)
			count = 7;
		else if (idx == 2)
			count = 12;
		else if (idx == 3)
			count = 18;
	}
	// ֡����׼��
	Vector<SpriteFrame*> animFrames;//���涯��֡������
	animFrames.reserve(count);//�����ڴ�
	//�������������������󣬽���װ��������
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
	//����
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	//Animate����
	Animate* animate = Animate::create(animation);
	// mySprite->runAction(RepeatForever::create(animate));
	mySprite->runAction(animate);  // ����һ��
	scene->addChild(mySprite);//���������
}
//��ֹ
void Creature::Show() {
	mySprite->setPosition(Vec2(x, y));
	scene->addChild(mySprite);
}
