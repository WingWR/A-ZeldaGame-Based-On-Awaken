#include "Monster.h"
USING_NS_CC;


// ��������
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));

//update����д
//����С�ڹ��﹥������ʱ�����﹥��
//����С�ڹ���������ʱ���������
//���볬�����������룬�����״̬��ԭ̬
void Monster::update(float dt) {
	//����AI

	ai->update(dt);
	state = ai->GetState();
	//����״̬ʵ�ֶ�Ӧ��Ϊ
	if (state == MonsterState::ATTACK) {
		Attack();
	}
	else if (state == MonsterState::CHASE) {
		Chase();
	}
	else if (state == MonsterState::FLEE) {
		Flee();
	}
	else {
		;
	}
}
//������������
void Monster::Die() {

	target->GetBonus(bonus);

	Creature::Die();
}
void Monster::Attack() {
	static int nums = 0;
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����ָ���ɫ����
	Vec2 pos = target->mySprite->getPosition();
	Vec2 mon = this->mySprite->getPosition();
	if (nums < 50) {
		nums++;
		return;
	}
	else {
		nums = 0;
		log("Monster:Attack*****************************************************************");
		log("mon:%f %f", mon.x, mon.y);
		log("positon:%f %f", pos.x, pos.y);
		log("direction:%f %f", direction.x, direction.y);
		log("speed:%d", speed);
	}
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			Creature::Attack(1, target);
		}
		else {
			Creature::Attack(0, target);
		}
	}
	else {
		if (direction.y > 0) {
			Creature::Attack(2, target);
		}
		else {
			Creature::Attack(3, target);
		}
	}
}
void Monster::Chase() {
	static int nums = 0;
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����ָ���ɫ����
	Vec2 pos = target->mySprite->getPosition();
	Vec2 mon = this->mySprite->getPosition();
	if (nums < 50) {
		nums++;
		return;
	}
	else {
		nums = 0;
		log("Monster:Chase*****************************************************************");
		log("mon:%f %f", mon.x, mon.y);
		log("positon:%f %f", pos.x, pos.y);
		log("direction:%f %f", direction.x, direction.y);
		log("speed:%d", speed);
	}
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			Move(1);
		}
		else {
			Move(0);
		}
	}
	else {
		if (direction.y > 0) {
			Move(2);
		}
		else {
			Move(3);
		}
	}

}

void Monster::Flee() {
	static int nums = 0;
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����ָ���ɫ����
	Vec2 pos = target->mySprite->getPosition();
	Vec2 mon = this->mySprite->getPosition();
	if (nums < 15) {
		nums++;
		return;
	}
	else {
		nums = 0;
		log("Monster:Flee*****************************************************************");
		log("mon:%f %f", mon.x, mon.y);
		log("positon:%f %f", pos.x, pos.y);
		log("direction:%f %f", direction.x, direction.y);
		log("speed:%d", speed);
	}
	if (abs(direction.x) > abs(direction.y)) {
		log("a");
		if (direction.x > 0) {
			Creature::Move(0);
		}
		else {
			Creature::Move(1);
		}
	}
	else {
		log("b");

		if (direction.y > 0) {
			Creature::Move(3);
		}
		else {
			Creature::Move(2);
		}
	}
}
//����ȼ��ӳ�
void Monster::levelBonus() {
	Creature::levelBonus();
	base_exp = base_exp * level;
}
//����follow_range
int Monster::GetFollowRange()const {
	return follow_range;
}


//ai��update
void MonsterAI::update(float dt) {
	switch (currentState) {
	case MonsterState::PATROLLING:// ִ��Ѳ���߼�

		if (shouldChasePlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		else if (shouldAttackPlayer()) {
			currentState = MonsterState::ATTACK;
		}
		break;
	case MonsterState::CHASE:// ִ��׷������߼�

		if (shouldAttackPlayer()) {
			currentState = MonsterState::ATTACK;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		else if (shouldPatrol()) {
			currentState = MonsterState::PATROLLING;
		}
		break;
	case MonsterState::ATTACK:	// ִ�й����߼�

		if (shouldChasePlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		else if (shouldPatrol()) {
			currentState = MonsterState::PATROLLING;
		}
		break;
	case MonsterState::FLEE:
		if (shouldChasePlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldPatrol()) {
			currentState = MonsterState::PATROLLING;
		}
		else if (shouldAttackPlayer()) {
			currentState = MonsterState::ATTACK;
		}
		break;
	}

}
//�ж��Ƿ�Ѳ��
bool MonsterAI::shouldPatrol() {
	float distance = monster->mySprite->getPosition().distance(target->mySprite->getPosition());
	log("distance:%f", distance);
	if (distance >= monster->GetFollowRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ񹥻�
bool MonsterAI::shouldAttackPlayer() {
	float distance = monster->mySprite->getPosition().distance(target->mySprite->getPosition());
	log("distance:%f", distance);
	if (distance <= monster->getAtkRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ�׷��
bool MonsterAI::shouldChasePlayer() {
	float distance = monster->mySprite->getPosition().distance(target->mySprite->getPosition());
	log("distance:%f", distance);
	if (distance < monster->GetFollowRange() && distance>monster->getAtkRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ�����
bool MonsterAI::shouldFlee() {
	float distance = monster->mySprite->getPosition().distance(target->mySprite->getPosition());
	log("distance:%f", distance);
	if (monster->getCurrentHp() < monster->getHp() / 10 && distance<monster->GetFollowRange() &&
		distance>monster->getAtkRange()) {
		return true;
	}
	else if (monster->getCurrentHp() < 3 * target->DamageCal(target, monster) &&
		distance<monster->GetFollowRange() && distance>monster->getAtkRange()) {
		return true;
	}
	return false;

}
//������״̬
MonsterState MonsterAI::GetState()const {
	return currentState;
}