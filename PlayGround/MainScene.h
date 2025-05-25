#pragma once
#include "Scene.h"
#include "player.h"
#include "UI.h"

#include "TownScene.h"

class MainScene : public Scene
{
public:
	virtual ~MainScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	
};

