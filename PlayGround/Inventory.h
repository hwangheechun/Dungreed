#pragma once
#include "GameObject.h"
#include "Weapon.h"

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
	bool  _isSlotCliked[2] = { 0, 0 };
	bool  _isEquipCliked[2] = { 0, 0 };
	bool  _isListCliked[15];
	/*vector<bool> _isSlotCliked2{ 2 };
	vector<bool> _isListCliked2{ 15 };*/

	Image* _equipSlot1 = nullptr;
	Image* _equipSlot2 = nullptr;
	vector<Image*> _equipListImage{ 15 };
};
