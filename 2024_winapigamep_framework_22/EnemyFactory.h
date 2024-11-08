#pragma once

class Enemy;

enum class ENEMY_TYPE
{
	NORMAL,
	RANGE,

};
class EnemyFactory
{
public:
	static Enemy* CreateEnemy(ENEMY_TYPE _eType, Vec2 _vPos);

public:
	EnemyFactory();
	~EnemyFactory();
};

