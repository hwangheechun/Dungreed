#include "stdafx.h"
#include "Weapon.h"
#include <string>

Weapon::Weapon()
{
	Init();
}

Weapon::~Weapon()
{

}

void Weapon::Init()
{
	_name = L"Weapon";
	_size = Vector2(15, 150);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;

	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));

	/*if (_player)
	{
		_position = Vector2(_player->GetPosition().x, _player->GetPosition().y);
	}*/

	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
	_direction = Vector2((float)cos(_angle), sin(_angle));
}

void Weapon::Release()
{

}

void Weapon::Update()
{
	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
	_direction = Vector2((float)cos(_angle), sin(_angle));

	if (_player)
	{
		_position = Vector2(_player->GetPosition().x, _player->GetPosition().y);
		_rect = RectMakePivot(_position, _size, Pivot::Center);
		_direction.x = _player->_cursor.x - _player->GetPosition().x;
		_direction.y = _player->_cursor.y - _player->GetPosition().y;
	}

	if (KEYMANAGER->IsStayKeyDown(0x57))	//W키
	{
#pragma region 7주차 과제_왼쪽 회전 처리
		MoveAngle(-4);
		_direction.x = cos(_angle);
		_direction.y = sin(_angle);
#pragma endregion
	}
	if (KEYMANAGER->IsStayKeyDown(0x53))	//S키
	{
#pragma region 7주차 과제_오른쪽 회전 처리
		MoveAngle(4);
		_direction.x = cos(_angle);
		_direction.y = sin(_angle);
#pragma endregion
	}
}

void Weapon::Render()
{
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	if(_angle * 180 / 3.141592 < 0)
		_D2DRenderer->RenderText(1300, 325, L"각도 : " + to_wstring(-_angle * 180 / 3.141592), 15);
	else
		_D2DRenderer->RenderText(1300, 325, L"각도 : " + to_wstring(360 -_angle * 180 / 3.141592), 15);
	if (_player)
	{
		if (_player->_isLeft)
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_player->GetPosition()) - Vector2(_player->GetSize().x / 2, 0.f), CAMERA->GetRelativeVector2(_player->GetPosition()) + Vector2(_direction.x, _direction.y));
		else 
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_player->GetPosition()) + Vector2(_player->GetSize().x / 2, 0.f), CAMERA->GetRelativeVector2(_player->GetPosition()) + _direction);
	}
}

void Weapon::MoveAngle(float angle)
{	
	_angle += angle;	//60프레임 기준 한 프레임 당, angle 값과 한 프레임 그리는 데 걸리는 시간을 곱한 값을 더해준다(개념적 이해) -> 설정한 angle만큼 커지는 순간 순간이 1초에 60번 보인다	
	//만약 deltaTime을 곱해주지 않는다면 60프레임 기준 의도한 바의 60배만큼 움직여 빠르게 보인다
	_rect.Update(_position, _size, Pivot::Center);
}


