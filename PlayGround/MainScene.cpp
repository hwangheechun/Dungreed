#include "stdafx.h"
#include "MainScene.h"

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
	Player* player = new Player();
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	Weapon* _weapon = new Weapon();
	OBJECTMANAGER->AddObject(ObjectType::Item, _weapon);

	Inventory* _inventory = new Inventory();
	OBJECTMANAGER->AddObject(ObjectType::UI, _inventory);

	UI* _ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, _ui);

	/*for (int i = 0; i < 20; ++i) 
	{
		Bullet* bullet = new Bullet();

		OBJECTMANAGER->AddObject(ObjectType::Bullet, bullet);
	}*/

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
