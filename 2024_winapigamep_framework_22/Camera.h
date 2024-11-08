#pragma once
#include "Define.h"
#include "Vec2.h"

class Object;
class Texture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffect
{
	CAM_EFFECT eEffect;
	float fDuration;
	float fCurTime;
};
class Camera
{
	DECLARE_SINGLE(Camera)
private:
	Vec2 m_vLookAt;
	Vec2 m_vCurLookAt;
	Vec2 m_vPrevLookAt;
	Object* m_pTargetObj;
	Vec2 m_vDiff;

	float m_fTime;
	float m_fSpeed;
	float m_fAccTime;

	list<tCamEffect> m_listCamEffect;

	Texture* m_pVeilTex;

public:
	void SetLookAt(Vec2 _vLook)
	{
		m_vLookAt = _vLook;
		float moveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = moveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(Object* _pTarget) { m_pTargetObj = _pTarget; }
	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) const { return _vObjPos - m_vDiff; };
	Vec2 GetRealPos(Vec2 _vRenderPos) const { { return _vRenderPos + m_vDiff; } }


	void FadeIn(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_IN;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);
		if (0.f == _fDuration)
			assert(nullptr);
	}
	void FadeOut(float _fDuration)
	{
		tCamEffect ef = {};
		ef.eEffect = CAM_EFFECT::FADE_OUT;
		ef.fDuration = _fDuration;
		ef.fCurTime = 0.f;

		m_listCamEffect.push_back(ef);

		if (0.f == _fDuration)
			assert(nullptr);
	}
public:
	void Init();
	void Update();
	void Render(HDC _hdc);

private:
	void CalDiff();
};
