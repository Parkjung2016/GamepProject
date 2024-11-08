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

	CLONE(Ground)
private:

	void Update() override;
public:
	void EnterCollision(Collider* _other) override;
	void StayCollision(Collider* _other) override;
	void ExitCollision(Collider* _other) override;
};

