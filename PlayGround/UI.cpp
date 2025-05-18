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
	_size = Vector2(300, 20);
	_rect = RectMakePivot(_position, _size, Pivot::Center);	// 히트박스
	_active = true;

	
	_playerHP = IMAGEMANAGER->AddImage(L"playerHP", L"Resources/PlayerHP.png");
	_dashCount = IMAGEMANAGER->AddImage(L"dashCount", L"Resources/DashCount_2.png");
	_mouseCursor = IMAGEMANAGER->AddImage(L"cursor", L"Resources/Cursor.png");
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
}