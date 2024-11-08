#pragma once
#include "Object.h"

class Texture;
class PlayerStateMachine;

struct tPlayerInfo
{
	float fWalkSpeed;
};
class Player : public Object
{
public:
	Player();
	virtual ~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void SetInfo(const tPlayerInfo& _info) { m_tInfo = _info; }
	void UpdateGravity();
private:
	int m_iInput;
	bool m_bIsPressInput;
	Texture* m_pTex;
	PlayerStateMachine* m_pStateMachine;
	tPlayerInfo m_tInfo;

public:
	void SetStateMachine(PlayerStateMachine* _stateMachine);
	int GetInput() const { return m_iInput; }
	bool GetIsPressInput() const { return m_bIsPressInput; }
	const tPlayerInfo& GetInfo() const { return m_tInfo; }
	CLONE(Player)
};
