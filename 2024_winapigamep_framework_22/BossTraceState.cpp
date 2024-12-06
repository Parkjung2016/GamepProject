#include "pch.h"
#include "BossTraceState.h"

#include "Animator.h"
#include "Boss.h"
#include "BossStateMachine.h"
#include "Player.h"
#include "Rigidbody.h"

BossTraceState::BossTraceState() : BossState(BOSS_STATE::TRACE)
{
}

BossTraceState::~BossTraceState()
{
}

void BossTraceState::Update()
{
	Boss* pBoss = GetBoss();
	float fRecogRange = pBoss->GetInfo().fRecogRange;
	float fAttackRange = pBoss->GetInfo().fAttackRange;
	float fDashAttackRange = pBoss->GetInfo().fDashAttackRange;
	Player* pPlayer = pBoss->GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = pBoss->GetPos();

	pBoss->GetComponent<Animator>()->SetIsRotate(vPlayerpos.x < vEnemyPos.x);
	if (!pBoss->IsPlayerInRange(fRecogRange))
	{
		GetStateMachine()->ChangeState(BOSS_STATE::IDLE);
		return;
	}
	if (pBoss->IsPlayerInRange(fAttackRange))
	{
		GetStateMachine()->ChangeState(BOSS_STATE::ATTACK);
		return;
	}
	if (pBoss->IsStep2() && !pBoss->IsPlayerInRange(fDashAttackRange * .9f) && pBoss->IsPlayerInRange(fDashAttackRange))
	{
		GetStateMachine()->ChangeState(BOSS_STATE::DASHATTACK);
		return;
	}


	Vec2 vDir = (vPlayerpos - vEnemyPos).Normalize();
	Vec2 vV = pBoss->GetComponent<Rigidbody>()->GetVelocity();
	float fSpeed = pBoss->GetInfo().fSpeed;
	pBoss->GetComponent<Rigidbody>()->SetVelocity({ vDir.x * fSpeed , vV.y });
}

void BossTraceState::Enter()
{
	if (GetBoss()->IsStep2())
		GetBoss()->GetComponent<Animator>()->PlayAnimation(L"TraceFast", true);
	else
		GetBoss()->GetComponent<Animator>()->PlayAnimation(L"Trace", true);

}

void BossTraceState::Exit()
{
}
