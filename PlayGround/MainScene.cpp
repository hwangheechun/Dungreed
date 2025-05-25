#include "stdafx.h"
#include "MainScene.h"

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
	Player* player = new Player();
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	UI* _ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, _ui);

	Weapon* _weapon = new Weapon();
	OBJECTMANAGER->AddObject(ObjectType::Item, _weapon);

	SCENEMANAGER->AddScene(L"TownScene", new TownScene());
	SCENEMANAGER->ChangeScene(L"TownScene");

	return S_OK;
}

void MainScene::Release()
{
}

void MainScene::Update()
{
	Scene::Update();
}

void MainScene::Render()
{
	
}
