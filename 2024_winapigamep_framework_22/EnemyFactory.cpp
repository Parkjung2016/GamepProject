#include "pch.h"
#include "EnemyFactory.h"

#include "EnemyStateMachine.h"
#include "Enemy.h"
#include "EnemyIdleState.h"
#include "EnemyTraceState.h"


EnemyFactory::EnemyFactory()
{
}

EnemyFactory::~EnemyFactory()
{
}

Enemy* EnemyFactory::CreateEnemy(ENEMY_TYPE _eType, Vec2 _vPos)
{
	Enemy* pEnemy = nullptr;
	switch (_eType)
	{
	case ENEMY_TYPE::NORMAL:
		pEnemy = new Enemy;
		pEnemy->SetPos(_vPos);

		tEnemyInfo info;
		info.fAttack = 10.f;
		info.fAttackRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 100.f;
		info.fSpeed = 150.f;

		pEnemy->SetInfo(info);
		EnemyStateMachine* pStateMachine = new EnemyStateMachine;
		pStateMachine->AddState(new EnemyIdleState);
		pStateMachine->AddState(new EnemyTraceState);
		pStateMachine->SetCurState(ENEMY_STATE::IDLE);

		pEnemy->SetStateMachine(pStateMachine);
		break;

	}

	assert(pEnemy);
	return pEnemy;
}
