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

	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
	_direction = Vector2((float)cos(_angle), sin(_angle));

	_weaponImage = IMAGEMANAGER->AddImage(L"sword", L"Resources/Sword.png");
}

void Weapon::Release()
{

}

void Weapon::Update()
{
	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
	_direction = Vector2((float)cos(_angle), sin(_angle));

	_rect = RectMakePivot(_position, _size, Pivot::Top);

	if (_player)
	{
		if (_player->_isLeft)
			_position = Vector2(_player->GetPosition().x - _player->GetSize().x / 3, _player->GetPosition().y);
		else
			_position = Vector2(_player->GetPosition().x + _player->GetSize().x / 3, _player->GetPosition().y);
		_rect = RectMakePivot(_position, _size, Pivot::Center);
		_direction.x = _player->_cursor.x - _player->GetPosition().x;
		_direction.y = _player->_cursor.y - _player->GetPosition().y;
	}

	if (KEYMANAGER->IsStayKeyDown(0x57))	//WŰ
	{
	}
	if (KEYMANAGER->IsStayKeyDown(0x53))	//SŰ
	{
	}
}

void Weapon::Render()
{
	//_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->RenderText(1400, 355, L"���� ��ġ x : " + to_wstring(_player->GetPosition().x + _player->GetSize().x / 4 + cos(_angle) * 15), 15);
	_D2DRenderer->RenderText(1400, 375, L"���� ��ġ Y : " + to_wstring(_player->GetPosition().y + sin(_angle) * 15), 15);
	_D2DRenderer->RenderText(1400, 435, L"�ޱ�: " + to_wstring(_angle), 15);
	_D2DRenderer->RenderText(1400, 395, L"�ڻ��� : " + to_wstring((float)cos(_angle) * 70), 15);
	_D2DRenderer->RenderText(1400, 415, L"���� : " + to_wstring((float)sin(_angle) * 70), 15);


		if (_angle * 180 / 3.141592 <= 0)
		{
			if (_player->_isLeft)
			{
				if (_player->_isSlashDown)
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2((float)sin(_angle) * 70, -(float)cos(_angle) * 70)));
				else
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 70, (float)cos(_angle) * 70)));
			}
			else
			{
				if (_player->_isSlashDown)
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 70, (float)cos(_angle) * 70)));
				else
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2((float)sin(_angle) * 70, -(float)cos(_angle) * 70)));
			}
		}
		else
		{
			if (_player->_isLeft)
			{
				if (_player->_isSlashDown)
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 70, (float)cos(_angle) * 70)));
				else
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2((float)sin(_angle) * 70, -(float)cos(_angle) * 70)));
			}
			else
			{
				if (_player->_isSlashDown)
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 70, (float)cos(_angle) * 70)));
				else
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)cos(_angle) * 70, (float)sin(_angle) * 70)));
			}
		}
	
		//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(cos(_angle), sin(_angle))));

	if (_angle * 180 / 3.141592 < 0)
		_D2DRenderer->RenderText(1300, 325, L"���� : " + to_wstring(-_angle * 180 / 3.141592), 15);
	else
		_D2DRenderer->RenderText(1300, 325, L"���� : " + to_wstring(360 - _angle * 180 / 3.141592), 15);
	if (_player)
	{
		if (_player->_isLeft)
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_player->GetPosition()) - Vector2(_player->GetSize().x / 5, 0.f), CAMERA->GetRelativeVector2(_player->GetPosition()) + Vector2(_direction.x, _direction.y));
		else
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_player->GetPosition()) + Vector2(_player->GetSize().x / 5, 0.f), CAMERA->GetRelativeVector2(_player->GetPosition()) + _direction);
	}
}

void Weapon::MoveAngle(float angle)
{
	_angle += angle;	//60������ ���� �� ������ ��, angle ���� �� ������ �׸��� �� �ɸ��� �ð��� ���� ���� �����ش�(������ ����) -> ������ angle��ŭ Ŀ���� ���� ������ 1�ʿ� 60�� ���δ�	
	//���� deltaTime�� �������� �ʴ´ٸ� 60������ ���� �ǵ��� ���� 60�踸ŭ ������ ������ ���δ�
	_rect.Update(_position, _size, Pivot::Center);
}


