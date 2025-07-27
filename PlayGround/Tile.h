#pragma once
#include "GameObject.h"

#define TILE_SIZE 48		// 32 48 64
#define MAX_TILE_X 100
#define MAX_TILE_Y 100
#define SAMPLE_TILE_SIZE	48
#define SAMPLE_TILE_X	10
#define SAMPLE_TILE_Y	10

class Tile : public GameObject
{
public:
	Tile() = default;			// �� �⺻ ������ ����ϰڴٴ� �� (��������� ǥ��)
	virtual ~Tile() = default;

public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetTile(int terX, int terY, int terrainImageNum);
	void SetTiles(int terX, int terY, int terNum, int objX, int objY, int objNum);


	bool CanView() 
	{
		if (CAMERA->GetRect().left < _rect.right &&	CAMERA->GetRect().right > _rect.left &&
			CAMERA->GetRect().top < _rect.bottom &&	CAMERA->GetRect().bottom > _rect.top)
			return true;

		return false;
	}

	bool _blocked = false;		// Ÿ���� �����ִ��� ���� (true: ����, false: ����)
private:
	int _terrainX = -1;			// Ÿ�� �̹��� x �ε���
	int _terrainY = -1;			// Ÿ�� �̹��� y �ε���

	int _terrainImageNum = 0;	// �ʿ�(0), ����(1), ����(2) � �̹��� �������

	int _objectX = -1;
	int _objectY = -1;

	int _objectImageNum = 0;

public:
	int GetTerrainX() { return _terrainX; }
	void SetTerrainX(int x) { _terrainX = x; }

	int GetTerrainY() { return _terrainY; }
	void SetTerrainY(int y) { _terrainY = y; }

	int GetTerrainImageNum() { return _terrainImageNum; }
	void SetTerrainImageNum(int imageNum) { _terrainImageNum = imageNum; }

	int GetObjectX() { return _objectX; }
	void SetObjectX(int x) { _objectX = x; }

	int GetObjectY() { return _objectY; }
	void SetObjectY(int y) { _objectY = y; }

	int GetObjectImageNum() { return _objectImageNum; }
	void SetObjectImageNum(int imageNum) { _objectImageNum = imageNum; }

	bool GetBlocked() { return _blocked; }
	void SetBlocked(bool blocked) { _blocked = blocked; }

	void SetTileRc(int left, int top) { _rect = RectMakePivot(Vector2(left, top), Vector2(TILE_SIZE, TILE_SIZE), Pivot::LeftTop); }
};