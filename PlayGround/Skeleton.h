#pragma once
#include "Monster.h"

class Skeleton : public Monster
{
public:
	Skeleton();
	virtual ~Skeleton();

	void Init() override;
	void Release() override;
	void Update() override;
	void Render() override;

	//¿ÃπÃ¡ˆ
	Image* _skeletonImage = nullptr;
	Image* _skeletonIdleImage = nullptr;
	Image* _skeletonAttackImage = nullptr;
	Animation* _skeletonIdle = nullptr;
	Animation* _skeletonAttack = nullptr;

	bool _isAttack = false;
};

