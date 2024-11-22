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

	std::unique_ptr<tson::Map> map; // Tileson �� ��ü
	HBITMAP tileSetBitmap;     // Ÿ�ϼ� �̹��� �ڵ�
	int tileWidth = 0, tileHeight = 0; // Ÿ�� ũ��
	int mapWidth = 0, mapHeight = 0;   // �� ũ��
};

