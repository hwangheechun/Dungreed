#pragma once
#include "GameObject.h"
#include "Weapon.h"

enum class ItemState : int
{
	DEFAULT,
	EQUIP_RELEASE,
	ITEM_MOVE,
};

class Inventory : public GameObject
{
public:
	Inventory();
	virtual ~Inventory();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Image* _invenImage = nullptr;

	
	vector<FloatRect> _equipSlot{ 2 };	//장비 슬롯 
	vector<FloatRect> _equipList{ 15 };	//장비 목록
	/*vector<bool> _isSlotCliked{ 2 };
	vector<bool> _isListCliked{ 15 };*/
	//vector<bool> _isSlotCliked = { true, false, false, true, true };
	bool  _isClicked = false;
	bool  _isSlotCliked[2] = { 0, 0 };
	bool  _isEquipCliked[2] = { 0, 0 };
	bool  _isListCliked[15];

	vector<Image*> _equipSlotImage{ 2 };
	vector<Image*> _equipListImage{ 15 };

	bool _isEquiped[2] = { 0,0 };
	bool _isExist[15];
	ItemState _itemState;

	void CleanSlotValue();
	void CleanListValue();
	void CleanListImage();
};
