#include "pch.h"
#include "Bullet.h"

#include "Animator.h"
#include "ResourceManager.h"
#include "TimeManager.h"

Bullet::Bullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Bullet.bmp");
	this->AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"Fire", m_pTex, Vec2(112.f, 144.f),
		Vec2(16.f, 16.f), Vec2(16.f, 0.f), 4, 0.1f);

	GetComponent<Animator>()->PlayAnimation(L"Fire", true);

}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos += m_vDir * m_fSpeed * fDT;
	SetPos(vPos);
}

void Bullet::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Bullet::EnterCollision(Collider* _other)
{
}
