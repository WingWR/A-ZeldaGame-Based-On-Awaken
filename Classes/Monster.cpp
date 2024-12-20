#include "Monster.h"
USING_NS_CC;
  // ��������
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));
 //update����д
//����С�ڹ��﹥������ʱ�����﹥��
//����С�ڹ���������ʱ���������
//���볬�����������룬�����״̬��ԭ̬
void Monster::update(float dt) {
	 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//����ָ���ɫ����
	//����AI
	Vec2 mon = this->mySprite->getPosition();
	x=getXY().x;
	y=getXY().y;
	static int nums = 50;
	if (nums < 60) {
		nums++;
	}
	else {
		nums = 0;
		log("mon***************************");
		log("position:%f %f", mon.x, mon.y);
		log("speed:%d", speed);
		log("direction:%f %f", direction.x, direction.y);
	}
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
	static int nums =100 ;
	 
  	if (nums < 120) {
		nums++;
		return;
	}
	else {
		nums = 0;
		log("Monster:Attack*****************************************************************");
 		  
 	}
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			face_to = 1;
			Creature::Attack();
			target->Hurt();
			target->DecreaseHp(DamageCal(this, target));
		}
		else {
			face_to = 0;
			Creature::Attack();
			target->Hurt();
			target->DecreaseHp(DamageCal(this, target));
		}
	}
	else {
		if (direction.y>0) {
			face_to = 2;
			Creature::Attack();
			target->Hurt();
			target->DecreaseHp(DamageCal(this, target));
		}
		else {
			face_to = 3;
			Creature::Attack();
			target->Hurt();
			target->DecreaseHp(DamageCal(this, target));
		}
	}
}
void Monster::Chase() {
	static int nums = 30;
	 
  	if (nums < 50) {
		nums++;
		return;
	}
	else {
		nums = 0;
		log("Monster:Chase*****************************************************************");
		  
 	}
	
	if (abs(direction.x) > abs(direction.y)) {
		if (direction.x > 0) {
			Move(1);
			mySprite->setPosition(x + (speed + 1.0 - 1.0) / 60, y);
		}
		else {
			Move(0);
			mySprite->setPosition(x + (-speed + 1.0 - 1.0) / 60, y);
		}
	}
	else {
		if (direction.y>0) {
			Move(2);
			mySprite->setPosition(x, y + (speed + 1.0 - 1.0) / 60);
		}
		else {
			Move(3);
			mySprite->setPosition(x, y + (-speed + 1.0 - 1.0) / 60);
		}
	}
 }
 void Monster::Flee() {
	static int nums = 0;
	 
  	if (nums < 50) {
		nums++;
		return;
	}
	else {
		nums = 0;
		log("Monster:Flee*****************************************************************");	 
		  
 	}
	if (abs(direction.x) > abs(direction.y)) {
		log("a");
		if (direction.x > 0) {
			Creature::Move(0);
			mySprite->setPosition(x + (-speed + 1.0 - 1.0) / 60, y);
		}
		else {
			Creature::Move(1);
			mySprite->setPosition(x + (speed + 1.0 - 1.0) / 60, y);
		}
	}
	else {
		log("b");
 		if (direction.y > 0) {
			Creature::Move(3);
			mySprite->setPosition(x, y + (-speed + 1.0 - 1.0) / 60);
		}
		else {
			Creature::Move(2);
			mySprite->setPosition(x, y + (speed + 1.0 - 1.0) / 60);
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
  distance = monster->mySprite->getPosition().distance(target->mySprite->getPosition());
  static int nums = 50;
  if (nums < 60) {
	  nums++;
  }
  else {
	  nums = 0;
	  log("distance:%f", distance);
  }
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
	 
	 
	if (distance >= monster->GetFollowRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ񹥻�
bool MonsterAI::shouldAttackPlayer() {
	 
	 
	if (distance <= monster->getAtkRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ�׷��
bool MonsterAI::shouldChasePlayer() {
	 
	 
	if (distance < monster->GetFollowRange() && distance>monster->getAtkRange()) {
		return true;
	}
	return false;
}
//�ж��Ƿ�����
bool MonsterAI::shouldFlee() {
	 
	 
	if (monster->getCurrentHp() < monster->getHp() / 10.0&&shouldChasePlayer()) {
		return true;
	}
	else if (monster->getCurrentHp() < 3 * target->DamageCal(target, monster)&&
		shouldChasePlayer()) {
		return true;
	}
	return false;
 }
//������״̬
MonsterState MonsterAI::GetState()const {
	return currentState;
}
void MonsterRespawn::update(float dt) {
	auto it= monster.begin();
	for(it = monster.begin(); it != monster.end(); it++) {
		if ((*it)->getIsDead()) {
			(*it)->Revive();
			(*it)->setPosition(monster_pos[it - monster.begin()]);
		}
	}
}
//
void MonsterBonus::init() {
	monster_bonus1.exp = 10;
	monster_bonus2.exp = 10;
	monster_bonus3.exp = 10;
	monster_bonus4.exp = 10;
	monster_bonus5.exp = 10;
	monster_bonus6.exp = 10;
	monster_bonus7.exp = 10;
	monster_bonus8.exp = 10;

}