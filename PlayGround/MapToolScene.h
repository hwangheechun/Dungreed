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
	vector<vector<Tile*>> _vSampleTiles;	//���� Ÿ��

	vector<MapTool_EnemyInfo> _vEnemies;

	// ���� ��ġ
	POINT _ptMapSize;	//ĭ ��

	Image* _imgTerrainSample;
	Image* _imgTerrain;
	Image* _imgObjectSample;
	Image* _imgObject;
	Image* _imgEnemySample;
	Image* _imgEnemy;
	Image* _imgType;
	int _nTerrainNum = 0;		// �ϴ� 1�����ӹǷ� �ε�����

	// UI ��ġ ���� RECT
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

