#pragma once
#include "Object.h"
class Effect :
	public Object
{
public:
	Effect();
	~Effect() override;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;

public:
	void SetOffset(Vec2 _vOffset) { m_vOffset = _vOffset; }
	void SetDurationTime(const float& _fDurationTime) { m_fDurationTime = _fDurationTime; }
	void SetParent(Object* _parentObject) { m_parentObject = _parentObject; }
	void SetEffectAnimation(Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _frameCount, float _fDuration);
	void SetAlpha(float _fAlpha);
	void DestroyObject();
	Texture* GetTex() const { return m_pTex; }


private:
	float m_fDurationTime;
	float m_fCurrentDurationTime;
	Vec2 m_vOffset;
	Object* m_parentObject;
	Texture* m_pTex;

	CLONE(Effect)
};

