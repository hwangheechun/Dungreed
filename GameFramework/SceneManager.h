#pragma once
#include "SingletonBase.h"
#include <map>

class GameNode;

class SceneManager final : public SingletonBase<SceneManager>
{
public:
	typedef map<wstring, GameNode*>			 mapSceneList;
	typedef map<wstring, GameNode*>::iterator mapSceneIter;

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

	bool check();

	Image* GetTileImage(int tileNum);
};

