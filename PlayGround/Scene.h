#pragma once
#include "GameNode.h"
#include "Skeleton.h"
#include "Tile.h"

class Scene : public GameNode
{
	// 타일맵 & 직렬화/역직렬화
public:
	typedef vector<Tile*>						vTileOneLine;
	typedef vector<Tile*>::iterator				viTileOneLine;
	typedef vector<vector<Tile*>>				vTiles;
	typedef vector<vector<Tile*>>::iterator		viTiles;

public:
	Scene();
	virtual ~Scene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

protected:
	wstring _nextScene;

	vTiles _tiles;
	viTiles _tilesIter;

	int _maxX = 0;
	int _maxY = 0;
};

class IntroScene : public Scene
{
public:
	virtual ~IntroScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	Image* _introImage;
};




