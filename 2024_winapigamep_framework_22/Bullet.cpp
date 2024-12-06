#include "pch.h"
#include "Bullet.h"

#include "Animator.h"
#include "Collider.h"
#include "EffectManager.h"
#include "EventManager.h"
#include "Interfaces.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "MyFunc.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextUI.h"
#include "Player.h"

Bullet::Bullet()
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Bullet.bmp");
	this->AddComponent<Animator>();
	this->AddComponent<Collider>();
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

	if (m_fCurrentDestroyTime <= 6)
	{
		m_fCurrentDestroyTime += fDT;
	}
	else
	{
		tEvent evt;
		evt.eveType = EVENT_TYPE::DELETE_OBJECT;
		evt.lParam = (DWORD_PTR)this;
		GET_SINGLE(EventManager)->AddEvent(evt);
	}
}

void Bullet::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Bullet::EnterCollision(Collider* _other)
{
	IDamageable* iDamageable = _other->GetOwner()->GetComponent<IDamageable>();
	if (iDamageable)
	{
		Vec2 vOtherPos = _other->GetOwner()->GetPos();

		Vec2 vPos = GetPos();
		Vec2 dis = (vOtherPos - vPos);
		dis.y = -10;
		Vec2 vKnockBackDir = dis.Normalize();
		CombatData combatData
		{
			m_pPlayer,
			m_iPower,
			vKnockBackDir,
			m_fKnockBackPower,
			m_fKnockBackDuration
		};
		TextUI* pTextUI = new TextUI(true, 25);
		Vec2 vTextPos = vPos;
		vTextPos.x += (rand() % 59 - 29);
		vTextPos.y -= (rand() % 29 + 10);
		pTextUI->SetPos(vTextPos);
		pTextUI->SetText(L"+" + std::to_wstring(combatData.iDamage));
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pTextUI, LAYER::UI);

		iDamageable->ApplyDamage(combatData);
		GET_SINGLE(EffectManager)->SpawnEffect(vPos, { 192.f,288.f }, { 16.f,16.f }, { 16.f,0.f }, 6, 2);
		tEvent evt;
		evt.eveType = EVENT_TYPE::DELETE_OBJECT;
		evt.lParam = (DWORD_PTR)this;
		GET_SINGLE(EventManager)->AddEvent(evt);
	}
}

