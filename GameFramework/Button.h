#pragma once
#include "GameObject.h"

enum class ButtonDirection : int
{
	None,
	Up,
	Down,
};

class Button : public GameObject
{
public:
	Button() = delete;
	Button(const wstring& imageName, Vector2 pos, int frameX, int frameY, int frameDownX, int frameDownY, function<void(void)> cbFuntion);
	~Button() = default;

public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

private:
	ButtonDirection _direction = ButtonDirection::None;		// ���� ����

	Image* _image = nullptr;		// �̹���

	POINT _frameDownPoint;
	POINT _frameUpPoint;

	function<void(void)> _cbFunction;		// �ݹ� �Լ�
};

