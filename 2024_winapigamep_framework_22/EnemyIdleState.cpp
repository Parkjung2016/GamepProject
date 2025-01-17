#include "pch.h"
#include "EnemyIdleState.h"

#include "Animator.h"
#include "Audio.h"
#include "EnemyStateMachine.h"
#include "Enemy.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"


EnemyIdleState::EnemyIdleState()
	:EnemyState(ENEMY_STATE::IDLE)
{
}

EnemyIdleState::~EnemyIdleState()
{
}

void EnemyIdleState::Update()
{
	Enemy* pEnemy = GetEnemy();
	float fRecogRange = pEnemy->GetInfo().fRecogRange;
	bool bPlayerIsDead = pEnemy->GetPlayer()->GetComponent<Health>()->GetIsDead();

	if (!bPlayerIsDead && pEnemy->IsPlayerInRange(fRecogRange))
	{
		GetEnemy()->GetComponent<Audio>()->PlayEvent("event:/SFX/Zombie/ZombieFindPlayer");


		GetStateMachine()->ChangeState(ENEMY_STATE::TRACE);
	}

}

void EnemyIdleState::Enter()
{

	Rigidbody* pRigid = GetEnemy()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
}

void EnemyIdleState::Exit()
{
}
