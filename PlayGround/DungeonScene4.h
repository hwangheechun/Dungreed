#pragma once
#include "Scene.h"

class DungeonScene4 : public Scene
{
public:
	virtual ~DungeonScene4() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:

};