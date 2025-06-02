#include "stdafx.h"
#include "Tile.h"

void Tile::Init()
{
}

void Tile::Release()
{
}

void Tile::Update()
{
}

void Tile::Render()
{
	auto pImage = SCENEMANAGER->GetTileImage(_terrainImageNum);

	if (pImage) 
	{
		pImage->SetSize(Vector2(TILE_SIZE, TILE_SIZE));
		pImage->FrameRender(CAMERA->GetRelativeVector2(_rect.GetCenter()), _terrainX, _terrainY);
	}
}

void Tile::SetTile(int terX, int terY, int terrainImageNum)
{
	_terrainX = terX;
	_terrainY = terY;
	_terrainImageNum = terrainImageNum;
}
