#pragma once
class Boss;
class BossState;
class BossStateMachine
{
private:
	map<BOSS_STATE, BossState*> m_mapState;
	BossState* m_pCurState;
	Boss* m_pOwner;
	bool m_bCanChangeState;
public:
	void Update();

public:
	void AddState(BossState* _pState);
	BossState* GetState(BOSS_STATE _eState);
	void SetCurState(BOSS_STATE _eState);
	void ChangeState(BOSS_STATE _eNextState);
	void SetCanChangeState(bool _b) { m_bCanChangeState = _b; }
	Boss* GetOwner() const { return m_pOwner; }
public:
	BossStateMachine();
	~BossStateMachine();

	friend class Boss;
};

