#pragma once
#include "Scene.h"

class DungeonScene3 : public Scene
{
public:
	virtual ~DungeonScene3() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:

};