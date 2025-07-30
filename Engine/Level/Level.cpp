#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>

Level::Level()
{

}
Level::~Level()
{
	// null 확인 후 액터 제거
	for (Actor* actor : actors)
	{
		//// null 확인 후 Actor 제거
		//if (actor)
		//{
		//	// 삭제 및 메모리 정리
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}
}

// 레벨에 액터를 추가할 때 사용
void Level::AddActor(Actor* newActor)
{
	// 예외처리(중복 여부 확인) 필요

	// push_back / emplace_back : 배열 맨 뒤에 새로운 항목 추가하는 함수
	
	// 대기 배열에 추가
	addRequestedActors.emplace_back(newActor);
	
	//newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	// 대기 배열에 추가
	destroyRequestedActors.emplace_back(destroyedActor);
}

// 이벤트 함수

// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적)
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		// 액터 처리 여부 확인
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// 이미 호출된 개체는 건너뛰기
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

// 프레임 마다 호출 (반복성 작업 / 지속성이 필요한 작업)
void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		// 액터 처리 여부 확인
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Tick(deltaTime);
	}
}

// 그리기 함수
void Level::Render()
{
	// 그리기 전에 정렬 순서 기준으로 재배치(정렬)
	SortActorsBySortingOrder();

	// Render Pass
	for (Actor* const actor : actors)
	{
		// 액터 처리 여부 확인
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// 검사(같은 위치에 정렬 순서 높은 액터가 있는지 확인)
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// 같은 액터면 무시
			if (actor == otherActor)
			{
				continue;
			}

			// 위치가 같은 액터 확인
			if (actor->Position() == otherActor->Position())
			{
				// 정렬 순서 비교 후 액터 저장
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					// 저장 및 루프 종료
					searchedActor = otherActor;
					break;
				}
			}
		}

		// 어떤 액터와 같은 위치에 정렬 순서가 더 높은 액터가 있으면
		// 그리지 않고 건너뛰기
		if (searchedActor)
		{
			continue;
		}

		// 드로우 콜
		actor->Render();
	}
}

void Level::ProcessAddAndDestroyActors()
{
	// actors 배열에서 제외 처리
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		// 삭제 요청된 액터인지 확인 후 배열에서 제외
		if ((*iterator)->isExpired)
		{
			// erase 함수를 사용하면 iterator가 무효화되기 때문에
			// 반환되는 값을 저장해야함/
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	// destroyedActors 배열을 순회하면서 액터 delete
	for (auto* actor : destroyRequestedActors)
	{
		// 액터가 그렸던 곳 지우기
		Utils::SetCursorPosition(actor->position);

		// 콘솔에 빈문자 출력해서 지우기
		for (int i = 0; i < actor->width; ++i)
		{
			std::cout << " ";
		}

		// 리소스 해제
		SafeDelete(actor);
	}

	// 배열 초기화
	destroyRequestedActors.clear();

	// addRequestedActors 배열을 순회하면서 새로운 액터 add
	for (auto* const actor : addRequestedActors)
	{
		actors.emplace_back(actor);
		actor->SetOwner(this);
	}

	addRequestedActors.clear();
}

void Level::SortActorsBySortingOrder()
{
	for (int i = 0; i < (int)actors.size(); ++i)
	{
		for (int j = 0; j < (int)actors.size() - 1; ++j)
		{
			// sortingOrder 값이 클수록 뒤 쪽에 배치
			if (actors[j]->sortingOrder > actors[j + 1]->sortingOrder)
			{
				std::swap(actors[j], actors[j + 1]);
			}
		}
	}
}
