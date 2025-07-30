#include "Actor.h"
#include "Utils/Utils.h"
#include "Engine.h"

#include <Windows.h>
#include <iostream>

Actor::Actor(const char* image, Color color, const Vector2& position)
	: color(color), position(position)
{
	// 문자열 길이
	width = (int)strlen(image);
	
	// 메모리 할당
	this->image = new char[width + 1];

	// 문자열 복사
	strcpy_s(this->image, width + 1, image);
}
Actor::~Actor()
{
	// 메모리 해제
	SafeDeleteArray(image);
}

// 이벤트 함수

// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적)
void Actor::BeginPlay()
{
	hasBeganPlay = true;
}

// 프레임 마다 호출 (반복성 작업 / 지속성이 필요한 작업)
void Actor::Tick(float deltaTime)
{

}

// 그리기 함수
void Actor::Render()
{
	// Win32 API
	// 커서 위치 이동

	// 콘솔 출력을 제어하는 핸들 얻어오기
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 커서 이동
	Utils::SetCursorPosition(position);

	// 색상 설정
	Utils::SetConsoleTextColor(color);

	//그리기
	std::cout << image;
}

void Actor::SetPosition(const Vector2& newPosition)
{
	// 콘솔 출력을 제어하는 핸들 얻어오기
	//static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (position == newPosition)
	{
		return;
	}
	// 지울 위치 확인
	Vector2 direction = newPosition - position;
	position.x = direction.x >= 0 ? position.x : position.x + width - 1;
	
	// 커서 이동
	Utils::SetCursorPosition(position);

	// 문자열 길이 고려해서 지울 위치 확인해야 함
	std::cout << ' ';

	position = newPosition;
}

Vector2 Actor::Position() const
{
	return position;
}

int Actor::Width() const
{
	return width;
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
	// 삭제 요청 되었다고 설정
	isExpired = true;
}

void Actor::QuitGame()
{
	Engine::Get().Quit();
}
