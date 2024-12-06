/*
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
//�ƶ�
void Creature::Move() {

}
//Player��ý���
void Player::GetBonus(Bonus bonus) {
	//���齱��
	current_exp += bonus.exp;
	//����
	while (current_exp >= next_level_exp) {
		current_exp -= next_level_exp;
		level++;
		Creature::Level_Bonus;
		next_level_exp *= (1 + level * 0.1);
	}
	//��Ʒ����
	//�ݴ�������Ʒ��װ��
}


//update����д
//����С�ڹ��﹥������ʱ�����﹥��
//����С�ڹ���������ʱ���������
//���볬�����������룬�����״̬��ԭ̬
void Monster::update(float dt) {
	//����AI
	ai.update(dt);
	state = ai.GetState();
	//����״̬ʵ�ֶ�Ӧ��Ϊ
}
//������������
void Monster::Die() {

	target->GetBonus(bonus);

	Creature::Die();
}
//�ȼ��ӳ�
void Creature::Level_Bonus() {
	int hp = hp * level;
	int mp = mp * level;
	int atk = atk * level;
	
	int def = def * level;
	int speed = speed * (0.05 * level + 1);

}
//����ȼ��ӳ�
void Monster::Level_Bonus() {
	Creature::Level_Bonus();
	base_exp = base_exp * level;
}
void MonsterAI::update(float dt) {
	switch (currentState) {
	case MonsterState::PATROLLING:// ִ��Ѳ���߼�

		if (shouldChasePlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	case MonsterState::CHASE:// ִ��׷������߼�

		if (shouldAttackPlayer()) {
			currentState = MonsterState::ATTACK;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	case MonsterState::ATTACK:	// ִ�й����߼�

		if (!shouldAttackPlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	}
}
//������״̬
MonsterState MonsterAI::GetState()const {
	return currentState;
}

*/