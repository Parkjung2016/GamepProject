#pragma once
#include "Object.h"

class Texture;
class Background :
	public Object
{
public:
	Background();
	~Background() override;

	void Render(HDC _hdc) override;

	void Update() override;
	void SetTexture(const wstring& _wKey, const wstring& _wPath);
	Texture* GetTexture() const { return m_pTex; }
private:
	Texture* m_pTex;
	bool m_bIsTransparent;
	Vec2 m_vParallaxFactor;
	CLONE(Background)

public:
	void SetParallaxFactor(const Vec2& vParallaxFactor) { m_vParallaxFactor = vParallaxFactor; }
	void SetTransparent() { m_bIsTransparent = true; }
};

