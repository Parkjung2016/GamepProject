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

	//Ÿ�� �̹���
	Texture* m_Texture;

public://��ü���� Ÿ�� ���� ����
	void SetTileInfo(const Vec2& Pos, const Vec2& Size,
		int IndexX, int IndexY, int Index, Texture* Texture);


private://Ÿ���� �� �� �ִ� ������ ���� ������
	TILEOPTION	m_Option;
public:
	TILEOPTION GetOption()	const { return m_Option; }
	void SetTileOption(TILEOPTION Option) { m_Option = Option; }


private://��ġ�� ũ��.
	Vec2		m_Pos;
	Vec2		m_Size;
public:
	const Vec2& GetPos()	const { return m_Pos; }
	const Vec2& GetSize()	const { return m_Size; }


private://Ÿ���� ��� ��ȣ
	int			m_IndexX;
	int			m_IndexY;
	int			m_Index;


private://��������Ʈ �̹��� ��� ��ġ ����
	int			m_TileFrame;
	Vec2		m_StartFrame;
	Vec2		m_EndFrame;
public:
	void SetFrame(const Vec2& Start, const Vec2& End);



public:
	void Render(HDC _hDC);
};

