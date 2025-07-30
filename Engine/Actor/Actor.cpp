#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"
#include "Level/Level.h"

#include <Windows.h>
#include <iostream>

Actor::Actor(const char* image, Color color, const Vector2& position)
	: color(color), position(position)
{
	// ���ڿ� ����
	width = (int)strlen(image);
	
	// �޸� �Ҵ�
	this->image = new char[width + 1];

	// ���ڿ� ����
	strcpy_s(this->image, width + 1, image);
}
Actor::~Actor()
{
	// �޸� ����
	SafeDeleteArray(image);
}

// �̺�Ʈ �Լ�

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// ������ ���� ȣ�� (�ݺ��� �۾� / ���Ӽ��� �ʿ��� �۾�)
void Actor::Tick(float deltaTime)
{

}

// �׸��� �Լ�
void Actor::Render()
{
	// Win32 API
	// Ŀ�� ��ġ �̵�

	// �ܼ� ����� �����ϴ� �ڵ� ������
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Ŀ�� �̵�
	Utils::SetCursorPosition(position);

	// ���� ����
	Utils::SetConsoleTextColor(color);

	//�׸���
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// �ܼ� ����� �����ϴ� �ڵ� ������
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// ����ó�� (ȭ�� ������� Ȯ��)
	
	// ���� �����ڸ��� ȭ�� ������ �������
	if (newPosition.x < 0)
	{
		return;
	}

	// ������ �����ڸ��� ȭ�� �������� �������
	if (newPosition.x + width - 1 > Engine::Get().Width())
	{
		return;
	}

	// ���� �����ڸ��� ȭ���� ���� �������
	if (newPosition.y < 0)
	{
		return;
	}

	// ȭ�� �Ʒ��� �������
	if (newPosition.y - 1 > Engine::Get().Height())
	{
		return;
	}

	// ������ ������Ʈ ����
	if (position == newPosition)
	{
		return;
	}
	// ���� ��ġ Ȯ��
	Vector2 direction = newPosition - position;
	position.x = direction.x >= 0 ? position.x : position.x + width - 1;
	
	// Ŀ�� �̵�
	Utils::SetCursorPosition(position);

	// ���ڿ� ���� ����ؼ� ���� ��ġ Ȯ���ؾ� ��
	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

void Actor::SetSortingOrder(unsigned int sortingOrder)
{
	this->sortingOrder = sortingOrder;
}

void Actor::SetOwner(Level* newOwner)
{
	owner = newOwner;
}

Level* Actor::GetOwner()
{
	return owner;
}

void Actor::Destroy()
{
	// ���� ��û �Ǿ��ٰ� ����
	isExpired = true;

	owner->DestroyActor(this);
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}
