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

	if (KEYMANAGER->IsStayKeyDown(0x57))	//WŰ
	{
#pragma region 7���� ����_���� ȸ�� ó��
		MoveAngle(-4);
		_direction.x = cos(_angle);
		_direction.y = sin(_angle);
#pragma endregion
	}
	if (KEYMANAGER->IsStayKeyDown(0x53))	//SŰ
	{
#pragma region 7���� ����_������ ȸ�� ó��
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
		_D2DRenderer->RenderText(1300, 325, L"���� : " + to_wstring(-_angle * 180 / 3.141592), 15);
	else
		_D2DRenderer->RenderText(1300, 325, L"���� : " + to_wstring(360 -_angle * 180 / 3.141592), 15);
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
	_angle += angle;	//60������ ���� �� ������ ��, angle ���� �� ������ �׸��� �� �ɸ��� �ð��� ���� ���� �����ش�(������ ����) -> ������ angle��ŭ Ŀ���� ���� ������ 1�ʿ� 60�� ���δ�	
	//���� deltaTime�� �������� �ʴ´ٸ� 60������ ���� �ǵ��� ���� 60�踸ŭ ������ ������ ���δ�
	_rect.Update(_position, _size, Pivot::Center);
}


