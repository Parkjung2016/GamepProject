#pragma once
#include "Object.h"

class Texture;
class Tile :
	public Object
{
public:
	Tile();
	~Tile() override;
public:
	void Start() override;
	void Render(HDC _hdc) override;

	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
	CLONE(Tile)
private:
	void Update() override;

public:
	void SetTransparent(bool _bIsTransparent) { m_bIsTransparent = _bIsTransparent; }
	void SetTexture(const wstring& _wKey, const wstring& _wPath);
	void SetPos2(const Vec2& _vPos) { m_vPos2 = _vPos; }
	void SetTileId(const int& _iTileId) { m_iTileId = _iTileId; }
	Texture* GetTex() const { return m_pTex; }
	Vec2 GetPos2() const { return m_vPos2; }
private:
	bool m_bIsTransparent;

	int m_iTileId;
	Texture* m_pTex;
	Vec2 m_vPos2;
};

