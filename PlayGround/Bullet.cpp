//#include "stdafx.h"
//#include "Bullet.h"
//#include <string>
//
//Bullet::Bullet()
//{
//	Init();
//}
//
//Bullet::~Bullet()
//{
//}
//
//void Bullet::Init()
//{
//	_name = L"Bullet";
//	_position = Vector2(WINSIZEX / 2 - 100, WINSIZEY / 2 - 100);
//	_size = Vector2(10, 10);
//	_rect = RectMakePivot(_position, _size, Pivot::Center);
//	_active = true;	// �̸� ���� �� ������ �� �뵵�� �̷��� ������, �����ؼ� ������ true�� ���� ���� ����
//
//	//_direction = Vector2(1, 0);
//	_isInit = false;
//
//	_player = dynamic_cast<Player*>(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
//	//_ai = dynamic_cast<AI*>(OBJECTMANAGER->FindObject(ObjectType::AI, L"AI"));
//
//	if (_player)
//	{
//		_position = _player->GetPosition() + Vector2((float)cos(_angle), sin(_angle));//_direction * 0.1f;
//		//_direction = _player->GetDirection();	//�߰��� ����
//	}
//
//	_isFire = false;
//	_gravity.x = 0;
//	_gravity.y = 1.5;
//
//	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
//	_direction = Vector2((float)cos(_angle), sin(_angle));
//}
//
//void Bullet::Release()
//{
//}
//
//void Bullet::Update()
//{
//	_angle = atan2(_direction.y, _direction.x); //* 180 / 3.141592;
//	_direction.x = _player->_cursor.x - CAMERA->GetRelativeVector2(_player->GetPosition()).x;
//	_direction.y = _player->_cursor.y - CAMERA->GetRelativeVector2(_player->GetPosition()).y;
//
//	if (_isFire)
//	{
//		Move(Vector2(600,0));
//		_direction += _gravity * TIMEMANAGER->GetElapsedTime();
//	}
//
//	//if (_position.x >= WINSIZEX || _position.x <= 0 || _position.y >= WINSIZEY || _position.y <= 0)
//	//{
//	//	//this->Release();	��ü�� �������� �ʴ� ������Ʈ Ǯ�� ����̶� ����� �ʿ䰡 ����. ������ �Լ��� ������Ʈ �Ҹ� �� ������ ������ �ִٸ� ���ο� �ۼ��Ͽ� ����ϴ� �Լ�
//	//	//OBJECTMANAGER->RemoveObject(ObjectType::Bullet, this);	��ü�� �������� �ʴ´�
//	//	Init();
//	//	//SetActive(false);	//��Ƽ�� ���� false�� �ٲ� 
//	//}
//}
//
//void Bullet::Render()
//{
//	if (_player)
//	{
//		_D2DRenderer->RenderText(510, 800, L"�Ѿ� ����", 15);
//		_D2DRenderer->RenderText(510, 850, to_wstring(_position.x), 15);
//		_D2DRenderer->RenderText(510, 890, to_wstring(_position.y), 15);
//		_D2DRenderer->RenderText(510, 910, to_wstring(_direction.x), 15);
//		_D2DRenderer->RenderText(510, 930, to_wstring(_direction.y), 15);
//		_D2DRenderer->RenderText(510, 950, to_wstring(_angle * 180 / 3.141592f), 15);
//		_D2DRenderer->RenderText(510, 990, to_wstring(_isFire), 15);
//
//	}
//	D2DRenderer::GetInstance()->DrawEllipse(CAMERA->GetRelativeVector2(_position), _size.x, D2DRenderer::DefaultBrush::Black, 1.0f);
//}
//
//void Bullet::Move(Vector2 moveDirection)
//{
//	_position += moveDirection * TIMEMANAGER->GetElapsedTime();	// == deltaTime
//	_rect = RectMakePivot(_position, _size, Pivot::Center);
//}
//
//void Bullet::MoveAngle(float speed)
//{
//	_position += _direction * speed * TIMEMANAGER->GetElapsedTime();
//	_rect.Update(_position, _size, Pivot::Center);
//}