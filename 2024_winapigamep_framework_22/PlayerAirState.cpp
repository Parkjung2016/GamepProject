#include "pch.h"
#include "PlayerAirState.h"

#include "Animator.h"
#include "Gravity.h"
#include "Player.h"
#include "Rigidbody.h"

PlayerAirState::PlayerAirState(PLAYER_STATE _eState) : PlayerState(_eState)
{
}

PlayerAirState::~PlayerAirState()
{
}

void PlayerAirState::Update()
{
	Player* player = GetPlayer();
	Rigidbody* pRigid = player->GetComponent<Rigidbody>();

	int iInput = player->GetMoveInput();
	tPlayerInfo info = player->GetInfo();
	if (iInput != 0)
	{
		player->GetComponent<Animator>()->SetIsRotate(iInput == -1);
	}
	pRigid->AddForce({ iInput * info.fAirControl,0.f });
}

void PlayerAirState::Enter()
{
	GetPlayer()->GetComponent<Gravity>()->SetCanGravity(true);

}

void PlayerAirState::Exit()
{

}
