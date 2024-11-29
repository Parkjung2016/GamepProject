#include "pch.h"
#include <algorithm>

#include "MapManager.h"

#include "Background.h"
#include "Collider.h"
#include "Core.h"
#include "Enemy.h"
#include "GameScene.h"
#include "Player.h"
#include "Tile.h"
#include "Scene.h"
#include "SceneManager.h"

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
		tson::Tileset* tileset = map->getTileset("Tileset");
		std::unordered_map<std::string, tson::Object> _entityObjectMap;
		for (auto object : entityLayer->getObjects())
		{
			_entityObjectMap.insert({ object.getName(),object });
		}
		if (mainLayer->getType() == tson::LayerType::TileLayer)
		{
			if (!map->isInfinite())
			{
				std::map<std::tuple<int, int>, tson::Tile*> tileData = mainLayer->getTileData();
				tson::Object playerObj = _entityObjectMap["PlayerPos"];
				Object* pPlayer = new Player;
				pPlayer->SetName(L"Player");
				pPlayer->SetPos({ playerObj.getPosition().x ,playerObj.getPosition().y });
				pPlayer->SetSize({ 100.f,100.f });
				GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pPlayer, LAYER::PLAYER);

				tson::Object enemyObj = _entityObjectMap["EnemyPos"];
				Enemy* pEnemy = new Enemy;
				pEnemy->SetName(L"Enemy");
				pEnemy->SetPos({ enemyObj.getPosition().x,enemyObj.getPosition().y });
				pEnemy->SetSize({ 100.f,100.f });

				GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pEnemy, LAYER::ENEMY);

				std::dynamic_pointer_cast<GameScene>(GET_SINGLE(SceneManager)->GetCurrentScene())->RegisterPlayer(pPlayer);
				GET_SINGLE(Camera)->SetTarget(pPlayer);

				if (middleGroundLayer || backgroundLayer)
				{
					if (middleGroundLayer)
						CreateBackground(middleGroundLayer, { .5f, 1.f }, LAYER::MIDDLEGROUND);
					if (backgroundLayer)
						CreateBackground(backgroundLayer, { .3f, 1.f }, LAYER::BACKGROUND);
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
					Tile* pTile = CreateTile(tile, screenX, screenY, tileX, tileY, tileWidth, tileHeight);
					GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pTile, LAYER::GROUND);


				}
			}
		}

	}
	else
	{
		std::cout << map->getStatusMessage();
	}
}

void MapManager::CreateBackground(tson::Layer* backgroundLayer, Vec2 vParallaxFactor, LAYER layer)
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
		vecPosition.x += (int)(vecSize.x / 2.f);
		vecPosition.y -= (int)(vecSize.y / 2.f);
		pBackground->SetPos({ (int)backgroundOffset.x + vecPosition.x ,(int)backgroundOffset.y + vecPosition.y });
		pBackground->SetSize({ vecSize.x,vecSize.y });
		pBackground->SetParallaxFactor(vParallaxFactor);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pBackground, layer);

	}
}

Tile* MapManager::CreateTile(tson::Tile* tile, int screenX, int screenY, int tileX, int tileY, int tileWidth,
	int tileHeight)
{
	Tile* pTile = new Tile;
	pTile->SetName(L"Tile");
	pTile->SetTexture(L"Tiles", L"Texture\\Map\\Tiles.bmp");
	pTile->SetPos({ screenX, screenY });
	pTile->SetPos2({ tileX, tileY });
	pTile->SetSize({ tileWidth, tileHeight });

	for (const auto& object : tile->getObjectgroup().getObjects())
	{
		if (object.getClassType() == "Collider")
		{
			tson::Vector2i vecSize = object.getSize();
			pTile->AddComponent<Collider>();
			pTile->GetComponent<Collider>()->SetSize({ vecSize.x, vecSize.y });
			break;
		}
	}
	return pTile;
}