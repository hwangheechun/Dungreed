#include "stdafx.h"
#include "PlayGround.h"
#include "IEvent.h"

HRESULT PlayGround::Init()
{
	GameNode::Init(true);

	SCENEMANAGER->AddScene(L"MainScene", new MainScene());
	SCENEMANAGER->AddScene(L"DungeonScene", new DungeonScene());
	SCENEMANAGER->AddScene(L"Test", new TownScene());
	SCENEMANAGER->AddScene(L"MapToolScene", new MapToolScene());
	SCENEMANAGER->AddScene(L"DungeonStartScene1", new DungeonStartScene1());
	SCENEMANAGER->AddScene(L"DungeonScene1", new DungeonScene1());
	SCENEMANAGER->AddScene(L"DungeonScene2", new DungeonScene2());
	SCENEMANAGER->AddScene(L"DungeonScene3", new DungeonScene3());
	SCENEMANAGER->ChangeScene(L"MainScene");


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
