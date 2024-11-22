#pragma once
class Texture;
class Scene;
class TileMap;
class Tile
{
	friend  TileMap;

public:
	Tile();
	~Tile();

private:
	TileMap* m_Owner;

	//타일 이미지
	Texture* m_Texture;

public://전체적인 타일 정보 설정
	void SetTileInfo(const Vec2& Pos, const Vec2& Size,
		int IndexX, int IndexY, int Index, Texture* Texture);


private://타일이 갈 수 있는 곳인지 없는 곳인지
	TILEOPTION	m_Option;
public:
	TILEOPTION GetOption()	const { return m_Option; }
	void SetTileOption(TILEOPTION Option) { m_Option = Option; }


private://위치와 크기.
	Vec2		m_Pos;
	Vec2		m_Size;
public:
	const Vec2& GetPos()	const { return m_Pos; }
	const Vec2& GetSize()	const { return m_Size; }


private://타일의 행렬 번호
	int			m_IndexX;
	int			m_IndexY;
	int			m_Index;


private://스프라이트 이미지 출력 위치 저장
	int			m_TileFrame;
	Vec2		m_StartFrame;
	Vec2		m_EndFrame;
public:
	void SetFrame(const Vec2& Start, const Vec2& End);



public:
	void Render(HDC _hDC);
};

