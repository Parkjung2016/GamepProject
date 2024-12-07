#include "pch.h"
#include "Enemy.h"

#include "Animator.h"
#include "Audio.h"
#include "EnemyStateMachine.h"
#include "Collider.h"
#include "EnemyAttackState.h"
#include "EnemyDeadState.h"
#include "EnemyGetHitState.h"
#include "EnemyIdleState.h"
#include "EnemyRecoverState.h"
#include "EnemyTraceState.h"
#include "GameScene.h"
#include "Gravity.h"
#include "Health.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "SceneManager.h"
#include "Texture.h"
#include "TimeManager.h"

Enemy::Enemy()
	: m_fFreezeTime(0), m_pTex(nullptr),
	m_tInfo{},
	m_pStateMachine(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Enemy_zombie1", L"Texture\\Enemy_zombie1.bmp");
}

Enemy::~Enemy()
{
	if (nullptr != m_pStateMachine)
		delete m_pStateMachine;
}

void Enemy::SetStateMachine(EnemyStateMachine* _stateMachine)
{
	m_pStateMachine = _stateMachine;
	m_pStateMachine->m_pOwner = this;
}

bool Enemy::IsPlayerInRange(float fRange) const
{
	Player* pPlayer = GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = GetPos();

	Vec2 vDiff = vPlayerpos - vEnemyPos;
	float fLen = vDiff.Length();

	return fLen < fRange;

}

bool Enemy::IsPlayerInFront()
{
	bool isRotate = GetComponent<Animator>()->GetIsRotate();
	Vec2 vPos = GetPos();
	Vec2 vPlayerPos = GetPlayer()->GetPos();
	return !isRotate ? vPos.x <= vPlayerPos.x : vPlayerPos.x <= vPos.x;
}


Player* Enemy::GetPlayer() const
{
	std::shared_ptr<GameScene> scene = std::dynamic_pointer_cast<GameScene>(GET_SINGLE(SceneManager)->GetCurrentScene());
	Player* pPlayer = (Player*)scene->GetPlayer();
	return pPlayer;
}

void Enemy::HandleApplyDamaged() const
{
	m_pStateMachine->ChangeState(ENEMY_STATE::GETHIT);
}
void Enemy::HandleDead() const
{
	m_pStateMachine->ChangeState(ENEMY_STATE::DEAD);
}

void Enemy::Start()
{
	AddComponent<Audio>()->PlayEvent("event:/SFX/Zombie/ZombieBreath", true);

	AddComponent<Animator>();
	AddComponent<Gravity>()->SetCanGravity(false);
	AddComponent<Rigidbody>();
	AddComponent<Health>()->SetMaxHealth(30);
	Collider* collider = this->AddComponent<Collider>();
	collider->SetSize({ 30,50 });
	collider->SetOffSetPos({ 0,21 });
	Animator* animator = GetComponent<Animator>();
	animator->CreateAnimation(L"Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(96.f, 96.f), Vec2(96.f, 0.f), 9, 0.1f);
	animator->CreateAnimation(L"Trace", m_pTex, Vec2(0.f, 672.f),
		Vec2(96.f, 96.f), Vec2(96.f, 0.f), 10, 0.1f);
	animator->CreateAnimation(L"Attack", m_pTex, Vec2(0.f, 96.f),
		Vec2(96.f, 96.f), Vec2(96.f, 0.f), 4, 0.1f);
	animator->CreateAnimation(L"GetHit", m_pTex, Vec2(0.f, 0.f),
		Vec2(96.f, 96.f), Vec2(96.f, 0.f), 5, 0.1f);
	animator->CreateAnimation(L"Dead", m_pTex, Vec2(0.f, 768.f),
		Vec2(96.f, 96.f), Vec2(96.f, 0.f), 5, 0.1f);
	tEnemyInfo info;
	info.fSpeed = 200;
	info.fRecogRange = 600;
	info.fAttackRange = 50;
	info.iPower = 5;
	info.fAttackKnockBackPower = 200;
	info.fAttackKnockBackDuration = .1f;
	SetInfo(info);
	EnemyStateMachine* pStateMachine = new EnemyStateMachine;
	pStateMachine->AddState(new EnemyIdleState);
	pStateMachine->AddState(new EnemyTraceState);
	pStateMachine->AddState(new EnemyAttackState);
	pStateMachine->AddState(new EnemyRecoverState);
	pStateMachine->AddState(new EnemyGetHitState);
	pStateMachine->AddState(new EnemyDeadState);
	SetStateMachine(pStateMachine);
	GetComponent<Health>()->onApplyDamaged += [this] { HandleApplyDamaged(); };
	GetComponent<Health>()->onDead += [this] { HandleDead(); };
	pStateMachine->SetCurState(ENEMY_STATE::IDLE);
}

void Enemy::Update()
{
	if (m_fFreezeTime > 0)
	{
		Rigidbody* pRigidbody = GetComponent<Rigidbody>();
		if (!pRigidbody)return;
		float fVelocityY = pRigidbody->GetVelocity().y;
		pRigidbody->SetVelocity({ 0.f,fVelocityY });
		m_fFreezeTime -= fDT;
		return;
	}
	m_pStateMachine->Update();
}

void Enemy::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Enemy::AfterRender()
{
	if (!m_bInit)
	{
		m_bInit = true;
		GetComponent<Gravity>()->SetCanGravity(true);
	}
}

void Enemy::EnterCollision(Collider* _other)
{
}

void Enemy::StayCollision(Collider* _other)
{
	//std::cout << "Stay" << std::endl;
}

void Enemy::ExitCollision(Collider* _other)
{
}
