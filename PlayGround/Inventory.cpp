#include "stdafx.h"
#include "Inventory.h"
#include <string>

Inventory::Inventory()
{
	Init();
}

Inventory::~Inventory()
{
}

void Inventory::Init()
{
	_name = L"Inventory";
	_position = Vector2(1600, WINSIZEY / 2);
	_size = Vector2(WINSIZEX / 3, WINSIZEY);	//640
	_active = false;

	_invenImage = IMAGEMANAGER->AddImage(L"inven", L"Resources/InventoryBase.png");
	//_weapon = dynamic_cast<Weapon*>(OBJECTMANAGER->FindObject(ObjectType::Item, L"Weapon"));

	/*FloatRect test = RectMakePivot(Vector2(365, 200), Vector2(80, 80), Pivot::Center);
	FloatRect test2 = RectMakePivot(Vector2(445, 200), Vector2(80, 80), Pivot::Center);
	FloatRect test3 = RectMakePivot(Vector2(525, 200), Vector2(80, 80), Pivot::Center);*/

	/*_equipList.push_back(&RectMakePivot(Vector2(365, 200), Vector2(80, 80), Pivot::Center));
	_equipList.push_back(&RectMakePivot(Vector2(445, 200), Vector2(80, 80), Pivot::Center));
	_equipList.push_back(&RectMakePivot(Vector2(525, 200), Vector2(80, 80), Pivot::Center));*/

	/**_equipList[0] = RectMakePivot(Vector2(365, 200), Vector2(80, 80), Pivot::Center);
	*_equipList[1] = RectMakePivot(Vector2(445, 200), Vector2(80, 80), Pivot::Center);
	*_equipList[2] = RectMakePivot(Vector2(525, 200), Vector2(80, 80), Pivot::Center);*/

	/*for (int i = 0; i < 15; i++)
	{
		_equipList.push_back()
	}*/
	//*_equipList[0] = RectMakePivot(Vector2(365, 200), Vector2(80, 80), Pivot::Center);

	for (int i = 0; i < 2; i++)
	{
		_equipSlot[i] = RectMakePivot(_position + Vector2(-180 + 100 * i, -200), Vector2(90, 90), Pivot::Center);
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			_equipList[i * 5 + j] = RectMakePivot(_position + Vector2(-180 + 100 * j, 100 * i), Vector2(90, 90), Pivot::Center);
		}
	}

	//test4 = RectMakePivot(Vector2(605, 200), Vector2(80, 80), Pivot::Center);
}

void Inventory::Release()
{
}

void Inventory::Update()
{
	_rect = RectMakePivot(_position, _size, Pivot::Center);
}

void Inventory::Render()
{
	//_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);
	//_invenImage->Render(_position);


	
	/*_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(-180, 0), Vector2(80,80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(-90, 0), Vector2(80,80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(0, 0), Vector2(80,80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(90, 0), Vector2(80,80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(180, 0), Vector2(80,80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);

	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(-180, 90), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(-90, 90), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(0, 90), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(90, 90), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(180, 90), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);

	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(-180, 180), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(-90, 180), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(0, 180), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(90, 180), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);
	_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(180, 180), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Black, 2.0f);*/
	
	for (int i = 0; i < 2; i++)
	{
		_D2DRenderer->DrawRectangle(_equipSlot[i], D2DRenderer::DefaultBrush::Red, 2.0f);
	}

	for (int i = 0; i < 15; i++)
	{
		_D2DRenderer->DrawRectangle(_equipList[i], D2DRenderer::DefaultBrush::Red, 2.0f);
	}
	//_D2DRenderer->DrawRectangle(RectMakePivot(_position + Vector2(65, 0), Vector2(80, 80), Pivot::Center), D2DRenderer::DefaultBrush::Red, 2.0f);

	/*_D2DRenderer->RenderText(300, 300, L"크기기기 : " + to_wstring((int)_equipList.size()), 15);
	_D2DRenderer->RenderText(300, 300, L"크기기기 : " + to_wstring((int)_equipList[0]), 15);
	_D2DRenderer->RenderText(300, 350, L"크기기기 : " + to_wstring((int)_equipList[1]), 15);
	_D2DRenderer->RenderText(300, 400, L"크기기기 : " + to_wstring((int)_equipList[2]), 15);
	_D2DRenderer->RenderText(300, 400, L"크기기기 : " + to_wstring((int)_equipList[3]), 15);*/
}