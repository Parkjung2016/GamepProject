#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "Projectile.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "PlayerIdleState.h"
#include "PlayerStateMachine.h"
#include "PlayerWalkState.h"
#include "Rigidbody.h"

Player::Player()
	: m_iInput(0)
	, m_pTex(nullptr)
{
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\Player.bmp");
	this->AddComponent<Animator>();
	this->AddComponent<Rigidbody>();
	this->AddComponent<Collider>();
	//GetComponent<Animator>()->LoadAnimation(L"Animation\\player_idle.anim");
	GetComponent<Animator>()->CreateAnimation(L"Idle", m_pTex, Vec2(0.f, 0.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 6, 0.1f);
	GetComponent<Animator>()->CreateAnimation(L"Walk", m_pTex, Vec2(0.f, 256.f),
		Vec2(128.f, 128.f), Vec2(128.f, 0.f), 10, 0.1f);


	//GetComponent<Animator>()->FindAnimation(L"JiwooFront")->Save(L"Animation\\player_idle.anim");
	GetComponent<Animator>()->PlayAnimation(L"Idle", true);


	tPlayerInfo info;
	info.fWalkSpeed = 100;
	SetInfo(info);
	PlayerStateMachine* pStateMachine = new PlayerStateMachine;
	pStateMachine->AddState(new PlayerIdleState);
	pStateMachine->AddState(new PlayerWalkState);
	SetStateMachine(pStateMachine);
	pStateMachine->SetCurState(PLAYER_STATE::IDLE);

}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	m_pStateMachine->Update();

	m_bIsPressInput = GET_KEY(KEY_TYPE::A) == true || GET_KEY(KEY_TYPE::D) == true;
	if (GET_KEY(KEY_TYPE::A) && GET_KEY(KEY_TYPE::D))
	{
		m_iInput = 0;
	}
	else if (GET_KEY(KEY_TYPE::A))
	{
		m_iInput = -1;
	}
	else if (GET_KEY(KEY_TYPE::D))
	{
		m_iInput = 1;
	}
	else if (GET_KEYUP(KEY_TYPE::A) || GET_KEYUP(KEY_TYPE::D))
		m_iInput = 0;
}

void Player::Render(HDC _hdc)
{

	ComponentRender(_hdc);

}

void Player::UpdateGravity()
{
	GetComponent<Rigidbody>()->AddForce({ 0.f,500.f });
}

void Player::SetStateMachine(PlayerStateMachine* _stateMachine)
{
	m_pStateMachine = _stateMachine;
	m_pStateMachine->m_pOwner = this;
}
