#pragma once
#include "Scene.h"

enum class EditMode : int
{
	Terrain,
	Object,
	Enemy,
	Type,
	End,
};

enum class PenMode : int
{
	Plus,
	Minus,
	End,
};

struct MapTool_EnemyInfo
{
	int tileX;
	int tileY;
	int frameX;
	int frameY;
	int enemyType;
};

struct MapTool_ObjectInfo
{

};

class MapToolScene : public Scene
{
public:
	MapToolScene() = default;
	virtual ~MapToolScene() = default;

public:
	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	vector<vector<Tile*>> _vTiles;	
	vector<vector<Tile*>> _vSampleTiles;	//샘플 타일

	vector<MapTool_EnemyInfo> _vEnemies;

	// 현재 위치
	POINT _ptMapSize;	//칸 수

	Image* _imgTerrainSample;
	Image* _imgTerrain;
	Image* _imgObjectSample;
	Image* _imgObject;
	Image* _imgEnemySample;
	Image* _imgEnemy;
	Image* _imgType;
	int _nTerrainNum = 0;		// 일단 1개ㅇㅣ므로 인덱스만

	// UI 위치 관련 RECT
	FloatRect _rcMapView;
	FloatRect _rcSampleView;
	FloatRect _rcSampleSelect;

	POINT _ptSampleStart;
	int _terrainPage = 0;

	POINT _ptDrawStart;

	FloatRect _rcEditMode[(int)EditMode::End];
	FloatRect _rcPenMode[(int)PenMode::End];
	EditMode _eEditMode = EditMode::Terrain;
	PenMode _ePenMode = PenMode::Plus;

	FloatRect _rcNonBlocked;
	FloatRect _rcBlocked;

public:
	void SaveMap();
	void LoadMap();

	void LoadMapFromFile(const std::wstring& mapFileName);
};

