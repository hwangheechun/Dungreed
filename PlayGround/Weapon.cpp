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
	_active = false;

	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));

	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
	_direction = Vector2((float)cos(_angle), sin(_angle));

	_weaponType = WeaponType::SWORD;
	IMAGEMANAGER->AddImage(L"sword", L"Resources/Sword.png");
	IMAGEMANAGER->AddImage(L"gatlinggun", L"Resources/GatlingGun.png");
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
		_direction.x = _player->_cursor.x - CAMERA->GetRelativeVector2(_player->GetPosition()).x;
		_direction.y = _player->_cursor.y - CAMERA->GetRelativeVector2(_player->GetPosition()).y;
	}

	if (KEYMANAGER->IsStayKeyDown(0x57))	//W키
	{
	}
	if (KEYMANAGER->IsStayKeyDown(0x53))	//S키
	{
	}

	switch (_weaponType)
	{
		case WeaponType::SWORD:
			_weaponImage = IMAGEMANAGER->FindImage(L"sword");
			break;
		case WeaponType::GATLINGGUN:
			_weaponImage = IMAGEMANAGER->FindImage(L"gatlinggun");
			break;
	}
}

void Weapon::Render()
{
	//_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->RenderText(1400, 355, L"무기 위치 x : " + to_wstring(_player->GetPosition().x + _player->GetSize().x / 4 + cos(_angle) * 15), 15);
	_D2DRenderer->RenderText(1400, 375, L"무기 위치 Y : " + to_wstring(_player->GetPosition().y + sin(_angle) * 15), 15);
	_D2DRenderer->RenderText(1400, 435, L"앵글: " + to_wstring(_angle), 15);
	_D2DRenderer->RenderText(1400, 395, L"코사인 : " + to_wstring((float)cos(_angle)), 15);
	_D2DRenderer->RenderText(1400, 415, L"사인 : " + to_wstring((float)sin(_angle)), 15);
	_D2DRenderer->RenderText(1400, 485, L"웨펀타입 : " + to_wstring((int)_weaponType), 15);

	switch (_weaponType)
	{
	case WeaponType::SWORD:
		if (_angle * 180 / 3.141592 <= 0)
		{
			if (_player->_isLeft)
			{
				if (_player->_isSlashDown)
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2((float)sin(_angle) * 70, -(float)cos(_angle) * 70)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
				else
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 40, (float)cos(_angle) * 40)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
			}
			else //여기를 기준으로 보죠
			{
				if (_player->_isSlashDown)
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2((float)sin(_angle) * 40, -(float)cos(_angle) * 40)));
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(0, 100)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
				else
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 30, -(float)cos(_angle) * 30)));
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(0, -100)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
			}
			break;
		}
		else
		{
			if (_player->_isLeft)
			{
				if (_player->_isSlashDown)
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 70, (float)cos(_angle) * 70)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
				else
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2((float)sin(_angle) * 70, -(float)cos(_angle) * 70)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
			}
			else
			{
				if (_player->_isSlashDown)
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)sin(_angle) * 70, (float)cos(_angle) * 70)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
				else
					//_weaponImage->Render(CAMERA->GetRelativeVector2(_position + Vector2(-(float)cos(_angle) * 70, (float)sin(_angle) * 70)));
					_weaponImage->Render(CAMERA->GetRelativeVector2(_position));
			}
			break;
		}
		break;
	case WeaponType::GATLINGGUN:
		if (_player->_isLeft)
			_weaponImage->Render(CAMERA->GetRelativeVector2(_position), _player->_isLeft);
		else
			_weaponImage->Render(CAMERA->GetRelativeVector2(_position), _player->_isLeft);
		break;
	}



	

	if (_angle * 180 / 3.141592 < 0)
		_D2DRenderer->RenderText(1300, 325, L"각도 : " + to_wstring(-_angle * 180 / 3.141592), 15);
	else
		_D2DRenderer->RenderText(1300, 325, L"각도 : " + to_wstring(360 - _angle * 180 / 3.141592), 15);

	if (_player)
	{
		if (_player->_isLeft)
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_player->GetPosition()) - Vector2(_player->GetSize().x / 3, 0.f), CAMERA->GetRelativeVector2(_player->GetPosition()) + _direction);
		else
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_player->GetPosition()) + Vector2(_player->GetSize().x / 3, 0.f), CAMERA->GetRelativeVector2(_player->GetPosition()) + _direction);
	}
}

void Weapon::MoveAngle(float angle)
{
	_angle += angle;	//60프레임 기준 한 프레임 당, angle 값과 한 프레임 그리는 데 걸리는 시간을 곱한 값을 더해준다(개념적 이해) -> 설정한 angle만큼 커지는 순간 순간이 1초에 60번 보인다	
	//만약 deltaTime을 곱해주지 않는다면 60프레임 기준 의도한 바의 60배만큼 움직여 빠르게 보인다
	_rect.Update(_position, _size, Pivot::Center);
}


