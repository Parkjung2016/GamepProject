#pragma once
#include "tileson.hpp"
class MapManager
{
	DECLARE_SINGLE(MapManager);

public:
	~MapManager();

	void Init();
	void LoadMap(const std::wstring& filePath);

private:
	wchar_t m_resourcePath[255] = {};

	std::unique_ptr<tson::Map> map; // Tileson 맵 객체
	HBITMAP tileSetBitmap;     // 타일셋 이미지 핸들
	int tileWidth = 0, tileHeight = 0; // 타일 크기
	int mapWidth = 0, mapHeight = 0;   // 맵 크기
};

