#include "pch.h"
#include "EnemyTraceState.h"

#include "Animation.h"
#include "Animator.h"
#include "Audio.h"
#include "AudioSystem.h"
#include "Enemy.h"
#include "EnemyStateMachine.h"
#include "GameScene.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "SceneManager.h"
#include "SoundEvent.h"

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
	Player* pPlayer = pEnemy->GetPlayer();
	Animation* currentAnim = GetEnemy()->GetComponent<Animator>()->GetCurrentAnim();
	size_t curFrame = currentAnim->GetCurFrame();
	if ((curFrame == 2 || curFrame == 7))
	{
		if (!m_bIsSoundTriggered)
		{

			m_bIsSoundTriggered = true;
			GetEnemy()->GetComponent<Audio>()->PlayEvent("event:/SFX/Footstep");
		}
	}
	else
		m_bIsSoundTriggered = false;
	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = pEnemy->GetPos();

	pEnemy->GetComponent<Animator>()->SetIsRotate(vPlayerpos.x < vEnemyPos.x);
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
