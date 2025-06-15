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
//	_active = true;	// 미리 생성 후 가져다 쓸 용도로 이렇게 설정함, 생성해서 쓰려면 true로 놓는 것이 맞음
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
//		//_direction = _player->GetDirection();	//추가한 문구
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
//	//	//this->Release();	객체가 없어지지 않는 오브젝트 풀링 방식이라 사용할 필요가 없다. 릴리즈 함수는 오브젝트 소멸 시 설정할 내용이 있다면 내부에 작성하여 사용하는 함수
//	//	//OBJECTMANAGER->RemoveObject(ObjectType::Bullet, this);	객체가 없어지지 않는다
//	//	Init();
//	//	//SetActive(false);	//액티브 값을 false로 바꿔 
//	//}
//}
//
//void Bullet::Render()
//{
//	if (_player)
//	{
//		_D2DRenderer->RenderText(510, 800, L"총알 있음", 15);
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