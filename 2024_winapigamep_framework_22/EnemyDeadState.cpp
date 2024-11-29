#include "pch.h"
#include "EnemyDeadState.h"

#include "Animator.h"
#include "Enemy.h"

EnemyDeadState::EnemyDeadState() : EnemyState(ENEMY_STATE::DEAD)
{
}

EnemyDeadState::~EnemyDeadState()
{
}

void EnemyDeadState::Update()
{
}

void EnemyDeadState::Enter()
{
	GetEnemy()->GetComponent<Animator>()->PlayAnimation(L"Dead", false);

}

void EnemyDeadState::Exit()
{
}
