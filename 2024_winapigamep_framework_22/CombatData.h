#pragma once
#include "Vec2.h"
class Object;
class CombatData
{
public:
	Object* pDealer;
	int iDamage;
	Vec2 vKnockBackDir;
	float fKnockBackPower;
	float fKnockBackDuration;
};

