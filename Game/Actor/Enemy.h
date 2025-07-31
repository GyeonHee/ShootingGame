#pragma once


#include "Actor/Actor.h"
#include "Utils/Timer.h"

class Enemy : public Actor
{
	// 이동 방향 열거형
	enum class MoveDirection
	{
		None = -1,
		Left,
		Right
	};

	RTTI_DECLARATIONS(Enemy, Actor)
public:
	Enemy(const char* image = "<-=->", int yPosition= 5);

	virtual void Tick(float deltaTime) override;
private:

	// 이동 방향
	MoveDirection direction = MoveDirection::None;

	// 속력을 고려한 이동 위치 계산을 위한 float 변수
	float xPosition = 0.0f;

	// 이동 빠르기
	float moveSpeed = 5.0f;

	// 타이머
	Timer timer;

	// 타이머 계산을 위한 변수

	//// 경과 시간 계산 변수
	//float elapsedTime = 0.0f;

	//// 목표 시간 값
	//float targetTime = 0.0f;
};