#include "pch.h"
#include "MapManager.h"

#include "Collider.h"
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
	tson::Tileson tileson;
	map = tileson.parse(path);
	if (map->getStatus() == tson::ParseStatus::OK)
	{
		std::cout << "Map loaded successfully!" << std::endl;
		std::cout << "Map size: " << map->getSize().x << "x" << map->getSize().y << std::endl;
	}
	else
	{
		std::cerr << "Failed to parse map. Error: " << map->getStatusMessage() << std::endl;
	}
	tileWidth = 32;
	tileHeight = 32;

	for (auto& layer : map->getLayers()) {
		if (layer.getType() == tson::LayerType::TileLayer) {
			for (auto& [pos, tile] : layer.getTileData()) {
				if (tile != nullptr) {
					int tileId = tile->getId();



					Ground* pGround = new Ground;
					pGround->SetName(L"Ground");
					pGround->SetTexture(L"Ground", L"Texture\\Map\\Tiles.bmp");
					int tilesetWidth = pGround->GetTex()->GetWidth();
					int tilesetCols = tilesetWidth / tileWidth;
					int srcX = (tileId - 1) % tilesetCols * tileWidth;
					int srcY = (tileId - 1) / tilesetCols * tileHeight;

					// 화면에 렌더링할 위치 계산
					int destX = std::get<0>(pos) * tileWidth;
					int destY = std::get<1>(pos) * tileHeight;
					pGround->SetPos({ destX,destY });
					pGround->SetSize({ tileWidth,tileHeight });
					pGround->SetPos2({ srcX ,srcY });
					pGround->SetTileId(tileId);
					for (auto& object : tile->getObjectgroup().getObjects()) {
						float colliderX = destX + object.getPosition().x;
						float colliderY = destY + object.getPosition().y;
						float colliderWidth = object.getSize().x;
						float colliderHeight = object.getSize().y;
						pGround->GetComponent<Collider>()->SetSize({ colliderWidth, colliderHeight });
						pGround->GetComponent<Collider>()->SetOffSetPos({ 15,15});


					}
					GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pGround, LAYER::GROUND);
				}
			}
		}
	}

}

