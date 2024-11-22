#pragma once
#include "Enums.h"
#include "Object.h"
class Texture;
class Object;
class  Tile;

class TileMap :
	public Object
{
	friend class Scene;
public:
	TileMap();
	TileMap(const TileMap& obj);
	~TileMap() override;
public:
	void Start() override;
	void Update() override;
	void Render(HDC _hdc) override;

private:
	vector< Tile*>	m_vecTile;
	Texture* m_TileTexture;
	int		m_CountX;
	int		m_CountY;
	Vec2	m_TileSize;
	int		m_StartX;
	int		m_StartY;
	int		m_EndX;
	int		m_EndY;



public:
	int GetCountX()	const { return m_CountX; }
	int GetCountY()	const { return m_CountY; }


public:
	void ChangeTileOption(const Vec2& Pos, TILEOPTION Option);
	void SetTileFrame(const Vec2& Pos, const Vec2& Start,
		const Vec2& End);
	Tile* GetTile(const Vec2& Pos);
	Tile* GetTile(int Index);
	Tile* GetTile(int IndexX, int IndexY);
	int GetTileIndexX(float x);
	int GetTileIndexY(float y);
	int GetTileIndex(const Vec2& Pos);


public:

	bool CreateTile(int iCountX, int iCountY, const Vec2& vTileSize);
	void SetTileTexture(const wstring& name);

	CLONE(TileMap)

};

