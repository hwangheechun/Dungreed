#pragma once
#include "GameObject.h"
//#include "Weapon.h"
#include "Inventory.h"

class Weapon;
class Inventory;

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
	bool _isSlashDown = false;

	Weapon* _weapon = nullptr;
	Inventory* _inventory = nullptr;

	//충돌 관련
	bool IsCollide(FloatRect _rect, FloatRect _rect2);
	bool IsCollide(Vector2 _point, FloatRect _rect);

	//체력 관련a
	float _maxHP = 80.f;
	float _hp = 80.f;
};

