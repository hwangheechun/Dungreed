#pragma once
#include "Scene.h"

class DungeonScene2 : public Scene
{
public:
	virtual ~DungeonScene2() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	
};

