#pragma once
#include "Scene.h"
class GameScene :
    public Scene
{

public:
    GameScene();
    ~GameScene() override;
public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    void Update() override;
    virtual void Render(HDC _hdc) override;
public:
    Object* GetPlayer() const { return m_pPlayer; }

private:
    void RegisterPlayer(Object* _pPlayer) { m_pPlayer = _pPlayer; }

private:
    Object* m_pPlayer;


};

