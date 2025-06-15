#include "stdafx.h"
#include "TownScene.h"

TownScene::~TownScene()
{
}

HRESULT TownScene::Init()
{
	Skeleton* skeleton = new Skeleton();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, skeleton);

	Belial* belial = new Belial();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, belial);

	//_townBackGround = IMAGEMANAGER->AddImage(L"townBackground", L"Resources/TownBG.png");

	return S_OK;
}

void TownScene::Release()
{
}

void TownScene::Update()
{
	Scene::Update();
}

void TownScene::Render()
{
	_townBackGround->Render(Vector2(100, 0));
	_D2DRenderer->RenderText(550, 800, L"�׷� �� Ÿ���", 15);

	Scene::Render();
	// Ÿ�ϸ� �׷� �ֱ�
	if (_townBackGround) {
		Vector2 vImage{};
		vImage.x = _townBackGround->GetWidth() / 2.f;
		vImage.y = _townBackGround->GetHeight() / 2.f;
		_townBackGround->Render(vImage);
	}
}
