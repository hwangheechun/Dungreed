#pragma once
#include "Scene.h"

class MainScene : public Scene
{
public:
	virtual ~MainScene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	vector<vector<Tile*>> _vTiles;	//test Ãß°¡
	POINT _ptMapSize;	//Ä­ ¼ö
	FloatRect _rcMapView;

	void LoadMapFromFile(const std::wstring& mapFileName);
	Tile* GetTile(int x, int y);

	Image* _imgTerrain;
private:
	Image* _backGround = nullptr;

	Vector2 _dungeonTestPos = Vector2(300, 1040);
};

