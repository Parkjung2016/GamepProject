#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	TitleScene();
	~TitleScene() override;
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;

public:
	Object* GetPlayer() const { return m_pPlayer; }
	void RegisterPlayer(Object* _pPlayer) { m_pPlayer = _pPlayer; }

private:
	Object* m_pPlayer;
};

