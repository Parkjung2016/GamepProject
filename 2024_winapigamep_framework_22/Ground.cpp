#include "pch.h"
#include "Ground.h"

#include "Collider.h"

Ground::Ground()
{
	AddComponent<Collider>();
}

Ground::~Ground()
{
}

void Ground::Start()
{
	GetComponent<Collider>()->SetSize(GetSize());

}

void Ground::Render(HDC _hdc)
{
}

void Ground::EnterCollision(Collider* _other)
{

}


