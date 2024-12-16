
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
	//log("Monster:Attack*****************************************************************");
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����
	direction.normalize();//��λ��
	//log("direction:%f%f", direction.x, direction.y);
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			Creature::Attack(1, target);
		}
		else {
			Creature::Attack(0, target);
		}
	}
	else {
		if (direction.y) {
			Creature::Attack(2, target);
		}
		else {
			Creature::Attack(3, target);
		}
	}
}
void Monster::Chase() {
	//log("Monster:Chase*****************************************************************");
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����
	direction.normalize();//��λ��
	//log("direction:%f%f", direction.x, direction.y);
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			Move(1);
		}
		else {
			Move(0);
		}
	}
	else {
		if (direction.y) {
			Move(2);
		}
		else {
			Move(3);
		}
	}

}
void Monster::Flee() {
	
		//log("Monster:Flee*****************************************************************");
		Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����
		direction.normalize();//��λ��
	
	//log("direction:%f%f", direction.x, direction.y);
	//log("speed:%d", speed);
	
	if (abs(direction.x) > abs(direction.y)) {
		//log("a");
		if (direction.x ) {
			Creature::Move(0);
		}
		else {
			Creature::Move(1);
		}
	}
	else {
		//log("b");
		
		if (direction.y) {
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
//�ж��Ƿ񹥻�
bool MonsterAI::shouldAttackPlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance <= monster->getAtkRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ�׷��
bool MonsterAI::shouldChasePlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance < monster->GetFollowRange()&&distance>monster->getAtkRange()) {
		return true;
	}
	return false;
}
bool MonsterAI::shouldFlee() {
	if (monster->getCurrentHp() < monster->getHp() / 10) {
		return true;
	}
	else if (monster->getCurrentHp() < 3 * target->DamageCal(target,monster)) {
		return true;
	}


}
//������״̬
MonsterState MonsterAI::GetState()const {
	return currentState;
}

