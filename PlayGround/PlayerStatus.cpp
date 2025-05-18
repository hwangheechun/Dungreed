#include "stdafx.h"
#include "PlayerStatus.h"

PlayerStatus::PlayerStatus()
{
	Init();
}

PlayerStatus::~PlayerStatus()
{

}

void PlayerStatus::Init()
{
	_name = L"UI";
	_position = Vector2(WINSIZEX - 100, 50);
	_size = Vector2(200, 85);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;


	_playerHP = IMAGEMANAGER->AddImage(L"playerHP", L"Resources/PlayerHP.png");
}

void PlayerStatus::Release()
{

}

void PlayerStatus::Update()
{

}

void PlayerStatus::Render()
{
	_playerHP->Render(_position);
}
