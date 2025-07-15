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

	IMAGEMANAGER->AddFrameImage(L"idle", L"Resources/Idle.png", 5, 1);
	IMAGEMANAGER->AddFrameImage(L"run", L"Resources/Run.png", 8, 1);

	_playerIdle = new Animation();
	_playerIdle->Init(IMAGEMANAGER->FindImage(L"idle")->GetWidth(), IMAGEMANAGER->FindImage(L"idle")->GetHeight(), IMAGEMANAGER->FindImage(L"idle")->GetFrameSize().x, IMAGEMANAGER->FindImage(L"idle")->GetFrameSize().y);
	_playerIdle->SetPlayFrame(0, 4, false, true);
	_playerIdle->SetFPS(7);
	_playerIdle->Start();

	_playerRun = new Animation();
	_playerRun->Init(IMAGEMANAGER->FindImage(L"run")->GetWidth(), IMAGEMANAGER->FindImage(L"run")->GetHeight(), IMAGEMANAGER->FindImage(L"run")->GetFrameSize().x, IMAGEMANAGER->FindImage(L"run")->GetFrameSize().y);
	_playerRun->SetPlayFrame(0, 7, false, true);
	_playerRun->SetFPS(12);
	_playerRun->Start();
}

void Player::Release()
{

}

void Player::Update()
{
#pragma region 찾기
	//인벤토리 찾기
	_inventory = dynamic_cast<Inventory*>(OBJECTMANAGER->FindObject(ObjectType::UI, L"Inventory"));	//캐릭터가 인벤토리보다 먼저 생성되서 init에서 찾아봐야 안 나온다

	//무기 찾기
	_weapon = dynamic_cast<Weapon*>(OBJECTMANAGER->FindObject(ObjectType::Item, L"Weapon"));	//캐릭터가 무기보다 먼저 생성되서 init에서 찾아봐야 안 나온다

	//UI 찾기
	_ui = dynamic_cast<UI*>(OBJECTMANAGER->FindObject(ObjectType::UI, L"UI"));

	//총알 찾기
	_bullet = OBJECTMANAGER->FindObjects(ObjectType::Bullet, L"Bullet");
#pragma endregion
#pragma region 무기
	if (_weapon)
	{
		if (_isLeft)
			_weapon->SetPosition(Vector2(_position.x - _size.x / 3, _position.y));
		else
			_weapon->SetPosition(Vector2(_position.x + _size.x / 3, _position.y));

		_weapon->_direction.x = _ui->_cursor.x - CAMERA->GetRelativeVector2(_position).x;
		_weapon->_direction.y = _ui->_cursor.y - CAMERA->GetRelativeVector2(_position).y;

		if (_weapon->_angle * 180 / 3.141592 < 0 && _isLeft == false)
			_weapon->_weaponImage->SetAngle(_weapon->_angle * 180 / 3.141592);
		else if (_weapon->_angle * 180 / 3.141592 < 0 && _isLeft == true)
			_weapon->_weaponImage->SetAngle(-180 + _weapon->_angle * 180 / 3.141592);
		else if (_weapon->_angle * 180 / 3.141592 > 0 && _isLeft == false)
			_weapon->_weaponImage->SetAngle(_weapon->_angle * 180 / 3.141592);
		else if (_weapon->_angle * 180 / 3.141592 > 0 && _isLeft == true)
			_weapon->_weaponImage->SetAngle(-180 + _weapon->_angle * 180 / 3.141592);
	}
#pragma endregion
#pragma region 중력, 애니메이션 업데이트
	//중력
	_gravity += 50.f;

	if (!_isOnGround)
		Move(Vector2(0.f, _gravity));
	else
		_gravity = 0.f;

	if (_position.y + _size.y / 2 >= WINSIZEY)
	{
		_isOnGround = true;
	}

	//애니메이션 업데이트
	_playerIdle->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_playerRun->FrameUpdate(TIMEMANAGER->GetElapsedTime());
#pragma endregion
#pragma region 캐릭터 동작
	Operate();
	InventoryOperate();
#pragma endregion

	switch (_playerState)
	{
	case PlayerState::IDLE:
		if (!_playerImage) return;
		_playerImage = IMAGEMANAGER->FindImage(L"idle");
		break;
	case PlayerState::RUN:
		if (!_playerImage) return;
		_playerImage = IMAGEMANAGER->FindImage(L"run");
		break;
	}	

	for (int i = 0; i < _bullet.size(); i++)
	{
		if (dynamic_cast<Bullet*>(_bullet[i])->_isFire)
			dynamic_cast<Bullet*>(_bullet[i])->Move(Vector2(WINSIZEX, 0));

		if (!dynamic_cast<Bullet*>(_bullet[i])->GetActive())
			dynamic_cast<Bullet*>(_bullet[i])->SetPosition(_position);
	}
}


void Player::Render()
{
	if (_inventory && _inventory->GetActive())
	{
		if ((_inventory->_isSlotCliked[0] && _inventory->_equipSlotImage[0]) || (_inventory->_isSlotCliked[1] && _inventory->_equipSlotImage[1]))
		{
			if(_ui->_mouseCursorItem) //null 체크
				_ui->_mouseCursorItem->Render(_ui->_cursor);
		}

		for (int i = 0; i < 15; i++)
		{
			if (_inventory->_isListCliked[i] && _inventory->_equipListImage[i])
			{
				if (_ui->_mouseCursorItem) //null 체크
					_ui->_mouseCursorItem->Render(_ui->_cursor);
			}
		}
	}

	//캐릭터 히트박스
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	//캐릭터 그리기
	switch (_playerState)
	{
	case PlayerState::IDLE:
		if (!_playerImage) return;
		if (_isLeft)
			_playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(92, 0)), _playerIdle, 6.5f, _isLeft);
		else _playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(6, 0)), _playerIdle, 6.5f, _isLeft);
		break;
	case PlayerState::RUN:
		if (!_playerImage) return;
		if (_isLeft)
			_playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(104, 0)), _playerRun, 6.5f, _isLeft);
		else _playerImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(8, 0)), _playerRun, 6.5f, _isLeft);
		break;
	}
#pragma region 플레이어 정보 텍스트
	if (_weapon)
	{
		_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(_weapon->GetPosition()), _ui->_cursor);
		_D2DRenderer->RenderText(1550, 190, L"아이템 잡힘 상태" + to_wstring(_position.x - _weapon->GetPosition().x), 15);
	}
	//캐릭터 위치 좌표
	_D2DRenderer->RenderText(550, 10, L"캐릭터 위치:" + to_wstring((int)CAMERA->GetRelativeVector2(_position).x), 15);
	_D2DRenderer->RenderText(700, 10, to_wstring((int)CAMERA->GetRelativeVector2(_position).y), 15);
	_D2DRenderer->RenderText(950, 10, L"실제 위치:" + to_wstring((int)_position.x), 15);
	_D2DRenderer->RenderText(1100, 10, to_wstring((int)_position.y), 15);

	//카메라 위치 좌표
	_D2DRenderer->RenderText(50, 500, L"카메라:" + to_wstring((int)CAMERA->GetrcTop().x), 15);
	_D2DRenderer->RenderText(50, 550, L"카메라:" + to_wstring((int)CAMERA->GetrcTop().y), 15);
	_D2DRenderer->RenderText(50, 600, L"카메라:" + to_wstring((int)CAMERA->GetrcBottom().x), 15);
	_D2DRenderer->RenderText(50, 650, L"카메라:" + to_wstring((int)CAMERA->GetrcBottom().y), 15);
	_D2DRenderer->RenderText(50, 675, L"카메라 중앙:" + to_wstring((int)CAMERA->GetPosition().x), 15);
	_D2DRenderer->RenderText(250, 675, to_wstring((int)CAMERA->GetPosition().y), 15);

	//마우스 위치 좌표
	if (_ui)
	{
		_D2DRenderer->RenderText(600, 30, L"마우스 : " + to_wstring((int)_ui->_cursor.x), 15);
		_D2DRenderer->RenderText(700, 30, to_wstring((int)_ui->_cursor.y), 15);
		_D2DRenderer->RenderText(600, 60, L"캐릭터로부터 마우스 : " + to_wstring((int)(_ui->_cursor.x - CAMERA->GetRelativeVector2(_position).x)), 15);
		_D2DRenderer->RenderText(800, 60, to_wstring((int)(_ui->_cursor.y - CAMERA->GetRelativeVector2(_position).y)), 15);
	}

	switch (_playerState)
	{
	case PlayerState::IDLE:
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
	_D2DRenderer->RenderText(100, 325, L"한 프레임 높높이 : " + to_wstring((int)_playerImage->GetFrameSize().y), 15);

	if (_isOnGround)
		_D2DRenderer->RenderText(550, 30, L"착지" + to_wstring(_isOnGround), 15);
	else
		_D2DRenderer->RenderText(550, 30, L"점프" + to_wstring(_isOnGround), 15);

	//_D2DRenderer->RenderText(90, 800, to_wstring(_gravity), 15);

	if (_isLeft)
		_D2DRenderer->RenderText(550, 45, L"좌 : " + to_wstring(_isLeft), 15);
	else
		_D2DRenderer->RenderText(550, 45, L"우 : " + to_wstring(_isLeft), 15);

	_D2DRenderer->RenderText(410, 800, to_wstring(_isSlashDown), 15);

	if (!_weapon)
		_D2DRenderer->RenderText(300, 500, L"무기 없음", 15);	
	else
		_D2DRenderer->RenderText(300, 500, L"무기 있음", 15);

	if (_inventory)
	{
		_D2DRenderer->RenderText(1210, 800, L"인벤있음", 15);
		_D2DRenderer->RenderText(1310, 800, to_wstring(_inventory->GetActive()), 15);
	}


	/*for (int i = 0; i < 20; i++)
	{
		_D2DRenderer->RenderText(100, 700 + i * 15, to_wstring(_bullet[i]->GetPosition().x), 15);
		_D2DRenderer->RenderText(300, 700 + i * 15, to_wstring(_bullet[i]->GetPosition().y), 15);
	}

	for (int i = 0; i < 20; i++)
	{

		auto pBulletObj = dynamic_cast<Bullet*>(_bullet[i]);

		_D2DRenderer->RenderText(400, 700 + i * 15, L"발사?" + to_wstring(pBulletObj->_isFire), 15);
		_D2DRenderer->RenderText(500, 700 + i * 15, L"보임?" + to_wstring(pBulletObj->GetActive()), 15);
	}	*/

	/*if(_inventory->_equipSlot1Image == nullptr)
		_D2DRenderer->RenderText(300,450, L"무기인벤이미지없음", 15);*/
#pragma endregion
	
}

void Player::Move(Vector2 moveDirection)
{
	_position += moveDirection * TIMEMANAGER->GetElapsedTime();	// == deltaTime
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void Player::Jump()
{
	_isOnGround = false;
	_gravity = -1200.0f;
}

//void Player::Dash()
//{
//	_isDash = true;
//	_isOnGround = false;
//	_isSlashDown = false;
//	_gravity = -200.0f;
//
//	if (_position != Vector2((float)_ptMouse.x, (float)_ptMouse.y))
//		_position += (Vector2((float)_ptMouse.x, (float)_ptMouse.y) - _position);
//	_rect = RectMakePivot(_position, _size, Pivot::Center);
//}

void Player::Attack(Weapon* weapon)
{
	if (_isSlashDown)
		_isSlashDown = false;
	else
		_isSlashDown = true;

	switch (weapon->_weaponType)
	{
		case WeaponType::SWORD:
			break;
		case WeaponType::GATLINGGUN:
			for (auto pObj : _bullet) 
			{	
				if (pObj->GetActive())
					continue;
				pObj->Init();
				pObj->SetActive(true);

				auto pBulletObj = dynamic_cast<Bullet*>(pObj);

				pBulletObj->_isFire = true;

				break;
			}
			break;
	}
}

void Player::Operate()
{
#pragma region 캐릭터 이동
	if (KEYMANAGER->IsStayKeyDown(0x41))	//A_좌로 이동
	{
		_playerState = PlayerState::RUN;
		Move(Vector2(-300, 0));
	}
	else if (KEYMANAGER->IsStayKeyDown(0x44))	//D_우로 이동
	{
		_playerState = PlayerState::RUN;
		Move(Vector2(300, 0));
	}
	else
	{
		_playerState = PlayerState::IDLE;
	}

	if (KEYMANAGER->IsOnceKeyDown(VK_SPACE))	//SPACE_점프
	{
		Jump();
	}
#pragma endregion
#pragma region 무기 조작
	if (_weapon)
	{
		if (KEYMANAGER->IsOnceKeyDown(0x31))
		{
			_weapon->_weaponType = WeaponType::SWORD;
		}
		else if (KEYMANAGER->IsOnceKeyDown(0x32))
		{
			_weapon->_weaponType = WeaponType::GATLINGGUN;
		}

		switch (_weapon->_weaponType)
		{
		case WeaponType::SWORD:
			break;
		case WeaponType::GATLINGGUN:
			if (KEYMANAGER->IsStayKeyDown(VK_LBUTTON))
			{
				for (auto pObj : _bullet)
				{
					if (pObj->GetActive())
						continue;
					pObj->Init();
					pObj->SetActive(true);

					auto pBulletObj = dynamic_cast<Bullet*>(pObj);

					pBulletObj->_isFire = true;

					break;
				}
			}
		}
	}
#pragma endregion
	//if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))	//Mouse_L
	//{
	//	if (!_inventory->GetActive())
	//	{
	//		if (_weapon)
	//			Attack(_weapon);
	//	}
	//}

	if (KEYMANAGER->IsOnceKeyDown(VK_RBUTTON))	//Mouse_R
	{
		//Dash();
	}

	if (_ui)
	{
		switch (_playerState)
		{
		case PlayerState::IDLE:
			if (_ui->_cursor.x - CAMERA->GetRelativeVector2(_position).x < 0)
			{
				_isLeft = true;
			}
			else
			{
				_isLeft = false;
			}
			break;
		case PlayerState::RUN:
			if (_ui->_cursor.x - CAMERA->GetRelativeVector2(_position).x < 0)
			{
				_isLeft = true;
			}
			else
			{
				_isLeft = false;
			}
			break;
		}
	}
	
	if (KEYMANAGER->IsOnceKeyDown(0x56))	//V_inventory
	{
		if (_inventory)
		{
			if (_inventory->GetActive() == false)
				_inventory->SetActive(true);
			else
				_inventory->SetActive(false);
		}
	}

	if (KEYMANAGER->IsOnceKeyDown(0x4A))	//V_inventory
	{
		SCENEMANAGER->ChangeScene(L"DungeonScene");
		SetPosition(Vector2(0, WINSIZEY - 150));	//던전 씬으로 이동할 때 캐릭터 위치 초기화
	}

	if (KEYMANAGER->IsOnceKeyDown(0x4F))	//V_inventory
	{
		SCENEMANAGER->check();
	}
}

void Player::InventoryOperate()
{
	if (_inventory && _ui)	//인벤토리와 UI 체크
	{
		for (int i = 0; i < 2; i++)
		{
			if (IsCollide(_ui->_cursor, _inventory->_equipSlot[i]))	//장비 슬롯
			{
				if (KEYMANAGER->IsOnceKeyDown(0x47))
				{
					if (!_inventory->_isSlotCliked[i])	//장비 슬롯의 장비를 끌어오거나 장착하기 위해 장비 슬롯을 클릭할 때(0일때)
					{
						if (_inventory->_itemState == ItemState::ITEM_MOVE)	//목록의 장비를 장비 슬롯에 장착하려 할 때
						{
							_inventory->CleanSlotValue();
							_inventory->CleanListValue();
							_inventory->_isSlotCliked[i] = false;
							if (_ui->_mouseCursorItem)
							{
								_inventory->_equipSlotImage[0] = _ui->_mouseCursorItem;
								_weapon->SetActive(true);
								/*for (int j = 0; j < 15; j++)
								{
									if (_inventory->_equipListImage[j] == _ui->_mouseCursorItem)
									{
										_inventory->_equipListImage[j] = nullptr;
										break;
									}
								}*/
								_ui->_mouseCursorItem = nullptr;
							}
						}
						else if (_inventory->_itemState == ItemState::DEFAULT) //슬롯에서 목록으로 장비를 해제하려 할 때
						{
							if (_inventory->_equipSlotImage[i])
							{
								_inventory->CleanSlotValue();
								_inventory->CleanListValue();
								_inventory->_isSlotCliked[i] = true;
								_ui->_mouseCursorItem = _inventory->_equipSlotImage[i];
							}
						}							
					}
					else                                //장비 슬롯을 클릭했지만 다시 비활성화할 때(1일때)
					{
						_inventory->CleanSlotValue();
						_inventory->CleanListValue();
						_inventory->_isSlotCliked[i] = false;
						_ui->_mouseCursorItem = nullptr;
					}
						
				}
			}
		}

		for (int i = 0; i < 15; i++)
		{
			if (IsCollide(_ui->_cursor, _inventory->_equipList[i]))	//장비 목록
			{
				if (KEYMANAGER->IsOnceKeyDown(0x47))
				{
					if (_inventory->_isSlotCliked[0] || _inventory->_isSlotCliked[1]) //장비 슬롯 둘 중에 하나라도 선택이 되어서 장착된 장비를 목록으로 가져와 해제하려 할 때
					{
						_inventory->CleanSlotValue();
						_inventory->_equipListImage[i] = _ui->_mouseCursorItem;
						_weapon->SetActive(false);
						_inventory->_equipSlotImage[0] = nullptr;
					}
					else                                                              
					{
						if (_inventory->_itemState == ItemState::DEFAULT)
						{
							if (_inventory->_equipListImage[i])
								_ui->_mouseCursorItem = _inventory->_equipListImage[i];

							if (!_inventory->_isListCliked[i])
							{
								_inventory->CleanSlotValue();
								_inventory->CleanListValue();
								_inventory->_isListCliked[i] = true;
							}
							else
							{
								_inventory->CleanSlotValue();
								_inventory->CleanListValue();
								_inventory->_isListCliked[i] = false;
							}
						}
						else if (_inventory->_itemState == ItemState::ITEM_MOVE)	//목록의 장비를 장비 슬롯에 장착하려 할 때
						{
							_inventory->CleanSlotValue();
							_inventory->CleanListValue();
						}
					}
				}
			}
		}

		if (_weapon && _weapon->GetActive())	//무기 체크
			_inventory->_equipSlotImage[0] = _weapon->_weaponImage;

	}
}

bool Player::IsCollide(FloatRect _rect, FloatRect _rect2)
{
	if (_rect.right > _rect2.left && _rect.left < _rect2.right && _rect.top < _rect2.bottom && _rect.bottom > _rect2.top)
		return true;
	else return false;
}

bool Player::IsCollide(Vector2 _point, FloatRect _rect)
{
	if (_point.x > _rect.left && _point.x < _rect.right && _point.y < _rect.bottom && _point.y > _rect.top)
		return true;
	return false;
}
