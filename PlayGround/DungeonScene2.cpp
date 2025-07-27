#include "stdafx.h"
#include "DungeonScene2.h"

DungeonScene2::~DungeonScene2()
{
}

HRESULT DungeonScene2::Init()
{
    return S_OK;
}

void DungeonScene2::Release()
{
}

void DungeonScene2::Update()
{
}

void DungeonScene2::Render()
{
	_D2DRenderer->RenderText(550, 800, L"´øÀü¾À2", 15);
}
