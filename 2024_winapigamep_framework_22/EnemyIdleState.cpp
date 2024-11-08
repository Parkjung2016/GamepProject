#include "pch.h"
#include "EnemyIdleState.h"

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
	std::shared_ptr<TitleScene> scene = std::dynamic_pointer_cast<TitleScene>(GET_SINGLE(SceneManager)->GetCurrentScene());
	Player* pPlayer = (Player*)scene->GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Enemy* pEnemy = GetEnemy();
	Vec2 vEnemyPos = pEnemy->GetPos();

	Vec2 vDiff = vPlayerpos - vEnemyPos;
	float fLen = vDiff.Length();

	if (fLen < pEnemy->GetInfo().fRecogRange)
	{
		GetStateMachine()->ChangeState(ENEMY_STATE::TRACE);
	}

}

void EnemyIdleState::Enter()
{
}

void EnemyIdleState::Exit()
{
}
