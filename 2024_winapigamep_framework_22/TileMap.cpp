#include "pch.h"
#include "TileMap.h"

#include "EditorScene.h"
#include "MyFunc.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Tile.h"
#include "TitleScene.h"

TileMap::TileMap()
	:m_CountX(0),
	m_CountY(0),
	m_StartX(-1),
	m_StartY(-1),
	m_EndX(-1),
	m_EndY(-1)

{

}
TileMap::TileMap(const TileMap& obj)
	:Object(obj)
{
}

TileMap::~TileMap()
{
	SafeDeleteVec(m_vecTile);

}

void TileMap::Start()
{
	(std::static_pointer_cast<EditorScene>(GET_SINGLE(SceneManager)->GetCurrentScene()))->SetTileMap(this);
}

void TileMap::Update()
{
	Object::Update();

	if (!m_vecTile.empty())
	{

		Vec2	CameraPos = GET_SINGLE(Camera)->GetLookAt();
		Vec2	Resolution = Vec2(SCREEN_WIDTH, SCREEN_HEIGHT);


		SetPos(GET_SINGLE(Camera)->GetRenderPos(GetPos()));

		m_StartX = (int)(CameraPos.x / m_TileSize.x);
		m_StartY = (int)(CameraPos.y / m_TileSize.y);

		m_EndX = (int)((CameraPos.x + Resolution.x) / m_TileSize.x);
		m_EndY = (int)((CameraPos.y + Resolution.y) / m_TileSize.y);

		m_StartX = m_StartX < 0 ? 0 : m_StartX;
		m_StartY = m_StartY < 0 ? 0 : m_StartY;

		m_EndX = m_EndX >= m_CountX ? m_CountX - 1 : m_EndX;
		m_EndY = m_EndY >= m_CountY ? m_CountY - 1 : m_EndY;
	}
}

void TileMap::Render(HDC _hdc)
{
	Object::Render(_hdc);
	for (int i = m_StartY; i <= m_EndY; ++i)
	{
		for (int j = m_StartX; j <= m_EndX; ++j)
		{
			m_vecTile[i * m_CountX + j]->Render(_hdc);
		}
	}
}

void TileMap::ChangeTileOption(const Vec2& Pos, TILEOPTION Option)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile[Index]->SetTileOption(Option);
}

Tile* TileMap::GetTile(const Vec2& Pos)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return nullptr;

	return m_vecTile[Index];
}

Tile* TileMap::GetTile(int Index)
{
	return m_vecTile[Index];
}

Tile* TileMap::GetTile(int IndexX, int IndexY)
{
	return m_vecTile[IndexY * m_CountX + IndexX];

}

int TileMap::GetTileIndexX(float x)
{
	int	IndexX = (int)(x / m_TileSize.x);

	if (IndexX < 0 || IndexX >= m_CountX)
		return -1;

	return IndexX;
}

int TileMap::GetTileIndexY(float y)
{
	int	IndexY = (int)(y / m_TileSize.y);

	if (IndexY < 0 || IndexY >= m_CountY)
		return -1;

	return IndexY;
}

int TileMap::GetTileIndex(const Vec2& Pos)
{
	int	IndexX = GetTileIndexX(Pos.x);
	int	IndexY = GetTileIndexY(Pos.y);

	if (IndexX == -1 || IndexY == -1)
		return -1;

	return IndexY * m_CountX + IndexX;
}

bool TileMap::CreateTile(int iCountX, int iCountY, const Vec2& vTileSize)
{
	m_CountX = iCountX;
	m_CountY = iCountY;
	m_TileSize = vTileSize;

	SafeDeleteVec(m_vecTile);


	for (int i = 0; i < m_CountY; ++i)
	{
		for (int j = 0; j < m_CountX; ++j)
		{
			Tile* tile = new Tile;

			tile->m_Owner = this;

			Vec2	Pos = m_TileSize * Vec2((float)j, (float)i);

			tile->SetTileInfo(Pos, m_TileSize, j, i, i * m_CountX + j,
				m_TileTexture);

			m_vecTile.push_back(tile);
		}
	}

	return false;
}

void TileMap::SetTileTexture(const wstring& name)
{
	m_TileTexture = GET_SINGLE(ResourceManager)->TextureFind(name);

	size_t	Size = m_vecTile.size();

	for (size_t i = 0; i < Size; ++i)
	{
		m_vecTile[i]->m_Texture = m_TileTexture;
	}
}

void TileMap::SetTileFrame(const Vec2& Pos, const Vec2& Start, const Vec2& End)
{
	int	Index = GetTileIndex(Pos);

	if (Index == -1)
		return;

	m_vecTile[Index]->SetFrame(Start, End);

}

