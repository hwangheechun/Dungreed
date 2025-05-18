#pragma once
#include "GameObject.h"
#include "Weapon.h"

class Weapon;

enum class PlayerState : int
{
	IDLE,
	RUN,
	ATTACK,
};

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	Vector2 _cursor;

	void Move(Vector2 moveDirection);
	void Jump();
	void Dash();
	//void Attack(Weapon* weapon);
	void Attack(Weapon* weapon);
	void Operate();

	Image* _playerImage = nullptr;
	Animation* _playerAnimation = nullptr;
	bool _isLeft;
	PlayerState _playerState;

	float _gravity = 0.f;
	bool _isOnGround = false;
	bool _isJumping = false;

	bool _isDash = false;
	int attackCount = 10;

	Weapon* _weapon = nullptr;
};

