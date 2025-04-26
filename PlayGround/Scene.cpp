#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

HRESULT Scene::Init()
{
	return S_OK;
}

void Scene::Release()
{
}

void Scene::Update()
{
	bool bTest = false;
	if (bTest) {
		SCENEMANAGER->ChangeScene(_nextScene);
	}
}

void Scene::Render()
{
	// 타일맵 그려 주기
}

IntroScene::~IntroScene()
{
}

HRESULT IntroScene::Init()
{
	//Player* _player = new Player();

	_introImage = IMAGEMANAGER->AddImage(L"Player Idle", L"Resources/shantae_piratesCurse_banner.png");

	return S_OK;
}

void IntroScene::Release()
{
}

void IntroScene::Update()
{
	Scene::Update();
}

void IntroScene::Render()
{
	Scene::Render();
	// 타일맵 그려 주기
	if (_introImage) {
		Vector2 vImage{};
		vImage.x = _introImage->GetWidth() / 2.f;
		vImage.y = _introImage->GetHeight() / 2.f;
		_introImage->Render(vImage);
	}
}
