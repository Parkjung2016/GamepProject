#pragma once
#include "Enums.h"

class PlayerState;
class Player;
class PlayerStateMachine
{
public:
	PlayerStateMachine();
	~PlayerStateMachine();
	int AddState(int _cpp_par_);

private:
	map<PLAYER_STATE, PlayerState*> m_mapState;
	PlayerState* m_pCurState;
	Player* m_pOwner;

public:
	void Update();

public:
	void AddState(PlayerState* _pState);
	PlayerState* GetState(PLAYER_STATE _eState);
	void SetCurState(PLAYER_STATE _eState);

	void ChangeState(PLAYER_STATE _eNextState);

	Player* GetOwner() const { return m_pOwner; }

	friend class Player;
};

