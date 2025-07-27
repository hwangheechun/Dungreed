#pragma once
#include "SingletonBase.h"
#include <map>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define GRID_WIDTH 4		// 맵 구조를 4x4로 설정
#define GRID_HEIGHT 4
#define MAX_ROOMS 8		// 최대 방 수 제한

class GameNode;

const int dx[] = { 0, 0, -1, 1 };
const int dy[] = { -1, 1, 0, 0 };

class SceneManager final : public SingletonBase<SceneManager>
{
public:
	typedef map<wstring, GameNode*>			 mapSceneList;
	typedef map<wstring, GameNode*>::iterator mapSceneIter;

	struct Room
	{
		int x, y;
		Room(int x, int y) : x(x), y(y) {}
	};

	bool visited[GRID_HEIGHT][GRID_WIDTH] = { false };
	int roomOrder[GRID_HEIGHT][GRID_WIDTH]; // 방 생성 순서 저장
	vector<Room> rooms;	//방 정보를 저장하는 벡터

private:
	static GameNode* _currentScene;
	mapSceneList _sceneList;

	vector<Image*> _tileImages;		// 필요에 따라서 확장

protected:
	SceneManager() = default;
	virtual ~SceneManager() = default;

	friend class SingletonBase<SceneManager>;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render();

	GameNode* AddScene(const wstring& sceneName, GameNode* scene);

	HRESULT ChangeScene(const wstring& sceneName);
	HRESULT ChangeSceneToDungeon(const wstring& sceneName);

	bool check();

	Image* GetTileImage(int tileNum);

	void ScenePlaceByDFS();	//방 DFS를 이용하여 생성하고 배치

	bool isValid(int x, int y) { return x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT; }	//방 위치를 벗어나지 않도록 체크	
	void GenerateMapDFS(int x, int y);
	void PrintMap();
};

