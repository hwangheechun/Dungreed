#include "stdafx.h"
#include "Player.h"
#include <string>

Player::Player()
{
	Init();
}

Player::~Player()
{

}

void Player::Init()
{
	_name = L"Player";
	_position = Vector2(0, WINSIZEY - 150);
	_size = Vector2(80, 120);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;

	_gravity = 10.f;

	_playerState = PlayerState::IDLE;

	_playerImage = IMAGEMANAGER->AddFrameImage(L"idle", L"Resources/Idle.png", 5, 1);
	IMAGEMANAGER->AddFrameImage(L"idle_left", L"Resources/Idle_left.png", 5, 1);

	_playerAnimation = new Animation();
	_playerAnimation->Init(_playerImage->GetWidth(), _playerImage->GetHeight(), _playerImage->GetFrameSize().x, _playerImage->GetFrameSize().y);
	_playerAnimation->SetFPS(7);	// 조정하면서 살펴보기
	_playerAnimation->Start();
}

void Player::Release()
{

}

void Player::Update()
{
	_cursor.x = CAMERA->GetPosition().x - WINSIZEX / 2 + _ptMouse.x;
	_cursor.y = _ptMouse.y;

	_weapon = dynamic_cast<Weapon*>(OBJECTMANAGER->FindObject(ObjectType::Item, L"Weapon"));

	_playerAnimation->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	_gravity += 50.f;

	if (!_isOnGround)
		Move(Vector2(0.0f, _gravity));
	else
		_gravity = 0.f;

	if (_position.y + _size.y / 2 >= WINSIZEY)
	{
		_isOnGround = true;

		if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))
		{
			_isOnGround = false;
			_gravity = -1200.0f;
		}
	}

	Operate();
}

void Player::Render()
{
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);
	_playerImage->AniRender(CAMERA->GetRelativeVector2(_position), _playerAnimation, 6.5f);
	
	
	_D2DRenderer->RenderText(550, 10, L"캐릭터 위치:" + to_wstring((int)CAMERA->GetRelativeVector2(_position).x), 15);
	_D2DRenderer->RenderText(700, 10, to_wstring((int)CAMERA->GetRelativeVector2(_position).y), 15);
	_D2DRenderer->RenderText(950, 10, L"실제 위치:" + to_wstring((int)_position.x), 15);
	_D2DRenderer->RenderText(1100, 10, to_wstring((int)_position.y), 15);

	_D2DRenderer->RenderText(50, 500, L"카메라:" + to_wstring((int)CAMERA->GetrcTop().x), 15);
	_D2DRenderer->RenderText(50, 550, L"카메라:" + to_wstring((int)CAMERA->GetrcTop().y), 15);
	_D2DRenderer->RenderText(50, 600, L"카메라:" + to_wstring((int)CAMERA->GetrcBottom().x), 15);
	_D2DRenderer->RenderText(50, 650, L"카메라:" + to_wstring((int)CAMERA->GetrcBottom().y), 15);
	_D2DRenderer->RenderText(50, 675, L"카메라 중앙:" + to_wstring((int)CAMERA->GetPosition().x), 15);
	_D2DRenderer->RenderText(250, 675, to_wstring((int)CAMERA->GetPosition().y), 15);


	switch (_playerState)
	{
	case PlayerState::IDLE :
		_D2DRenderer->RenderText(800, 10, L"서있는 상태" + to_wstring((int)_playerState), 15);
		break;
	case PlayerState::RUN:
		_D2DRenderer->RenderText(800, 10, L"달리는 상태" + to_wstring((int)_playerState), 15);
		break;
	}

	_D2DRenderer->RenderText(100, 200, L"너비 : " + to_wstring((int)_playerImage->GetWidth()), 15);
	_D2DRenderer->RenderText(100, 225, L"높이 : " + to_wstring((int)_playerImage->GetHeight()), 15);
	_D2DRenderer->RenderText(100, 250, L"가로 프레임 : " + to_wstring((int)_playerImage->GetMaxFrameX()), 15);
	_D2DRenderer->RenderText(100, 275, L"세로 프레임 : " + to_wstring((int)_playerImage->GetMaxFrameY()), 15);
	_D2DRenderer->RenderText(100, 300, L"한 프레임 너비 : " + to_wstring((int)_playerImage->GetFrameSize().x), 15);
	_D2DRenderer->RenderText(100, 325, L"한 프레임 높이 : " + to_wstring((int)_playerImage->GetFrameSize().y), 15);

	if(_isOnGround)
		_D2DRenderer->RenderText(550, 30, L"착지" + to_wstring(_isOnGround), 15);
	else
		_D2DRenderer->RenderText(550, 30, L"점프" + to_wstring(_isOnGround), 15);

	//_D2DRenderer->RenderText(90, 800, to_wstring(_gravity), 15);
	_D2DRenderer->RenderText(600, 30, L"마우스 : " + to_wstring((int)_cursor.x), 15);
	_D2DRenderer->RenderText(700, 30, to_wstring((int)_cursor.y), 15);

	if(_isLeft)
		_D2DRenderer->RenderText(550, 45, L"좌 : " + to_wstring(_isLeft), 15);
	else 
		_D2DRenderer->RenderText(550, 45, L"우 : " + to_wstring(_isLeft), 15);

	//_D2DRenderer->RenderText(210, 800, to_wstring(_isDash + 125), 15);
	_D2DRenderer->RenderText(410, 800, to_wstring(attackCount), 15);

	if (!_weapon)
		_D2DRenderer->RenderText(910, 800, L"무기 없음", 15);
	else
		_D2DRenderer->RenderText(910, 800, to_wstring(_weapon->_angle), 15);
}

void Player::Move(Vector2 moveDirection)
{
	_position += moveDirection * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void Player::Jump()
{

}

void Player::Dash()
{
	_isDash = true;
	_isOnGround = false;
	_gravity = -200.0f;

	if(_position != Vector2((float)_ptMouse.x, (float)_ptMouse.y))
		_position += (Vector2((float)_ptMouse.x, (float)_ptMouse.y) - _position);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void Player::Attack(Weapon* weapon)
{
	attackCount++;
	weapon->MoveAngle(4);

}

void Player::Operate()
{
	if (KEYMANAGER->IsStayKeyDown(0x41))	//A
	{
		_playerState = PlayerState::RUN;
		Move(Vector2(-300, 0));
	}
	else if (KEYMANAGER->IsStayKeyDown(0x44))	//D
	{
		_playerState = PlayerState::RUN;
		Move(Vector2(300, 0));
	}
	else
	{
		_playerState = PlayerState::IDLE;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))	//SPACE
	{
		Jump();
	}

	if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))	//Mouse_R
	{
		if(_weapon)
			Attack(_weapon);
	}
	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))	//Mouse_R
	{
		Dash();
	}

	switch (_playerState)
	{
		case PlayerState::IDLE :
			_playerAnimation->SetPlayFrame(0, 4, false, true);

			if (_cursor.x < _position.x)
			{
				_isLeft = true;
				_playerImage = IMAGEMANAGER->FindImage(L"idle_left");
			}
			else
			{
				_isLeft = false;
				_playerImage = IMAGEMANAGER->FindImage(L"idle");
			}
			break;
		case PlayerState::RUN :
			_playerAnimation->SetPlayFrame(0, 4, false, true);

			if (_cursor.x < _position.x)
			{
				_isLeft = true;
				_playerImage = IMAGEMANAGER->FindImage(L"idle_left");
			}
			else
			{
				_isLeft = false;
				_playerImage = IMAGEMANAGER->FindImage(L"idle");
			}
			break;
	}
}