#include "pch.h"
#include "Enemy.h"

#include "Animator.h"
#include "EnemyStateMachine.h"
#include "Collider.h"
#include "EnemyAttackState.h"
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

Enemy::Enemy()
	:m_tInfo{},
	m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Enemy_zombie1", L"Texture\\Enemy_zombie1.bmp");
	this->AddComponent<Animator>();
	this->AddComponent<Gravity>();
	this->AddComponent<Rigidbody>();
	this->AddComponent<Health>();
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
	animator->CreateAnimation(L"Dead", m_pTex, Vec2(0.f, 864.f),
		Vec2(96.f, 96.f), Vec2(96.f, 0.f), 5, 0.1f);
	tEnemyInfo info;
	info.fSpeed = 100;
	info.fRecogRange = 400;
	info.fAttackRange = 100;
	info.iPower = 4;
	SetInfo(info);
	EnemyStateMachine* pStateMachine = new EnemyStateMachine;
	pStateMachine->AddState(new EnemyIdleState);
	pStateMachine->AddState(new EnemyTraceState);
	pStateMachine->AddState(new EnemyAttackState);
	pStateMachine->AddState(new EnemyRecoverState);
	pStateMachine->AddState(new EnemyGetHitState);
	SetStateMachine(pStateMachine);
	GetComponent<Health>()->onApplyDamaged += [this] { HandleApplyDamaged(); };
	GetComponent<Health>()->onDead += [this] { HandleDead(); };
	pStateMachine->SetCurState(ENEMY_STATE::IDLE);

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

bool Enemy::IsPlayerInRange(float fRange)
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

void Enemy::HandleApplyDamaged()
{
	m_pStateMachine->ChangeState(ENEMY_STATE::GETHIT);
}
void Enemy::HandleDead()
{
	m_pStateMachine->ChangeState(ENEMY_STATE::DEAD);
}
void Enemy::Update()
{
	m_pStateMachine->Update();
}

void Enemy::Render(HDC _hdc)
{
	ComponentRender(_hdc);
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
