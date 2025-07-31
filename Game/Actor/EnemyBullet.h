#pragma once

#include "Actor/Actor.h"

class EnemyBullet : public Actor
{
	RTTI_DECLARATIONS(EnemyBullet, Actor)
public:
	EnemyBullet(const Vector2& position, float moveSpeed = 15.0f);

	virtual void Tick(float deltaTime) override;
private:

	// �̵� ó���� ���� ����
	float moveSpeed = 15.0f;

	// �ε� �Ҽ������� �̵� ��ġ�� ����� �� ����� ����
	float yPosition = 0.0f;
};