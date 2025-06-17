#include "stdafx.h"
#include "MainScene.h"

MainScene::~MainScene()
{
}

HRESULT MainScene::Init()
{
	Player* player = new Player();
	OBJECTMANAGER->AddObject(ObjectType::Player, player);

	CAMERA->ChangeTarget(OBJECTMANAGER->FindObject(ObjectType::Player, L"Player"));
	CAMERA->SetCameraMode(CameraState::TARGET);

	Weapon* _weapon = new Weapon();
	OBJECTMANAGER->AddObject(ObjectType::Item, _weapon);

	Inventory* _inventory = new Inventory();
	OBJECTMANAGER->AddObject(ObjectType::UI, _inventory);

	UI* _ui = new UI();
	OBJECTMANAGER->AddObject(ObjectType::UI, _ui);

	Skeleton* skeleton = new Skeleton();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, skeleton);

	/*Belial* belial = new Belial();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, belial);*/

	//_backGround = IMAGEMANAGER->AddImage(L"townBackground", L"Resources/TownBG.png");

	for (int i = 0; i < 20; ++i) 
	{
		Bullet* bullet = new Bullet();

		OBJECTMANAGER->AddObject(ObjectType::Bullet, bullet);
	}

	/*SCENEMANAGER->AddScene(L"TownScene", new TownScene());
	SCENEMANAGER->ChangeScene(L"TownScene");*/

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
	_D2DRenderer->RenderText(150, 1000, L"¸ÞÀÎ¾À", 15);

	if (_backGround) 
	{
		Vector2 vImage{};
			vImage.x = _backGround->GetWidth();
			vImage.y = _backGround->GetHeight();
		_backGround->Render(vImage);
	}
}
