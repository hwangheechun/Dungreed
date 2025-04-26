#pragma once
#include "../GameFramework/GameNode.h"
#include "Shantae.h"
#include "Ground.h"
#include "UI.h"
#include "Camera.h"
#include "Obstacle.h"
#include "Scene.h"
#include "EventManager.h"

class PlayGround : public GameNode
{	
public:
	PlayGround() = default;
	virtual ~PlayGround() = default;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

