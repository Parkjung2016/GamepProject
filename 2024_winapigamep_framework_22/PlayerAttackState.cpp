#include "pch.h"
#include "PlayerAttackState.h"

#include "Animation.h"
#include "Animator.h"
#include "Bullet.h"
#include "EventManager.h"
#include "MyFunc.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "Rigidbody.h"

PlayerAttackState::PlayerAttackState() : PlayerState(PLAYER_STATE::ATTACK)
{
}

PlayerAttackState::~PlayerAttackState()
{
}

void PlayerAttackState::Update()
{

	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
	Animation* currentAnim = GetPlayer()->GetComponent<Animator>()->GetCurrentAnim();
	bool isFinishedAnimation = currentAnim->IsFinished();
	if (isFinishedAnimation)
	{
		GetStateMachine()->ChangeState(PLAYER_STATE::IDLE);
		return;
	}
	if (!m_bIsFired && currentAnim->GetCurFrame() == 2)
	{
		m_bIsFired = true;
		float xDir = GetPlayer()->GetComponent<Animator>()->GetIsRotate() ? -1 : 1;
		Vec2 vBulletPos = GetPlayer()->GetPos();
		vBulletPos.y += 25;
		vBulletPos.x += 20 * xDir;

		tPlayerInfo tInfo = GetPlayer()->GetInfo();
		int iTotalBulletCount = tInfo.iBulletCountPerShot;
		int halfCount = iTotalBulletCount / 2;
		for (int i = 0; i < iTotalBulletCount; i++)
		{
			GetPlayer()->FireGun();

			float fAngleOffset = (i - halfCount) * .3f;
			Bullet* pBullet = new Bullet;
			pBullet->SetOwner(GetPlayer());
			pBullet->SetName(L"Bullet_Player");
			pBullet->SetPos(vBulletPos);
			pBullet->SetSize(Vec2(25.f, 25.f));
			pBullet->SetDir({ xDir,fAngleOffset });
			pBullet->SetSpeed(tInfo.fBulletSpeed);
			pBullet->SetPower(tInfo.iBulletPower);
			pBullet->SetKnockBackDuration(tInfo.fBulletKnockBackDuration);
			pBullet->SetKnockBackPower(tInfo.fBulletKnockBackPower);
			CreateObject(pBullet, LAYER::BULLET);
		}
	}
}

void PlayerAttackState::Enter()
{
	GetPlayer()->GetComponent<Animator>()->PlayAnimation(L"Attack", false);

	Rigidbody* pRigid = GetPlayer()->GetComponent<Rigidbody>();
	Vec2 velocity = pRigid->GetVelocity();

	pRigid->SetVelocity({ 0.f,velocity.y });
}

void PlayerAttackState::Exit()
{
	m_bIsFired = false;
}
