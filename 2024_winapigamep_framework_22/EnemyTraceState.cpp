#include "pch.h"
#include "EnemyTraceState.h"

#include "Animator.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "GameScene.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SceneManager.h"

EnemyTraceState::EnemyTraceState()
	:EnemyState(ENEMY_STATE::TRACE)
{
}

EnemyTraceState::~EnemyTraceState()
{
}

void EnemyTraceState::Update()
{
	Enemy* pEnemy = GetEnemy();
	float fRecogRange = pEnemy->GetInfo().fRecogRange;
	float fAttackRange = pEnemy->GetInfo().fAttackRange;
	if (!pEnemy->IsPlayerInRange(fRecogRange))
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::IDLE);
		return;
	}
	if (pEnemy->IsPlayerInRange(fAttackRange))
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::ATTACK);
		return;
	}
	std::shared_ptr<GameScene> scene = std::dynamic_pointer_cast<GameScene>(GET_SINGLE(SceneManager)->GetCurrentScene());
	Player* pPlayer = (Player*)scene->GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = pEnemy->GetPos();

	Vec2 vDir = (vPlayerpos - vEnemyPos).Normalize();
	Vec2 vV = pEnemy->GetComponent<Rigidbody>()->GetVelocity();
	float fSpeed = pEnemy->GetInfo().fSpeed;
	pEnemy->GetComponent<Rigidbody>()->SetVelocity({ vDir.x * fSpeed , vV.y });

}

void EnemyTraceState::Enter()
{
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Trace", true);

}

void EnemyTraceState::Exit()
{
}
