#pragma once
#include "../GameFramework/GameNode.h"
#include "EventManager.h"
#include "MainScene.h"
#include "TownScene.h"
#include "DungeonScene.h"
#include "MapToolScene.h"
#include "DungeonStartScene1.h"
#include "DungeonScene1.h"
#include "DungeonScene2.h"
#include "DungeonScene3.h"

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

