#include "pch.h"
#include "MapManager.h"

#include "Collider.h"
#include "Core.h"
#include "Ground.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Texture.h"

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
		tson::Layer* layer = map->getLayer("Main Layer");
		tson::Tileset* tileset = map->getTileset("Tiles");
		if (layer->getType() == tson::LayerType::TileLayer)
		{
			if (!map->isInfinite())
			{
				std::map<std::tuple<int, int>, tson::Tile*> tileData = layer->getTileData();


				for (const auto& [pos, tile] : tileData)
				{

					if (tile != nullptr)
					{
						int tileId = tile->getId();

						// 타일셋 이미지에서 타일의 위치 계산
						int columns = tileset->getColumns();
						int tileWidth = tileset->getTileSize().x;
						int tileHeight = tileset->getTileSize().y;
						int tileX = ((tileId - 1) % columns) * tileWidth;
						int tileY = ((tileId - 1) / columns) * tileHeight;

						// 화면에서 타일의 렌더링 위치
						int screenX = std::get<0>(pos) * tileWidth;
						int screenY = std::get<1>(pos) * tileHeight;
						// 타일 렌더링


						Ground* ground = new Ground;
						ground->SetTexture(L"Tiles", L"Texture\\Map\\Tiles.bmp");
						ground->SetPos({ screenX,screenY });
						ground->SetPos2({ tileX ,tileY });
						ground->SetSize({ tileWidth ,tileHeight });
						GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(ground, LAYER::GROUND);

						for (const auto& object : tile->getObjectgroup().getObjects())
						{
							if (object.getClassType() == "Collider")
							{
								tson::Vector2i vec2iSize = object.getSize();
								tson::Vector2i vec2iPos = object.getPosition();
								ground->AddComponent<Collider>();
								ground->GetComponent<Collider>()->SetSize({ vec2iSize.x,vec2iSize.y });
								ground->GetComponent<Collider>()->SetOffSetPos({ vec2iPos.x,vec2iPos.y });
								break;
							}
						}
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



