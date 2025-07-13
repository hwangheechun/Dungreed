#pragma once
#include "../GameFramework/GameNode.h"
#include "EventManager.h"
#include "MainScene.h"
#include "TownScene.h"
#include "DungeonScene.h"
#include "MapToolScene.h"

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

