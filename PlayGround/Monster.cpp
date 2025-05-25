#include "stdafx.h"
#include "Monster.h"

Monster::Monster()
{
	Init();
}

Monster::~Monster()
{
}

void Monster::Init()
{
	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
}

void Monster::Release()
{
}

void Monster::Update()
{
}

void Monster::Render()
{
}

bool Monster::IsCollide(FloatRect _rect, FloatRect _rect2)
{
	if (_rect.right > _rect2.left && _rect.left < _rect2.right && _rect.top < _rect2.bottom && _rect.bottom > _rect2.top)
		return true;
	else return false;
}
