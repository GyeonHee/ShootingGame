#include "Level.h"
#include "Actor/Actor.h"


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
	actors.emplace_back(newActor);
	newActor->SetOwner(this);
}

// 이벤트 함수

// 객체 생애주기(Lifetime)에 1번만 호출됨 (초기화 목적)
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
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
