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
	_position = Vector2(WINSIZEX / 2, WINSIZEY / 2);
	_size = Vector2(190, 160);
	_rect = RectMakePivot(_position, _size, Pivot::Center);
	_active = true;
	_monState = MonsterState::IDLE;

	_attackSpeed = 0.f;
	_attackTime = 2.0f;

	_belialIdleImage = IMAGEMANAGER->AddFrameImage(L"belial_idle", L"Resources/Monster/Belial/idle.png", 10, 1);
	//_belialAttackImage = IMAGEMANAGER->AddFrameImage(L"belial_attack", L"Resources/attack.png", 12, 1);
	_belialLeftHandImage = IMAGEMANAGER->AddFrameImage(L"belial_hand_idle", L"Resources/Monster/Belial/hand_idle.png", 10, 1);
	_belialRightHandImage = IMAGEMANAGER->AddFrameImage(L"belial_hand_idle", L"Resources/Monster/Belial/hand_idle.png", 10, 1);

	_leftHandRect = RectMakePivot(_position + Vector2(-265, 0), _size, Pivot::Center);
	_rightHandRect = RectMakePivot(_position + Vector2(265, 0), _size, Pivot::Center);

	_belialIdle = new Animation();
	_belialIdle->Init(_belialIdleImage->GetWidth(), _belialIdleImage->GetHeight(), _belialIdleImage->GetFrameSize().x, _belialIdleImage->GetFrameSize().y);
	_belialIdle->SetPlayFrame(0, 9, false, true);
	_belialIdle->SetFPS(8);
	_belialIdle->Start();

	_belialLeftHand = new Animation();
	_belialLeftHand->Init(_belialLeftHandImage->GetWidth(), _belialLeftHandImage->GetHeight(), _belialLeftHandImage->GetFrameSize().x, _belialLeftHandImage->GetFrameSize().y);
	_belialLeftHand->SetPlayFrame(0, 9, false, true);
	_belialLeftHand->SetFPS(8);
	_belialLeftHand->Start();

	_belialRightHand = new Animation();
	_belialRightHand->Init(_belialLeftHandImage->GetWidth(), _belialLeftHandImage->GetHeight(), _belialLeftHandImage->GetFrameSize().x, _belialLeftHandImage->GetFrameSize().y);
	_belialRightHand->SetPlayFrame(0, 9, false, true);
	_belialRightHand->SetFPS(8);
	_belialRightHand->Start();
}

void Belial::Release()
{
}

void Belial::Update()
{
	_belialIdle->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_belialLeftHand->FrameUpdate(TIMEMANAGER->GetElapsedTime());
	_belialRightHand->FrameUpdate(TIMEMANAGER->GetElapsedTime());
}

void Belial::Render()
{
	_D2DRenderer->FillRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(_rect), D2DRenderer::DefaultBrush::Black, 2.0f);

	_D2DRenderer->DrawRectangle(_leftHandRect, D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(_rightHandRect, D2DRenderer::DefaultBrush::Black, 2.0f);

	switch (_monState)
	{
	case MonsterState::IDLE:
		if (!_belialIdleImage) return;	//null 체크. 안 하면 오류
		if (_isLeft)
		{
			_belialIdleImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(190, 0)), _belialIdle, 2.5f, _isLeft);
			_belialLeftHandImage->AniRender(CAMERA->GetRelativeVector2(_leftHandRect.GetCenter()), _belialLeftHand, 2.5f, 0);
			_belialLeftHandImage->AniRender(CAMERA->GetRelativeVector2(_rightHandRect.GetCenter()), _belialRightHand, 2.5f, 1);
		}
		else
		{
			_belialIdleImage->AniRender(CAMERA->GetRelativeVector2(_position + Vector2(-10, 0)), _belialIdle, 2.5f, _isLeft);
			_belialLeftHandImage->AniRender(CAMERA->GetRelativeVector2(_leftHandRect.GetCenter()), _belialLeftHand, 2.5f, 0);
			_belialLeftHandImage->AniRender(CAMERA->GetRelativeVector2(_rightHandRect.GetCenter() + Vector2(150,0)), _belialRightHand, 2.5f, 1);
		}
		break;
	}
}

void Belial::Razor()
{

}
