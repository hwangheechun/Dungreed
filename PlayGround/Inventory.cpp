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

	_itemState = ItemState::DEFAULT;
}

void Inventory::Release()
{
}

void Inventory::Update()
{
	_rect = RectMakePivot(_position, _size, Pivot::Center);

	for (int i = 0; i < 15; i++)
	{
		if (_equipListImage[i])
			_isExist[i] = true;
		else
			_isExist[i] = false;
	}

	if (_isSlotCliked[0] && _equipSlotImage[0] || _isSlotCliked[1] && _equipSlotImage[1])	//슬롯 2개 중 장착된 장비가 있는 칸을 클릭하면
	{
		_itemState = ItemState::EQUIP_RELEASE;
	}
	else
	{
		for (int i = 0; i < 15; i++)
		{
			if(_isListCliked[i])
			{
				_itemState = ItemState::ITEM_MOVE;
				break;
			}
			else
				_itemState = ItemState::DEFAULT;
		}
		
	}
}

void Inventory::Render()
{
	//_D2DRenderer->FillRectangle(_rect, D2DRenderer::DefaultBrush::White);
	_D2DRenderer->DrawRectangle(_rect, D2DRenderer::DefaultBrush::Black, 2.0f);
	//_invenImage->Render(_position);
	
	for (int i = 0; i < 2; i++)
	{
		_D2DRenderer->DrawRectangle(_equipSlot[i], D2DRenderer::DefaultBrush::Red, 2.0f);
	}

	for (int i = 0; i < 15; i++)
	{
		_D2DRenderer->DrawRectangle(_equipList[i], D2DRenderer::DefaultBrush::Red, 2.0f);
	}

	if (_equipSlotImage[0])
		_equipSlotImage[0]->Render(_equipSlot[0].GetCenter());

	if (_equipSlotImage[1])
		_equipSlotImage[1]->Render(_equipSlot[1].GetCenter());

	for (int i = 0; i < 15; i++)
	{
		if (_equipListImage[i])
			_equipListImage[i]->Render(_equipList[i].GetCenter());
	}

	for (int i = 0; i < 2; i++)
		_D2DRenderer->RenderText(1350 + i * 100, 200, to_wstring((int)_isSlotCliked[i]), 15);
	for (int i = 0; i < 15; i++)
		_D2DRenderer->RenderText(1350 + i * 20, 250, to_wstring((int)_isListCliked[i]), 15);

	_D2DRenderer->RenderText(300, 300, L"장비 슬롯 1 이미지가 있나? : " + to_wstring((int)_isEquiped[0]), 15);
	_D2DRenderer->RenderText(300, 325, L"장비 슬롯 2 이미지가 있나? : " + to_wstring((int)_isEquiped[1]), 15);

	for(int i = 0; i < 15; i++)
		_D2DRenderer->RenderText(300, 380 + 20 * i, to_wstring(i) + L"장비 목록 이미지가 있나? : " + to_wstring((int)_isExist[i]), 15);
	_D2DRenderer->RenderText(400, 350, L"뭐든지 클릭? : " + to_wstring((int)_isClicked), 15);
	_D2DRenderer->RenderText(700, 350, L"아이템 상태 : " + to_wstring((int)_itemState), 15);
	switch (_itemState)
	{
	case ItemState::DEFAULT:
		_D2DRenderer->RenderText(700, 370, L"기본 상태 : ", 15);
		break;
	case ItemState::EQUIP_RELEASE:
		_D2DRenderer->RenderText(700, 370, L"아이템 장착 해제하려는 상태 : ", 15);
		break;
	case ItemState::ITEM_MOVE:
		_D2DRenderer->RenderText(700, 370, L"아이템 옮기는 상태 : ", 15);
		break;
	}

}

void Inventory::CleanSlotValue()
{
	for (int i = 0; i < 2; i++)
	{
		_isSlotCliked[i] = false;
	}
}

void Inventory::CleanListValue()
{
	for (int i = 0; i < 15; i++)
	{
		_isListCliked[i] = false;
	}
}

void Inventory::CleanListImage()
{
	for (int i = 0; i < 15; i++)
	{
		_equipListImage[i] = nullptr;
	}
}