#pragma once
#include "tileson.hpp"

class Tile;
class MapManager
{
	DECLARE_SINGLE(MapManager);

public:
	~MapManager();

	void Init();
	void LoadMap(const std::wstring& filePath);

private:
	void CreateBackground(tson::Layer* backgroundLayer, Vec2 vParallaxFactor, LAYER layer, bool bIsTransparent);
	void CreatePlayer(const Vec2& vPos);
	void CreateEnemy(const Vec2& vPos);
	void CreateBoss(const Vec2& vPos);
	void CreateTile(tson::Tile* tile, int screenX, int screenY, int tileX, int tileY, int tileWidth, int tileHeight);
private:
	wchar_t m_resourcePath[255] = {};

	std::unique_ptr<tson::Map> map; // Tileson 맵 객체
	HBITMAP tileSetBitmap;     // 타일셋 이미지 핸들
	int tileWidth = 0, tileHeight = 0; // 타일 크기
	int mapWidth = 0, mapHeight = 0;   // 맵 크기
};

