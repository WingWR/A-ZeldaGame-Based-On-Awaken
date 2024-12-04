#include "CombatSystem.h"
USING_NS_CC;


// ��������
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));


//����
void Creature::Attack(Node* target,int idx) {
	//���㹥����Χ
	//���target�ڹ�����Χ��
	//target.Hurt(atk);
	//����ʵ��
	// ͼƬ��ǰ׺:����Ų���
	string s;
	if (idx == 1 || idx == 2)
		s = "Role/Player/" + role + "/attack" + std::to_string(idx) + "/" + role + "_atk" + std::to_string(idx) + "_";
	else if (idx == 3)
		s = "Role/Player/" + role + "/attack_final/" + role + "_final_";
	// ֡��
	int count = 0;
	if (role == "Arthur") {
		if (idx == 1)
			count = 10;
		else if (idx == 2)
			count = 12;
		else if (idx == 3)
			count = 15;
	}
	else if (role == "Longbow") {
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
//update����д
//����С�ڹ��﹥������ʱ�����﹥��
//����С�ڹ���������ʱ���������
//���볬�����������룬�����״̬��ԭ̬
void Monster::update(float dt) {
	float distance = target->getPosition().distance(getPosition());
	if (distance < atk_range) {
		Attack(target, 1);
	}
	else if (distance < follow_range) {
		auto followAction = Follow::create(target);
		this->runAction(followAction);
	}
	else {
		state = State::WALKING;
	}
}

//��Ҫ��ѭ����Ϊǰ����������ٶ����㿪ʼս������
void Monster::StartFight() {
	
}
