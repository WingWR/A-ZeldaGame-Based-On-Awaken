#include "Monster.h"
USING_NS_CC;
  // 基本动作
auto attackAction = MoveBy::create(1.0f, Vec2(100, 0));
 //update的重写
//距离小于怪物攻击距离时，怪物攻击
//距离小于怪物跟随距离时，怪物跟随
//距离超过怪物跟随距离，怪物的状态回原态
void Monster::update(float dt) {
	 direction = target->mySprite->getPosition() - this->mySprite->getPosition();//怪物指向角色方向
	//怪物AI
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
	case MonsterState::PATROLLING:// 执行巡逻逻辑
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
	case MonsterState::CHASE:// 执行追踪玩家逻辑
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
	case MonsterState::ATTACK:	// 执行攻击逻辑
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
//判断是否巡逻
bool MonsterAI::shouldPatrol() {
	 
	 
	if (distance >= monster->GetFollowRange()) {
		return true;
	}
	return false;
}
//判断是否攻击
bool MonsterAI::shouldAttackPlayer() {
	 
	 
	if (distance <= monster->getAtkRange()) {
		return true;
	}
	return false;
}
//判断是否追踪
bool MonsterAI::shouldChasePlayer() {
	 
	 
	if (distance < monster->GetFollowRange() && distance>monster->getAtkRange()) {
		return true;
	}
	return false;
}
//判断是否逃跑
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
//返回现状态
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