#include "stdafx.h"
#include "DungeonScene.h"

DungeonScene::~DungeonScene()
{
}

HRESULT DungeonScene::Init()
{
	Belial* belial = new Belial();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, belial);

	return E_NOTIMPL;
}

void DungeonScene::Release()
{
}

void DungeonScene::Update()
{
	Scene::Update();
}

void DungeonScene::Render()
{
	_D2DRenderer->RenderText(350, 1100, L"´øÀü¾À", 15);
}
