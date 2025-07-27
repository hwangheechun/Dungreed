#include "stdafx.h"
#include "DungeonScene3.h"

DungeonScene3::~DungeonScene3()
{
}

HRESULT DungeonScene3::Init()
{
    return S_OK;
}

void DungeonScene3::Release()
{
}

void DungeonScene3::Update()
{
}

void DungeonScene3::Render()
{
	_D2DRenderer->RenderText(550, 800, L"´øÀü¾À3", 15);
}
