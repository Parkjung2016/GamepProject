#include "pch.h"
#include "BossIdleState.h"

#include "Animator.h"
#include "Audio.h"
#include "Boss.h"
#include "BossStateMachine.h"
#include "GameScene.h"
#include "Health.h"
#include "Player.h"
#include "Rigidbody.h"
#include "SceneManager.h"
#include "SoundObject.h"

BossIdleState::BossIdleState() : BossState(BOSS_STATE::IDLE)
{
}

BossIdleState::~BossIdleState()
{
}

void BossIdleState::Update()
{
	Boss* pBoss = GetBoss();
	float fRecogRange = pBoss->GetInfo().fRecogRange;
	bool bPlayerIsDead = pBoss->GetPlayer()->GetComponent<Health>()->GetIsDead();

	if (!bPlayerIsDead && pBoss->IsPlayerInRange(fRecogRange))
	{
		if (!m_bIsInit)
		{
			m_bIsInit = true;
			std::dynamic_pointer_cast<GameScene>(GET_SINGLE(SceneManager)->GetCurrentScene())->GetBGMSoundObject()->GetSoundEvent().SetParameterWithLabel("Type", "Boss");
		}
		GetStateMachine()->ChangeState(BOSS_STATE::TRACE);
	}
}

void BossIdleState::Enter()
{
	Rigidbody* pRigid = GetBoss()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	GetBoss()->GetComponent<Animator>()->PlayAnimation(L"Idle", true);
}

void BossIdleState::Exit()
{
}
