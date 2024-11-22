#pragma once
#include "Object.h"

class Texture;
class Background :
	public Object
{
public:
	Background();
	~Background() override;

	void Render(HDC _hdc) override;;

private:
	Texture* m_pTex;

	CLONE(Background)

public:
	void Update() override;
};

