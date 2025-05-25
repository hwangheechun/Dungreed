#include "stdafx.h"
#include "UI.h"
#include <string>

UI::UI()
{
	Init();
}

UI::~UI()
{
}

void UI::Init()
{
	_name = L"UI";
	_position = Vector2(260, 70);
	_size = Vector2(340, 70);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;
	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	
	_playerHP = IMAGEMANAGER->AddImage(L"playerHP", L"Resources/PlayerHP.png");
	_dashCount = IMAGEMANAGER->AddImage(L"dashCount", L"Resources/DashCount_2.png");
	_mouseCursor = IMAGEMANAGER->AddImage(L"cursor", L"Resources/Cursor.png");

	_HPGauge = RectMakePivot(_position + Vector2(65, 0), _size, Pivot::Center);
	//_HP = RectMakePivot(Vector2(500, 80), Vector2(800.f, 80.f), Pivot::Center);
}

void UI::Release()
{
}

void UI::Update()
{
	
}

void UI::Render()
{
	//_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	//_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	_playerHP->Render(_position);
	_dashCount->Render(_position + Vector2(-178, 75));
	_mouseCursor->Render(Vector2((float)_ptMouse.x, (float)_ptMouse.y));

	FloatRect _HPBar{ _HPGauge.left, _HPGauge.top, _HPGauge.left + _HPGauge.GetWidth() * _player->_hp / _player->_maxHP, _HPGauge.bottom };

	_D2DRenderer->FillRectangle(_HPBar, D2DRenderer::DefaultBrush::Red);
	_D2DRenderer->DrawRectangle(_HPGauge, D2DRenderer::DefaultBrush::Black, 1.0f);
	
}