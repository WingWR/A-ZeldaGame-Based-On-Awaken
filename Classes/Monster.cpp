
#include "Monster.h"
USING_NS_CC;


// 基本动作
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));

//update的重写
//距离小于怪物攻击距离时，怪物攻击
//距离小于怪物跟随距离时，怪物跟随
//距离超过怪物跟随距离，怪物的状态回原态
void Monster::update(float dt) {
	//怪物AI
	
	ai->update(dt);
	state = ai->GetState();
	//根据状态实现对应行为
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
//怪物死亡机制
void Monster::Die() {

	target->GetBonus(bonus);

	Creature::Die();
}
void Monster::Attack() {
	log("Monster:Attack*****************************************************************");
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//方向
	direction.normalize();//单位化
	log("direction:%f%f", direction.x, direction.y);
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
	log("Monster:Chase*****************************************************************");
	Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//方向
	direction.normalize();//单位化
	log("direction:%f%f", direction.x, direction.y);
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
	
		log("Monster:Flee*****************************************************************");
		Vec2 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//方向
		direction.normalize();//单位化
	
	log("direction:%f%f", direction.x, direction.y);
	log("speed:%d", speed);
	
	if (abs(direction.x) > abs(direction.y)) {
		log("a");
		if (direction.x ) {
			Creature::Move(0);
		}
		else {
			Creature::Move(1);
		}
	}
	else {
		log("b");
		
		if (direction.y) {
			Creature::Move(3);
		}
		else {
			Creature::Move(2);
		}
	}
}
//怪物等级加成
void Monster::levelBonus() {
	Creature::levelBonus();
	base_exp = base_exp * level;
}
//返回follow_range
int Monster::GetFollowRange()const {
	return follow_range;
}


//ai的update
void MonsterAI::update(float dt) {
	switch (currentState) {
	case MonsterState::PATROLLING:// 执行巡逻逻辑

		if (shouldChasePlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	case MonsterState::CHASE:// 执行追踪玩家逻辑

		if (shouldAttackPlayer()) {
			currentState = MonsterState::ATTACK;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	case MonsterState::ATTACK:	// 执行攻击逻辑

		if (!shouldAttackPlayer()) {
			currentState = MonsterState::CHASE;
		}
		else if (shouldFlee()) {
			currentState = MonsterState::FLEE;
		}
		break;
	}
}
//判断是否攻击
bool MonsterAI::shouldAttackPlayer() {
	float distance = monster->getPosition().distance(target->getPosition());
	if (distance <= monster->getAtkRange()) {
		return true;
	}
	return false;
}
//判断是否追踪
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
//返回现状态
MonsterState MonsterAI::GetState()const {
	return currentState;
}

