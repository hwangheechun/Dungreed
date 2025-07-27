#include "stdafx.h"
#include "Scene.h"
#include <string>

Scene::Scene()
{
}

Scene::~Scene()
{
}

HRESULT Scene::Init()
{
	IMAGEMANAGER->AddFrameImage(L"towntile", L"Resources/Map/TownTile.png", 16, 18);

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
	if (_tiles.empty())
		return;

	//int startX = CAMERA->GetRect().left / TILE_SIZE;		// 100 / 32 -> index 3번째의 타일이 보여지고 있는 중, 0~2번째는 보여주지 X
	//int startY = CAMERA->GetRect().top / TILE_SIZE;
	//int endX = CAMERA->GetRect().right / TILE_SIZE;
	//int endY = CAMERA->GetRect().bottom / TILE_SIZE;

	//// 값을 보정
	//if (startX <= 0)
	//	startX = 0;
	//if (startY <= 0)
	//	startY = 0;
	//if (endX >= _maxX)
	//	endX = _maxX;
	//if (endY >= _maxY)
	//	endY = _maxY;

	for (int i = 0; i <= 40; ++i)
	{
		for (int j = 0; j <= 40; ++j)
		{
			_tiles[i][j]->Render();

		}

	}

	if (KEYMANAGER->IsStayKeyDown(0x4C))
	{
		for (int i = 0; i <= 40; ++i)
		{
			for (int j = 0; j <= 40; ++j)
			{
				_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(Vector2(j * 48, 0)), CAMERA->GetRelativeVector2(Vector2(j * 48, 1600)));  // 좌측 끝에서 우측 끝까지 수평선
			}
			_D2DRenderer->DrawLine(CAMERA->GetRelativeVector2(Vector2(0, i * 48)), CAMERA->GetRelativeVector2(Vector2(1920, i * 48)));  // 좌측 끝에서 우측 끝까지 수평선
		}
	}
}



