#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

GameNode* SceneManager::_currentScene = nullptr;

random_device rd;
mt19937 g(rd());

HRESULT SceneManager::Init()
{
	_currentScene = nullptr;

	_tileImages.emplace_back(IMAGEMANAGER->AddFrameImage(L"terrain", L"Resources/tileAtlas.png", 10, 9));	// 1번

	for (int y = 0; y < GRID_HEIGHT; ++y)
		for (int x = 0; x < GRID_WIDTH; ++x)
			roomOrder[y][x] = 0;

	return S_OK;
}

void SceneManager::Release()
{
	mapSceneIter miSceneList = _sceneList.begin();

	for (; miSceneList != _sceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->Release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _sceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_sceneList.clear();
}

void SceneManager::Update()
{
	if (_currentScene)
	{
		_currentScene->Update();
	}
}

void SceneManager::Render()
{
	if (_currentScene) 
		_currentScene->Render();


		SCENEMANAGER->ScenePlaceByDFS();
	
}

GameNode * SceneManager::AddScene(const wstring& sceneName, GameNode* scene)
{
	if (!scene) 
		return nullptr;

	_sceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(const wstring& sceneName)
{
	mapSceneIter find = _sceneList.find(sceneName);

	if (find == _sceneList.end()) 
		return E_FAIL;

	if (find->second == _currentScene) 
		return S_OK;

	if (SUCCEEDED(find->second->Init()))
	{
		// 어떤 Scene의 정보가 들어 있기 때문에 릴리즈 먼저 해 주고
		if (_currentScene) 
			_currentScene->Release();

		// 현재 Scene에 바꾸려는 Scene을 담는다
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT SceneManager::ChangeSceneToDungeon(const wstring& sceneName)
{
	mapSceneIter find = _sceneList.find(sceneName);

	if (find == _sceneList.end())
		return E_FAIL;

	if (find->second == _currentScene)
		return S_OK;

	if (SUCCEEDED(find->second->Init()))
	{
		// 어떤 Scene의 정보가 들어 있기 때문에 릴리즈 먼저 해 주고
		if (_currentScene)
			_currentScene->Release();

		// 현재 Scene에 바꾸려는 Scene을 담는다
		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

bool SceneManager::check()
{
	if (_currentScene)
		return true;
	else
		return false;
}

Image* SceneManager::GetTileImage(int tileNum)
{
	if (_tileImages.size() <= tileNum || tileNum < 0)
		return nullptr;

	return _tileImages[tileNum];
}

void SceneManager::ScenePlaceByDFS()
{
	_D2DRenderer->RenderText(300, 1040, L"시작", 15);
	srand(static_cast<unsigned int>(time(nullptr)));

	int startX = rand() % GRID_WIDTH;
	int startY = rand() % GRID_HEIGHT;

	SceneManager::GenerateMapDFS(startX, startY);
	SceneManager::PrintMap();

}

// DFS로 랜덤한 경로를 따라 방 생성 (방 수 제한)
void SceneManager::GenerateMapDFS(int x, int y)
{
	if (rooms.size() >= MAX_ROOMS) return;

	visited[y][x] = true;
	rooms.emplace_back(x, y);
	roomOrder[y][x] = rooms.size();  // 순서 저장

	vector<int> dirs = { 0, 1, 2, 3 };
	shuffle(dirs.begin(), dirs.end(), g);

	for (int i = 0; i < 4; ++i) {
		if (rooms.size() >= MAX_ROOMS) break;

		int nx = x + dx[dirs[i]];
		int ny = y + dy[dirs[i]];

		if (SCENEMANAGER->isValid(nx, ny) && !visited[ny][nx]) 
		{
			SceneManager::GenerateMapDFS(nx, ny);
		}
	}
}

// 맵 출력
void SceneManager::PrintMap()
{
	for (int y = 0; y < GRID_HEIGHT; ++y)
	{
		for (int x = 0; x < GRID_WIDTH; ++x)
		{
			visited[y][x] ? _D2DRenderer->RenderText(750 + x * 30, 110 + y * 30, to_wstring(roomOrder[y][x]), 15) : _D2DRenderer->RenderText(750 + x * 30, 110 + y * 30, L"X", 15);
		}
	}
}

