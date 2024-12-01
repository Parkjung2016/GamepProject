#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Gravity.h"
#include "Health.h"
#include "PlayerAttackState.h"
#include "PlayerDeadState.h"
#include "PlayerFallingState.h"
#include "PlayerGetHitState.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerStateMachine.h"
#include "PlayerWalkState.h"
#include "Rigidbody.h"

Player::Player()
	: m_iMoveInput(0)
	, m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\Player.bmp");
	this->AddComponent<Health>()->SetMaxHealth(10);
	this->AddComponent<Animator>();
	this->AddComponent<Gravity>();
	this->AddComponent<Rigidbody>();
	Collider* collider = this->AddComponent<Collider>();
	collider->SetSize({ 30,84 });
	collider->SetOffSetPos({ 0,20 });
	GetComponent<Animator>()->CreateAnimation(L"Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 6, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Walk", m_pTex, Vec2(0.f, 256.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 10, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Run", m_pTex, Vec2(0.f, 384.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 10, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"JumpUp", m_pTex, Vec2(512.f, 512.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"JumpDown", m_pTex, Vec2(640.f, 512.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 3, 0.08f);
	GetComponent<Animator>()->CreateAnimation(L"Attack", m_pTex, Vec2(0.f, 640.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"GetHit", m_pTex, Vec2(0.f, 1024.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.05f);
	GetComponent<Animator>()->CreateAnimation(L"Dead", m_pTex, Vec2(0.f, 1152.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 5, 0.1f);
	tPlayerInfo info;
	info.fWalkSpeed = 100;
	info.fRunSpeed = 300;
	info.fJumpPower = 500;
	info.fAirControl = 300;
	info.fBulletSpeed = 600;
	info.iBulletPower = 2;
	info.fBulletKnockBackDuration = .15f;
	info.fBulletKnockBackPower = 200;
	info.iBulletCountPerShot = 3;
	SetInfo(info);
	PlayerStateMachine* pStateMachine = new PlayerStateMachine;
	pStateMachine->AddState(new PlayerIdleState);
	pStateMachine->AddState(new PlayerWalkState);
	pStateMachine->AddState(new PlayerRunState);
	pStateMachine->AddState(new PlayerJumpState);
	pStateMachine->AddState(new PlayerFallingState);
	pStateMachine->AddState(new PlayerAttackState);
	pStateMachine->AddState(new PlayerGetHitState);
	pStateMachine->AddState(new PlayerDeadState);
	SetStateMachine(pStateMachine);
	pStateMachine->SetCurState(PLAYER_STATE::IDLE);
	GetComponent<Health>()->onApplyDamaged += [this] { HandleApplyDamagedEvent(); };
	GetComponent<Health>()->onDead += [this] { HandleDeadEvent(); };
}

Player::~Player()
{
	if (nullptr != m_pTex)
		delete m_pTex;
}
void Player::Update()
{
	m_pStateMachine->Update();

	UpdateInput();


}
void Player::UpdateInput()
{
	m_bIsPressRunInput = GET_KEY(KEY_TYPE::LSHIFT);
	UpdateMoveInput();
}

void Player::UpdateMoveInput()
{
	m_bIsPressMoveInput = m_iMoveInput != 0;
	if (GET_KEY(KEY_TYPE::LEFT) && GET_KEY(KEY_TYPE::RIGHT))
	{
		m_iMoveInput = 0;
	}
	else if (GET_KEY(KEY_TYPE::LEFT))
	{
		m_iMoveInput = -1;
	}
	else if (GET_KEY(KEY_TYPE::RIGHT))
	{
		m_iMoveInput = 1;
	}
	else if (GET_KEYUP(KEY_TYPE::LEFT) || GET_KEYUP(KEY_TYPE::RIGHT))
		m_iMoveInput = 0;
}

void Player::HandleApplyDamagedEvent()
{
	m_pStateMachine->ChangeState(PLAYER_STATE::GETHIT);

}

void Player::HandleDeadEvent()
{
	m_pStateMachine->ChangeState(PLAYER_STATE::DEAD);

}


void Player::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Player::EnterCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{

}


void Player::SetStateMachine(PlayerStateMachine* _stateMachine)
{
	m_pStateMachine = _stateMachine;
	m_pStateMachine->m_pOwner = this;
}
