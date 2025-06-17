#pragma once
#include "Scene.h"

class DungeonScene : public Scene
{
public:
	virtual ~DungeonScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;
private:
	Image* _townBackGround = nullptr;
};

