#pragma once
#include "Scene.h"

class DungeonStartScene1 : public Scene
{
public:
	virtual ~DungeonStartScene1() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:

};

