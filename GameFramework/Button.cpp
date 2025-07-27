#include "stdafx.h"
#include "Button.h"

Button::Button(const wstring& imageName, Vector2 pos, int frameX, int frameY, int frameDownX, int frameDownY, function<void(void)> cbFuntion)
	: _cbFunction(cbFuntion)
{
	_direction = ButtonDirection::None;

	_position = pos;

	_image = IMAGEMANAGER->FindImage(imageName);

	_frameUpPoint = { frameX, frameY };
	_frameDownPoint = { frameDownX, frameDownY };

	_rect.Update(_position, Vector2(_image->GetFrameSize()), Pivot::Center);
}

void Button::Init()
{
}

void Button::Release()
{
}

void Button::Update()
{
	RECT rc = _rect.GetRect();
	if (PtInRect(&rc, _ptMouse))	// ��ġ�� ���� ��, ���콺�� RECT �ȿ� �ִٸ�
	{
		if (KEYMANAGER->IsOnceKeyDown(VK_LBUTTON))
		{
			_direction = ButtonDirection::Down;
		}
		else if (_direction == ButtonDirection::Down && KEYMANAGER->IsOnceKeyUp(VK_LBUTTON))
		{
			_direction = ButtonDirection::Up;
			_cbFunction();
		}
	}
}

void Button::Render()
{
	switch (_direction)
	{
	case ButtonDirection::None:
	case ButtonDirection::Up:
		_image->FrameRender(_rect.GetCenter(), _frameUpPoint.x, _frameUpPoint.y);
		break;
	case ButtonDirection::Down:
		_image->FrameRender(_rect.GetCenter(), _frameDownPoint.x, _frameDownPoint.y);
		break;
	}
}
