#include "pch.h"
#include "Boss.h"

#include "Animator.h"
#include "Audio.h"
#include "BossAttackState.h"
#include "BossDashAttackState.h"
#include "BossDeadState.h"
#include "BossGetHitState.h"
#include "BossIdleState.h"
#include "BossRecoverState.h"
#include "BossStateMachine.h"
#include "BossTraceState.h"
#include "EffectManager.h"
#include "GameScene.h"
#include "Gravity.h"
#include "Health.h"
#include "MyFunc.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Rigidbody.h"
#include "SceneManager.h"
#include "Texture.h"
Boss::Boss()
	: m_pTex(nullptr),
	m_tInfo{},
	m_pStateMachine(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss", L"Texture\\Boss.bmp");
}

Boss::~Boss()
{
	if (nullptr != m_pStateMachine)
		delete m_pStateMachine;
}
void Boss::Start()
{
	this->AddComponent<Animator>();
	this->AddComponent<Audio>();
	this->AddComponent<Gravity>()->SetCanGravity(false);
	this->AddComponent<Rigidbody>();
	this->AddComponent<Health>()->SetMaxHealth(50);
	Collider* collider = this->AddComponent<Collider>();
	collider->SetSize({ 30,86 });
	collider->SetOffSetPos({ 0,20 });
	Animator* animator = GetComponent<Animator>();
	animator->CreateAnimation(L"Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 5, 0.1f);
	animator->CreateAnimation(L"Trace", m_pTex, Vec2(0.f, 128.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 7, 0.1f);
	animator->CreateAnimation(L"TraceFast", m_pTex, Vec2(0.f, 256.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 8, 0.1f);
	animator->CreateAnimation(L"Attack", m_pTex, Vec2(0.f, 384.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 5, 0.1f);
	animator->CreateAnimation(L"DashAttack", m_pTex, Vec2(0.f, 512.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 5, 0.1f);
	animator->CreateAnimation(L"GetHit", m_pTex, Vec2(0.f, 640.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 5, 0.1f);
	animator->CreateAnimation(L"Dead", m_pTex, Vec2(0.f, 768.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	tBossInfo info;
	info.fSpeed = 100;
	info.fDashSpeed = 800;
	info.fRecogRange = 400;
	info.fAttackRange = 50;
	info.fDashAttackRange = 150;
	info.fAttackKnockBackPower = 200;
	info.fAttackKnockBackDuration = .1f;
	info.iPower = 6;
	info.iStep2HPPercent = 50;
	SetInfo(info);
	BossStateMachine* pStateMachine = new BossStateMachine;
	pStateMachine->AddState(new BossIdleState);
	pStateMachine->AddState(new BossTraceState);
	pStateMachine->AddState(new BossAttackState);
	pStateMachine->AddState(new BossDashAttackState);
	pStateMachine->AddState(new BossRecoverState);
	pStateMachine->AddState(new BossGetHitState);
	pStateMachine->AddState(new BossDeadState);
	SetStateMachine(pStateMachine);
	GetComponent<Health>()->onApplyDamaged += [this] { HandleApplyDamaged(); };
	GetComponent<Health>()->onDead += [this] { HandleDead(); };
	pStateMachine->SetCurState(BOSS_STATE::IDLE);
}
void Boss::SetStateMachine(BossStateMachine* _stateMachine)
{
	m_pStateMachine = _stateMachine;
	m_pStateMachine->m_pOwner = this;
}

void Boss::CheckStep2()
{
	Health* pHealth = GetComponent<Health>();
	int currentHealth = pHealth->GetCurrentHealth();
	int step2Health = (int)(pHealth->GetMaxHealth() * GetInfo().iStep2HPPercent * .01f);

	if (!m_bIsStep2 && currentHealth <= step2Health)
	{
		m_bIsStep2 = true;

		EnterStep2();

	}
}

void Boss::EnterStep2()
{
	m_pStep2Effect = GET_SINGLE(EffectManager)->SpawnEffect({ 0,-10 }, { 592.f,0.f }, { 16.f,16.f }, { 16.f,0.f }, 3, this);

	m_tInfo.fSpeed *= 1.5f;
}

void Boss::HandleApplyDamaged()
{
	m_pStateMachine->ChangeState(BOSS_STATE::GETHIT);
	CheckStep2();
}
void Boss::HandleDead()
{
	DeleteObject((Object*)m_pStep2Effect);
	m_pStateMachine->ChangeState(BOSS_STATE::DEAD);
}
bool Boss::IsPlayerInRange(float fRange) const
{
	Player* pPlayer = GetPlayer();

	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vEnemyPos = GetPos();

	Vec2 vDiff = vPlayerpos - vEnemyPos;
	float fLen = vDiff.Length();

	return fLen < fRange;
}

bool Boss::IsPlayerInFront()
{
	bool isRotate = GetComponent<Animator>()->GetIsRotate();
	Vec2 vPos = GetPos();
	Vec2 vPlayerPos = GetPlayer()->GetPos();
	return !isRotate ? vPos.x <= vPlayerPos.x : vPlayerPos.x <= vPos.x;
}

Player* Boss::GetPlayer() const
{
	std::shared_ptr<GameScene> scene = std::dynamic_pointer_cast<GameScene>(GET_SINGLE(SceneManager)->GetCurrentScene());
	Player* pPlayer = (Player*)scene->GetPlayer();
	return pPlayer;
}


void Boss::Update()
{
	m_pStateMachine->Update();
}


void Boss::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Boss::AfterRender()
{
	if (!m_bInit)
	{
		m_bInit = true;
		GetComponent<Gravity>()->SetCanGravity(true);
	}
}
