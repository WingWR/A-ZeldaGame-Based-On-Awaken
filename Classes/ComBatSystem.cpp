/*
#include "CombatSystem.h"
#include "Player.h"
USING_NS_CC;


// ��������
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));




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

void Monster::Chase() {
	Vec2 direction = target->getPosition() - this->getPosition();//����
	direction.normalize();//��λ��
	Vec2 newPosition = this->getPosition() + direction * this->GetSpeed() * deltatime;//��һ֡�ƶ�����
	this->setPosition(newPosition);
}
//����ȼ��ӳ�
void Monster::Level_Bonus() {
	Creature::Level_Bonus();
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
	if (distance <= monster->GetATKRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ�׷��
bool MonsterAI::shouldChasePlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance < monster->GetFollowRange()&&distance>monster->GetATKRange()) {
		return true;
	}
	return false;
}
bool MonsterAI::shouldFlee() {
	if (current_hp < hp / 10) {
		return ture;
	}
	else if (hp < 3 * target->GetATKValue()) {
		return ture;
	}


}
//������״̬
MonsterState MonsterAI::GetState()const {
	return currentState;
}

*/