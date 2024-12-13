#pragma once
#include "Object.h"
class Wall :
	public Object
{
public:
	Wall();
	~Wall() override;
public:
	void Render(HDC _hdc) override;
	void Update() override;
	CLONE(Wall)
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
private:
	Texture* m_pTex;
};

