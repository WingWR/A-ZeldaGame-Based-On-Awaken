
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


//����ȼ��ӳ�
void Monster::Level_Bonus() {
	Creature::Level_Bonus();
	base_exp = base_exp * level;
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
bool MonsterAI::shouldChasePlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance > monster.) {
		Vec2 direction = player->getPosition() - this->getPosition();
		direction.normalize();
		Vec2 newPosition = this->getPosition() + direction * speed * dt;
		this->setPosition(newPosition);
	}
}
//������״̬
MonsterState MonsterAI::GetState()const {
	return currentState;
}

