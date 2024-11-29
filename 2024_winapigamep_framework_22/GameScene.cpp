#include "pch.h"
#include "GameScene.h"

#include "Background.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "Tile.h"
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


	//Enemy* pEnemy = new Enemy;
	//pEnemy->SetPos({ SCREEN_WIDTH / 2.f,0.f });
	//pEnemy->SetSize({ 100.f,100.f });

	//AddObject(pEnemy, LAYER::ENEMY);


	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::GROUND);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::GROUND);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::BULLET, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	Vec2 vResolution = { SCREEN_WIDTH, SCREEN_HEIGHT };
	GET_SINGLE(Camera)->SetPrevShakeLookAt(vResolution / 2.f);

	//GET_SINGLE(Camera)->FadeOut(2.f);
	//GET_SINGLE(Camera)->FadeIn(2.f);

	Scene::Init();

}

void GameScene::Update()
{
	Scene::Update();

}

void GameScene::Render(HDC _hdc)
{

	Scene::Render(_hdc);
}
