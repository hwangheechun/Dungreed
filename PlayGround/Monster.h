#pragma once
#include "GameObject.h"
#include "player.h"

enum class MonsterState : int
{
	IDLE,
	RUN,
	ATTACK,
};

enum class MonsterType : int
{
	SKELETON,
	BELIAL,
};

class Monster : public GameObject
{
public:
	Monster();
	virtual ~Monster();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	MonsterState _monState;
	FloatRect _attackRange;
	float _attackSpeed;
	float _attackTime;
	bool _isLeft = false;

	Player* _player = nullptr;

	//충돌 관련
	bool IsCollide(FloatRect _rect, FloatRect _rect2);
};


