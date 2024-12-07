#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Audio.h"
#include "Gravity.h"
#include "Health.h"
#include "PlayerAttackState.h"
#include "PlayerBlockState.h"
#include "PlayerDashState.h"
#include "PlayerDeadState.h"
#include "PlayerFallingState.h"
#include "PlayerGetHitState.h"
#include "PlayerHealth.h"
#include "PlayerIdleState.h"
#include "PlayerJumpState.h"
#include "PlayerReloadGunState.h"
#include "PlayerRunState.h"
#include "PlayerStateMachine.h"
#include "PlayerWalkState.h"
#include "Rigidbody.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextUI.h"

Player::Player()
	: m_pHealthTextUI(nullptr), m_iCurrentBulletCount(0), m_iMoveInput(0)
	, m_iDashableCount(0), m_bIsPressRunInput(false), m_bIsPressMoveInput(false), m_pTex(nullptr),
	m_pStateMachine(nullptr), m_tInfo()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\Player.bmp");
}

Player::~Player()
= default;

void Player::Start()
{

	Health* pHealth = this->AddComponent<PlayerHealth>();
	pHealth->SetMaxHealth(30);
	AddComponent<Audio>();
	AddComponent<Animator>();
	AddComponent<Gravity>()->SetCanGravity(false);
	AddComponent<Rigidbody>();
	Collider* collider = this->AddComponent<Collider>();
	collider->SetSize({ 30,86 });
	collider->SetOffSetPos({ 0,20 });
	GetComponent<Animator>()->CreateAnimation(L"Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 6, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Walk", m_pTex, Vec2(0.f, 256.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 10, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Run", m_pTex, Vec2(0.f, 384.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 10, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Dash", m_pTex, Vec2(1024.f, 384.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"JumpUp", m_pTex, Vec2(512.f, 512.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 1, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"JumpDown", m_pTex, Vec2(640.f, 512.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 3, 0.08f);
	GetComponent<Animator>()->CreateAnimation(L"Attack", m_pTex, Vec2(0.f, 640.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Block", m_pTex, Vec2(0.f, 896.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 3, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"ReloadGun", m_pTex, Vec2(0.f, 768.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 17, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"GetHit", m_pTex, Vec2(0.f, 1024.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 4, 0.05f);
	GetComponent<Animator>()->CreateAnimation(L"Dead", m_pTex, Vec2(0.f, 1152.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 5, 0.1f);

	tPlayerInfo info;
	info.fWalkSpeed = 100;
	info.fRunSpeed = 300;
	info.fDashSpeed = 3500;
	info.fDashDuration = .1f;
	info.fJumpPower = 500;
	info.fAirControl = 300;
	info.fBulletSpeed = 600;
	info.iBulletPower = 2;
	info.fBulletKnockBackDuration = .15f;
	info.fBulletKnockBackPower = 200;
	info.iBulletCountPerShot = 3;
	info.iMaxBulletCount = 12;
	SetInfo(info);
	PlayerStateMachine* pStateMachine = new PlayerStateMachine;
	pStateMachine->AddState(new PlayerIdleState);
	pStateMachine->AddState(new PlayerWalkState);
	pStateMachine->AddState(new PlayerRunState);
	pStateMachine->AddState(new PlayerDashState);
	pStateMachine->AddState(new PlayerJumpState);
	pStateMachine->AddState(new PlayerFallingState);
	pStateMachine->AddState(new PlayerAttackState);
	pStateMachine->AddState(new PlayerBlockState);
	pStateMachine->AddState(new PlayerReloadGunState);
	pStateMachine->AddState(new PlayerGetHitState);
	pStateMachine->AddState(new PlayerDeadState);
	SetStateMachine(pStateMachine);
	pStateMachine->SetCurState(PLAYER_STATE::IDLE);
	GetComponent<Health>()->onApplyDamaged += [this] { HandleApplyDamagedEvent(); };
	GetComponent<Health>()->onDead += [this] { HandleDeadEvent(); };

	m_pBulletCountTextUI = new TextUI;
	m_pBulletCountTextUI->SetPos({ 0,25 });
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pBulletCountTextUI, LAYER::UI);

	ReloadGun();
	m_pCurrentDashCountTextUI = new TextUI;
	m_pCurrentDashCountTextUI->SetPos({ 0,50 });
	m_pCurrentDashCountTextUI->SetText(L"Dash : " + std::to_wstring(m_iDashableCount));
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pCurrentDashCountTextUI, LAYER::UI);


	m_pHealthTextUI = new TextUI;
	m_pHealthTextUI->SetPos({ 0,0 });
	int iHealth = GetComponent<Health>()->GetCurrentHealth();
	m_pHealthTextUI->SetText(L"Health : " + std::to_wstring(iHealth));
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(m_pHealthTextUI, LAYER::UI);
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
	int iHealth = GetComponent<Health>()->GetCurrentHealth();
	m_pHealthTextUI->SetText(L"Health : " + std::to_wstring(iHealth));
	GET_SINGLE(Camera)->Shake(.05f, .2f);
	m_pStateMachine->ChangeState(PLAYER_STATE::GETHIT);

}

void Player::HandleDeadEvent() const
{
	m_pStateMachine->ChangeState(PLAYER_STATE::DEAD);

}


void Player::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Player::AfterRender()
{
	if (!m_bInit)
	{
		m_bInit = true;
		GetComponent<Gravity>()->SetCanGravity(true);
	}
}

void Player::EnterCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{

}


void Player::UpdateBulletCountText()
{
	int iBulletCount = GetCurrentBulletCount();
	m_pBulletCountTextUI->SetText(L"Bullet : " + std::to_wstring(iBulletCount));
}

void Player::AddDashableCount()
{
	m_iDashableCount++;
	m_pCurrentDashCountTextUI->SetText(L"Dash : " + std::to_wstring(m_iDashableCount));

}

void Player::SubDashableCount()
{
	m_iDashableCount--;
	m_pCurrentDashCountTextUI->SetText(L"Dash : " + std::to_wstring(m_iDashableCount));

}

void Player::SetStateMachine(PlayerStateMachine* _stateMachine)
{
	m_pStateMachine = _stateMachine;
	m_pStateMachine->m_pOwner = this;
}

void Player::ReloadGun()
{
	m_iCurrentBulletCount = GetInfo().iMaxBulletCount;
	UpdateBulletCountText();
}

void Player::FireGun()
{
	m_iCurrentBulletCount--;
	UpdateBulletCountText();
}
