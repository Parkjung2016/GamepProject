#include "pch.h"

#include "MapManager.h"

#include "Background.h"
#include "Boss.h"
#include "Collider.h"
#include "Core.h"
#include "Enemy.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Wall.h"

MapManager::~MapManager()
{
}

void MapManager::Init()
{

	::GetCurrentDirectory(255, m_resourcePath);
	wcscat_s(m_resourcePath, 255, L"\\Resource\\");
}

void MapManager::LoadMap(const std::wstring& filePath) {

	wstring path = m_resourcePath;
	path += filePath;
	tson::Tileson t;
	std::unique_ptr<tson::Map> map = t.parse(path);

	if (map->getStatus() == tson::ParseStatus::OK)
	{
		tson::Layer* mainLayer = map->getLayer("Main Layer");
		tson::Layer* entityLayer = map->getLayer("Entity Layer");
		tson::Layer* backgroundLayer = map->getLayer("Background Layer");
		tson::Layer* middleGroundLayer = map->getLayer("MiddleGround Layer");
		tson::Layer* underGroundLayer = map->getLayer("UnderGround Layer");
		tson::Layer* wallLayer = map->getLayer("Wall Layer");
		tson::Tileset* tileset = map->getTileset("Tileset");
		if (mainLayer->getType() == tson::LayerType::TileLayer)
		{
			if (!map->isInfinite())
			{
				std::map<std::tuple<int, int>, tson::Tile*> tileData = mainLayer->getTileData();

				auto wallLayerObjects = wallLayer->getObjects();


				for (auto& obj : wallLayerObjects)
				{
					Wall* pWall = new Wall;
					wstring name = wstring(obj.getName().begin(), obj.getName().end());
					pWall->SetName(name);

					auto vecPosition = obj.getPosition();
					auto vecSize = obj.getSize();
					pWall->SetPos({ (int)vecPosition.x ,(int)vecPosition.y });
					pWall->SetSize({ vecSize.x,vecSize.y });

					pWall->AddComponent<Collider>()->SetSize({ vecSize.x,vecSize.y });
					GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pWall, LAYER::TILE);
				}
				if (middleGroundLayer || backgroundLayer || underGroundLayer)
				{
					if (middleGroundLayer)
						CreateBackground(middleGroundLayer, { .5f, 1.f }, LAYER::MIDDLEGROUND, true);
					if (backgroundLayer)
						CreateBackground(backgroundLayer, { .3f, 1.f }, LAYER::BACKGROUND, true);
					if (underGroundLayer)
					{
						CreateBackground(underGroundLayer, { 1.f,1.f }, LAYER::BACKGROUND, false);
					}
				}

				const int columns = tileset->getColumns();
				const int tileWidth = tileset->getTileSize().x;
				const int tileHeight = tileset->getTileSize().y;
				for (const auto& [pos, tile] : tileData)
				{
					if (!tile) continue;
					int tileId = tile->getId();

					int tileX = ((tileId - 1) % columns) * tileWidth;
					int tileY = ((tileId - 1) / columns) * tileHeight;

					int screenX = std::get<0>(pos) * tileWidth;
					int screenY = std::get<1>(pos) * tileHeight;

					screenX += (int)(tileWidth / 2.f);
					screenY += (int)(tileHeight / 2.f);
					CreateTile(tile, screenX, screenY, tileX, tileY, tileWidth, tileHeight);


				}

				for (auto entityObj : entityLayer->getObjects())
				{
					Vec2 vPos = { entityObj.getPosition().x,entityObj.getPosition().y };

					if (entityObj.getClassType() == "EnemyPos")
					{
						CreateEnemy(vPos);
					}
					else if (entityObj.getClassType() == "PlayerPos")
					{

						CreatePlayer(vPos);
					}
					else if (entityObj.getClassType() == "BossPos")
					{
						CreateBoss(vPos);
					}
				}

			}
		}

	}
	else
	{
		std::cout << map->getStatusMessage();
	}
}

void MapManager::CreateBackground(tson::Layer* backgroundLayer, Vec2 vParallaxFactor, LAYER layer, bool bIsTransparent)
{
	auto backgroundObjects = backgroundLayer->getObjects();
	auto backgroundOffset = backgroundLayer->getOffset();


	for (auto& obj : backgroundObjects)
	{
		Background* pBackground = new Background;
		wstring name = wstring(obj.getName().begin(), obj.getName().end());
		pBackground->SetName(name);
		pBackground->SetTexture(name, L"Texture\\Map\\" + name + L".bmp");

		auto vecPosition = obj.getPosition();
		auto vecSize = obj.getSize();
		pBackground->SetPos({ (int)backgroundOffset.x + vecPosition.x ,(int)backgroundOffset.y + vecPosition.y });
		pBackground->SetSize({ vecSize.x,vecSize.y });
		pBackground->SetParallaxFactor(vParallaxFactor);
		if (bIsTransparent)
			pBackground->SetTransparent();
		if (obj.getClassType() == "Collider")
		{
			pBackground->AddComponent<Collider>()->SetSize({ vecSize.x,vecSize.y });
		}
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pBackground, layer);
	}
}

void MapManager::CreatePlayer(const Vec2& vPos)
{
	Object* pPlayer = new Player;
	pPlayer->SetName(L"Player");
	pPlayer->SetPos(vPos);
	pPlayer->SetSize({ 100.f,100.f });
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pPlayer, LAYER::PLAYER);

	std::dynamic_pointer_cast<GameScene>(GET_SINGLE(SceneManager)->GetCurrentScene())->RegisterPlayer(pPlayer);
	GET_SINGLE(Camera)->SetTarget(pPlayer);
}

void MapManager::CreateEnemy(const Vec2& vPos)
{
	Enemy* pEnemy = new Enemy;
	pEnemy->SetName(L"Enemy");
	pEnemy->SetPos(vPos);
	pEnemy->SetSize({ 100.f,100.f });

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pEnemy, LAYER::ENEMY);
}

void MapManager::CreateBoss(const Vec2& vPos)
{
	Boss* pBoss = new Boss;
	pBoss->SetName(L"Boss");
	pBoss->SetPos(vPos);
	pBoss->SetSize({ 100.f,100.f });

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pBoss, LAYER::BOSS);
}

void MapManager::CreateTile(tson::Tile* tile, int screenX, int screenY, int tileX, int tileY, int tileWidth,
	int tileHeight)
{
	Tile* pTile = new Tile;
	pTile->SetName(L"Tile");
	pTile->SetTexture(L"Tiles", L"Texture\\Map\\Tiles.bmp");
	pTile->SetPos({ screenX, screenY });
	pTile->SetPos2({ tileX, tileY });
	pTile->SetSize({ tileWidth, tileHeight });
	pTile->SetTransparent(true);

	for (const auto& object : tile->getObjectgroup().getObjects())
	{
		if (object.getClassType() == "Collider")
		{
			tson::Vector2i vecSize = object.getSize();
			pTile->AddComponent<Collider>();
			pTile->GetComponent<Collider>()->SetSize({ vecSize.x, vecSize.y });
			pTile->SetTransparent(false);

			break;
		}

	}

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pTile, LAYER::TILE);
}
