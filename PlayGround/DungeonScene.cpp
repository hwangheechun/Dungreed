#include "stdafx.h"
#include "DungeonScene.h"

DungeonScene::~DungeonScene()
{
}

HRESULT DungeonScene::Init()
{
	Belial* belial = new Belial();
	OBJECTMANAGER->AddObject(ObjectType::Enemy, belial);

	//_bossBackGround = IMAGEMANAGER->AddImage(L"bossBackground", L"Resources/Map/Boss.png");

	_maxX = 40;
	_maxY = 40;

	for (int i = 0; i <= _maxY; ++i)
	{
		vTileOneLine v;
		for (int j = 0; j <= _maxX; ++j)
		{
			Tile* t = new Tile();
			t->SetTile(1, 0, 0);
			t->SetTileRc(j * TILE_SIZE, i * TILE_SIZE);		// 0, 0 -> 0, 0 / 0, 1 -> 48, 0 - left top 설정해 주는 함수

			v.emplace_back(t);
		}
		_tiles.emplace_back(v);
	}

	//return E_NOTIMPL;
	return S_OK;
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
	//_bossBackGround->Render(CAMERA->GetRelativeVector2(Vector2(WINSIZEX/2, WINSIZEY/2)));
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(FloatRect(0,0,1920,1080)), D2DRenderer::DefaultBrush::Red, 2.0f);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(FloatRect(1940, 0, 1940 + 1920, 1080)), D2DRenderer::DefaultBrush::Red, 2.0f);
	_D2DRenderer->DrawRectangle(CAMERA->GetRelativeRect(FloatRect(1960 + 1920, 0, 1940 + 1920 + 1920, 1080)), D2DRenderer::DefaultBrush::Red, 2.0f);
	_D2DRenderer->RenderText(CAMERA->GetRelativeVector2(Vector2(0,0)).x, CAMERA->GetRelativeVector2(Vector2(0, 0)).y, L"던전씬1", 15);
	_D2DRenderer->RenderText(CAMERA->GetRelativeVector2(Vector2(1940,0)).x, CAMERA->GetRelativeVector2(Vector2(1940, 0)).y, L"던전씬2", 15);
	_D2DRenderer->RenderText(CAMERA->GetRelativeVector2(Vector2(1960 + 1920,0)).x, CAMERA->GetRelativeVector2(Vector2(3880, 0)).y, L"던전씬3", 15);

}
