#pragma once
#include "Scene.h"
//#include "Bullet.h"

class MainScene : public Scene
{
public:
	virtual ~MainScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	Image* _backGround = nullptr;
};

