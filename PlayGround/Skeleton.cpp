#include "stdafx.h"
#include "Skeleton.h"
#include <string>

Skeleton::Skeleton()
{
	Init();
}

Skeleton::~Skeleton()
{
}

void Skeleton::Init()
{
	_name = L"Skeleton";
	_position = Vector2(400, 851);
	_size = Vector2(90, 160);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;
	_monState = MonsterState::IDLE;

	_attackSpeed = 0.f;
	_attackTime = 2.0f;

	_skeletonIdleImage = IMAGEMANAGER->AddFrameImage(L"skel_idle", L"Resources/Skel_idle.png", 5, 1);
	_skeletonAttackImage = IMAGEMANAGER->AddFrameImage(L"skel_attack", L"Resources/attack.png", 12, 1);

	_skeletonIdle = new Animation();
	_skeletonIdle->Init(_skeletonIdleImage->GetWidth(), _skeletonIdleImage->GetHeight(), _skeletonIdleImage->GetFrameSize().x, _skeletonIdleImage->GetFrameSize().y);
	_skeletonIdle->SetPlayFrame(0, 4, false, true);
	_skeletonIdle->SetFPS(8);	
	_skeletonIdle->Start();

	_skeletonAttack = new Animation();
	_skeletonAttack->Init(_skeletonAttackImage->GetWidth(), _skeletonAttackImage->GetHeight(), _skeletonAttackImage->GetFrameSize().x, _skeletonAttackImage->GetFrameSize().y);
	_skeletonAttack->SetPlayFrame(0, 11, false, true);
	_skeletonAttack->SetFPS(6);
	//_skeletonAttack->Start();

	_isAttack = false;
}

void Skeleton::Release()
{
}

void Skeleton::Update()
{
	_skeletonIdle->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_skeletonAttack->FrameUpdate(TIMEMANAGER->GetElapsedTime());

	if (fabs(_position.x - _player->GetPosition().x) < 200)
	{
		_isAttack = true;
		_monState = MonsterState::ATTACK;

		_skeletonImage = IMAGEMANAGER->FindImage(L"skel_attack");
		//_skeletonAttack->Start();
	}
	else
	{
		_isAttack = false;
		_monState = MonsterState::IDLE;

		_skeletonImage = IMAGEMANAGER->FindImage(L"skel_idle");
		//_skeletonAttack->Pause();
	}

	if (_player->GetPosition().x >= _position.x)
		_isLeft = false;
	else _isLeft = true;

	switch (_monState)
	{
	case MonsterState::IDLE:
		if (!_skeletonImage) return;	//null 체크. 안 하면 오류
		_attackSpeed = 0.f;
		_skeletonAttack->Stop();
		break;
	case MonsterState::ATTACK:
		if (!_skeletonImage) return;
		_skeletonAttack->Resume();
		
		if (_attackSpeed >= _attackTime) _attackSpeed = 0.f;
		_attackSpeed += TIMEMANAGER->GetElapsedTime();

		if(_isLeft)
			_attackRange = RectMakePivot(_position - Vector2(90.f, 0.f),Vector2(260, 140), Pivot::Center);
		else
			_attackRange = RectMakePivot(_position + Vector2(90.f, 0.f), Vector2(260, 140), Pivot::Center);

		if (_skeletonAttack->_nowPlayIndex == 3 || _skeletonAttack->_nowPlayIndex == 4 && IsCollide(_attackRange, _player->GetRect()))
			_player->_hp -= 3 * TIMEMANAGER->GetElapsedTime();
		break;
	}
}

void Skeleton::Render()
{
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	switch (_monState)
	{
	case MonsterState::IDLE:
		if (!_skeletonImage) return;	//null 체크. 안 하면 오류
		if(_isLeft)
			_skeletonImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(190, 0)), _skeletonIdle, 5.5f, _isLeft);
		else
			_skeletonImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(-10, 0)), _skeletonIdle, 5.5f, _isLeft);
		_D2DRenderer->RenderText(1000, 720, L"서있는상태", 15);
		break;
	case MonsterState::ATTACK:
		if (!_skeletonImage) return;
		if (_isLeft)
			_skeletonImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(300, -53)), _skeletonAttack, 1.4f, _isLeft);
		else
			_skeletonImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(98, -53)), _skeletonAttack, 1.4f, _isLeft);

		if(_skeletonAttack->_nowPlayIndex == 3 || _skeletonAttack->_nowPlayIndex == 4)
			_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_attackRange), D2DRenderer::DefaultBrush::Black, 2.0f);
		_D2DRenderer->RenderText(1000, 720, L"공격하는상태", 15);
		break;
	}

	_D2DRenderer->RenderText(1000, 820, to_wstring(_skeletonAttack->_nowPlayIndex), 15);
}
