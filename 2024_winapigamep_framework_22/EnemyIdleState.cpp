#include "pch.h"
#include "EnemyIdleState.h"

#include "Animator.h"
#include "EnemyStateMachine.h"
#include "Enemy.h"
#include "Player.h"
#include "SceneManager.h"
#include "TitleScene.h"


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

	if (pEnemy->IsPlayerInRange(fRecogRange))
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::TRACE);
	}

}

void EnemyIdleState::Enter()
{
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
}

void EnemyIdleState::Exit()
{
}
