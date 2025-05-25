#pragma once
#include "GameObject.h"
#include "player.h"

class UI : public GameObject
{
public:
	UI();
	virtual ~UI();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Image* _playerHP = nullptr;
	Image* _dashCount = nullptr;
	Image* _mouseCursor = nullptr;

	FloatRect _HPGauge;

	Player* _player = nullptr;
};

