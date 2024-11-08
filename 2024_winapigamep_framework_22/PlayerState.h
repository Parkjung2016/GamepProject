#pragma once
class PlayerStateMachine;
class Player;

class PlayerState
{
public:
	PlayerState(PLAYER_STATE _eState);
	virtual ~PlayerState();
private:
	PlayerStateMachine* m_pStateMachine;
	PLAYER_STATE m_eState;

public:
	PlayerStateMachine* GetStateMachine() const { return m_pStateMachine; }
	PLAYER_STATE GetType() const { return m_eState; }

	Player* GetPlayer() const;

public:
	virtual void Update() = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;

	friend class PlayerStateMachine;
};

