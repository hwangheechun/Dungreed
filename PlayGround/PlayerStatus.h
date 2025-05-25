#pragma once
#include "UI.h"


class PlayerStatus : public UI
{
	PlayerStatus();
	virtual ~PlayerStatus();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
};

