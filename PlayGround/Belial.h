#pragma once
#include "Monster.h"

class Belial : public Monster
{
public:
	Belial();
	virtual ~Belial();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//∆»
	FloatRect _leftHandRect;
	Image* _belialLeftHandImage = nullptr;
	Animation* _belialLeftHand = nullptr;

	FloatRect _rightHandRect;
	Image* _belialRightHandImage = nullptr;
	Animation* _belialRightHand = nullptr;

	//¿ÃπÃ¡ˆ
	Image* _belialImage = nullptr;
	Image* _belialIdleImage = nullptr;
	Image* _belialAttackImage = nullptr;
	Animation* _belialIdle = nullptr;
	Animation* _belialAttack = nullptr;

	bool _isAttack = false;
	bool _isLeft = false;

	void Razor();
};

