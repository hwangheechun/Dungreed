#pragma once
#include "Scene.h"

class TownScene : public Scene
{
public:
	virtual ~TownScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	Image* _townBackGround = nullptr;
};

