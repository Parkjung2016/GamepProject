#include "pch.h"
#include "GameScene.h"

#include "Background.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Ground.h"
#include "InputManager.h"
#include "MapManager.h"
#include "Player.h"
#include "ResourceManager.h"

GameScene::GameScene()
	: m_pPlayer(nullptr)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init()
{
	GET_SINGLE(MapManager)->LoadMap(L"Json\\Tileset.json"); // ¸Ê ·Îµå

	Background* pBackground = new Background;
	pBackground->SetPos({ SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 });
	pBackground->SetSize({ 0,0 });
	AddObject(pBackground, LAYER::BACKGROUND);



	//Enemy* pEnemy = new Enemy;
	//pEnemy->SetPos({ SCREEN_WIDTH / 2.f,0.f });
	//pEnemy->SetSize({ 100.f,100.f });

	//AddObject(pEnemy, LAYER::ENEMY);

	Object* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,-100.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);

	RegisterPlayer(pPlayer);

	//Object* pGround = new Ground;
	//pGround->SetName(L"Ground");
	//pGround->SetPos({ 640.f,600.f });
	//pGround->SetSize({ 1500.f,60.f });
	//AddObject(pGround, LAYER::GROUND);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::GROUND);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::GROUND);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	Vec2 vResolution = { SCREEN_WIDTH, SCREEN_HEIGHT };
	GET_SINGLE(Camera)->SetLookAt({ 256,544 });
	GET_SINGLE(Camera)->SetPrevShakeLookAt(vResolution / 2.f);

	GET_SINGLE(Camera)->FadeOut(2.f);
	GET_SINGLE(Camera)->FadeIn(2.f);

	Scene::Init();

}

void GameScene::Update()
{
	Scene::Update();

	//if (GET_KEYDOWN(KEY_TYPE::R))
	//{
	//	GET_SINGLE(Camera)->SetLookAt(GET_SINGLE(InputManager)->GetMousePos());
	//}
}

void GameScene::Render(HDC _hdc)
{

	Scene::Render(_hdc);
}
