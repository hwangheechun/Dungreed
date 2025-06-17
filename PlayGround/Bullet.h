#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
	Bullet();
	virtual ~Bullet();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//void Init(string a);

	void Move(Vector2 moveDirection);
	void MoveAngle(float speed);

	class AI* _ai;
	bool _isInit;
	Vector2 _direction;

	int countCollide;
	bool _isFire = false;

	//void Trajectory();	//±ËÀû
	Vector2 _gravity;			//Áß·Â
};

