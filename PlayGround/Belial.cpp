#include "stdafx.h"
#include "Belial.h"

Belial::Belial()
{
	Init();
}

Belial::~Belial()
{
}

void Belial::Init()
{
	_name = L"Belial";
	_position = Vector2(200, 851);
	_size = Vector2(190, 160);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;
	_monState = MonsterState::IDLE;

	_attackSpeed = 0.f;
	_attackTime = 2.0f;

	_belialIdleImage = IMAGEMANAGER->AddFrameImage(L"belial_idle", L"Resources/Monster/Belial/idle.png", 10, 1);
	//_belialAttackImage = IMAGEMANAGER->AddFrameImage(L"belial_attack", L"Resources/attack.png", 12, 1);

	_belialIdle = new Animation();
	_belialIdle->Init(_belialIdleImage->GetWidth(), _belialIdleImage->GetHeight(), _belialIdleImage->GetFrameSize().x, _belialIdleImage->GetFrameSize().y);
	_belialIdle->SetPlayFrame(0, 9, false, true);
	_belialIdle->SetFPS(8);
	_belialIdle->Start();
}

void Belial::Release()
{
}

void Belial::Update()
{
	_belialIdle->FrameUpdate(TIMEMANAGER->GetElapsedTime());
}

void Belial::Render()
{
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	switch (_monState)
	{
	case MonsterState::IDLE:
		if (!_belialIdleImage) return;	//null 체크. 안 하면 오류
		if (_isLeft)
			_belialIdleImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(190, 0)), _belialIdle, 2.5f, _isLeft);
		else
			_belialIdleImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(-10, 0)), _belialIdle, 2.5f, _isLeft);
		_D2DRenderer->RenderText(1000, 720, L"서있는상태", 15);
		break;
	}
}
