#pragma once
#include "Object.h"
class Ground :
	public Object
{
public:
	Ground();
	~Ground() override;
public:
	void Start() override;
	void Render(HDC _hdc) override;
	void EnterCollision(Collider* _other) override;

	CLONE(Ground)
private:
};

