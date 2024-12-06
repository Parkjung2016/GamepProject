#pragma once
#include "Scene.h"
class GameScene :
	public Scene
{

public:
	GameScene();
	~GameScene() override;
public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	void Update() override;
	void LateUpdate() override;
	virtual void Render(HDC _hdc) override;
	void AfterRender() override;
public:
	Object* GetPlayer() const { return m_pPlayer; }

	void RegisterPlayer(Object* _pPlayer) { m_pPlayer = _pPlayer; }
private:
	int m_iCurrentInitCount;
	Object* m_pPlayer;


};

