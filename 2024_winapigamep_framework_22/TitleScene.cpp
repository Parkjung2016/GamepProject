#include "pch.h"
#include "TitleScene.h"

#include "EnemyStateMachine.h"
#include "BtnUI.h"
#include "Object.h"
#include "Player.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "EnemyFactory.h"
#include "PanelUI.h"
#include "ResourceManager.h"
#include "Ground.h"
#include "UI.h"

void ChangeScene(DWORD_PTR, DWORD_PTR);

TitleScene::TitleScene()
	: m_pPlayer(nullptr)
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	Scene::Init();
	Enemy* pEnemy = EnemyFactory::CreateEnemy(ENEMY_TYPE::NORMAL, { 250.f,500.f });

	AddObject(pEnemy, LAYER::ENEMY);

	Object* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);

	RegisterPlayer(pPlayer);

	Object* pGround = new Ground;
	pGround->SetPos({ 640.f,584.f });
	pGround->SetSize({ 200.f,60.f });
	AddObject(pGround, LAYER::GROUND);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::GROUND);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	Vec2 vResolution = { SCREEN_WIDTH, SCREEN_HEIGHT };
	GET_SINGLE(Camera)->SetLookAt(vResolution / 2.f);


	Vec2 resolution = { SCREEN_WIDTH,SCREEN_HEIGHT };

	Vec2 size = { 500.f,300.f };
	UI* pPanelUI = new PanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetSize(size);
	pPanelUI->SetPos({ resolution.x - size.x,0.f });


	BtnUI* pBtnUI = new BtnUI;
	pBtnUI->SetName(L"ChildUI");
	size = { 100.f,40.f };
	pBtnUI->SetSize(size);
	pBtnUI->SetPos({ 0.f,0.f });
	pBtnUI->SetClickedCallBack(ChangeScene, 0, 0);

	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, LAYER::UI);

	UI* pClonePanel = pPanelUI->Clone();
	Vec2 pos = pClonePanel->GetPos();
	pClonePanel->SetPos(pos + Vec2(-300.f, 0.f));
	((BtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	AddObject(pClonePanel, LAYER::UI);

	GET_SINGLE(Camera)->FadeOut(2.f);
	GET_SINGLE(Camera)->FadeIn(2.f);

}

void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
}
void TitleScene::Update()
{
	Scene::Update();
}
