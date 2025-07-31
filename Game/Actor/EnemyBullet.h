#pragma once

#include "Actor/Actor.h"

class EnemyBullet : public Actor
{
	RTTI_DECLARATIONS(EnemyBullet, Actor)
public:
	EnemyBullet(const Vector2& position, float moveSpeed = 15.0f);

	virtual void Tick(float deltaTime) override;
private:

	// 이동 처리를 위한 변수
	float moveSpeed = 15.0f;

	// 부동 소수점으로 이동 위치를 계산할 때 사용할 변수
	float yPosition = 0.0f;
};