#include "pch.h"
#include "Tile.h"

#include "Camera.h"
#include "SceneManager.h"
#include "Texture.h"

Tile::Tile()
	:m_Option(TILEOPTION::NORMAL),
	m_Owner(nullptr),
	m_IndexX(0),
	m_IndexY(0),
	m_Index(0),
	m_TileFrame(0)
{
}

Tile::~Tile()
{
}

void Tile::SetTileInfo(const Vec2& Pos, const Vec2& Size, int IndexX, int IndexY, int Index, Texture* Texture)
{
	m_Texture = Texture;
	m_Pos = Pos;
	m_Size = Size;
	m_IndexX = IndexX;
	m_IndexY = IndexY;
	m_Index = Index;
}

void Tile::SetFrame(const Vec2& Start, const Vec2& End)
{
	m_StartFrame = Start;
	m_EndFrame = End;
}

void Tile::Render(HDC _hDC)
{
	Vec2	Pos;
	Pos = GET_SINGLE(Camera)->GetRenderPos(Pos);
	if (m_Texture)
	{
		//if (m_Texture->GetTextureType() == ETextureType::Sprite)
		//{
		StretchBlt(_hDC, (int)Pos.x, (int)Pos.y,
			(int)m_Size.x, (int)m_Size.y, m_Texture->GetTexDC(),
			(int)m_StartFrame.x, (int)m_StartFrame.y,
			(int)m_Size.x, (int)m_Size.y,
			SRCCOPY);
		//}

		//else
		//{
		//	StretchBlt(_hDC, (int)Pos.x, (int)Pos.y,
		//		(int)m_Size.x, (int)m_Size.y,
		//		m_Texture->GetDC(m_TileFrame),
		//		0, 0,
		//		(int)m_Size.x, (int)m_Size.y,
		//		SRCCOPY);
		//}
	}

}
