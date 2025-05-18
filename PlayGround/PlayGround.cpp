#include "stdafx.h"
#include "PlayGround.h"
#include "IEvent.h"

HRESULT PlayGround::Init()
{
	GameNode::Init(true);

	Player* player = new Player();
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	UI* _ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, _ui);

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	CAMERA->SetCameraMode(CameraState::TARGET);

	return S_OK;
}

void PlayGround::Release()
{
	OBJECTMANAGER->Release();
}

void PlayGround::Update()
{
	GameNode::Update();

	OBJECTMANAGER->Update();
	SCENEMANAGER->Update();
	CAMERA->Update();
	EventManager::GetInstance()->Update();
}

void PlayGround::Render()
{	
	// 백버퍼 초기화
	D2DRenderer::GetInstance()->BeginRender(D2D1::ColorF::White);
	{
		SCENEMANAGER->Render();
		OBJECTMANAGER->Render();
	}
	D2DRenderer::GetInstance()->EndRender();
}
