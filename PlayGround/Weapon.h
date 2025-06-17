#pragma once
#include "GameObject.h"

enum class WeaponType : int
{
	SWORD,
	GATLINGGUN,
};

class Weapon : public GameObject
{
public:
	Weapon();
	virtual ~Weapon();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	void SetPosition(Vector2 _pos);
	void MoveAngle(float angle);
	float _angle;
	Vector2 _direction;

	Image* _weaponImage = nullptr;

	WeaponType _weaponType;
};

