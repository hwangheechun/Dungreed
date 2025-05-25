#pragma once
#include "GameNode.h"
#include "Skeleton.h"

class Scene : public GameNode
{
	// 타일맵 & 직렬화/역직렬화
public:
	Scene();
	virtual ~Scene() override;

	HRESULT Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

protected:
	wstring _nextScene;
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




