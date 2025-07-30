#include "Level.h"
#include "Actor/Actor.h"
#include "Utils/Utils.h"
#include <iostream>

Level::Level()
{

}
Level::~Level()
{
	// null Ȯ�� �� ���� ����
	for (Actor* actor : actors)
	{
		//// null Ȯ�� �� Actor ����
		//if (actor)
		//{
		//	// ���� �� �޸� ����
		//	delete actor;
		//	actor = nullptr;
		//}

		SafeDelete(actor);
	}
}

// ������ ���͸� �߰��� �� ���
void Level::AddActor(Actor* newActor)
{
	// ����ó��(�ߺ� ���� Ȯ��) �ʿ�

	// push_back / emplace_back : �迭 �� �ڿ� ���ο� �׸� �߰��ϴ� �Լ�
	
	// ��� �迭�� �߰�
	addRequestedActors.emplace_back(newActor);
	
	//newActor->SetOwner(this);
}

void Level::DestroyActor(Actor* destroyedActor)
{
	// ��� �迭�� �߰�
	destroyRequestedActors.emplace_back(destroyedActor);
}

// �̺�Ʈ �Լ�

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����)
void Level::BeginPlay()
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �̹� ȣ��� ��ü�� �ǳʶٱ�
		if (actor->HasBeganPlay())
		{
			continue;
		}

		actor->BeginPlay();
	}
}

// ������ ���� ȣ�� (�ݺ��� �۾� / ���Ӽ��� �ʿ��� �۾�)
void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		actor->Tick(deltaTime);
	}
}

// �׸��� �Լ�
void Level::Render()
{
	// �׸��� ���� ���� ���� �������� ���ġ(����)
	SortActorsBySortingOrder();

	// Render Pass
	for (Actor* const actor : actors)
	{
		// ���� ó�� ���� Ȯ��
		if (!actor->isActive || actor->isExpired)
		{
			continue;
		}

		// �˻�(���� ��ġ�� ���� ���� ���� ���Ͱ� �ִ��� Ȯ��)
		Actor* searchedActor = nullptr;
		for (Actor* const otherActor : actors)
		{
			// ���� ���͸� ����
			if (actor == otherActor)
			{
				continue;
			}

			// ��ġ�� ���� ���� Ȯ��
			if (actor->Position() == otherActor->Position())
			{
				// ���� ���� �� �� ���� ����
				if (actor->sortingOrder < otherActor->sortingOrder)
				{
					// ���� �� ���� ����
					searchedActor = otherActor;
					break;
				}
			}
		}

		// � ���Ϳ� ���� ��ġ�� ���� ������ �� ���� ���Ͱ� ������
		// �׸��� �ʰ� �ǳʶٱ�
		if (searchedActor)
		{
			continue;
		}

		// ��ο� ��
		actor->Render();
	}
}

void Level::ProcessAddAndDestroyActors()
{
	// actors �迭���� ���� ó��
	for (auto iterator = actors.begin(); iterator != actors.end();)
	{
		// ���� ��û�� �������� Ȯ�� �� �迭���� ����
		if ((*iterator)->isExpired)
		{
			// erase �Լ��� ����ϸ� iterator�� ��ȿȭ�Ǳ� ������
			// ��ȯ�Ǵ� ���� �����ؾ���/
			iterator = actors.erase(iterator);
			continue;
		}

		++iterator;
	}

	// destroyedActors �迭�� ��ȸ�ϸ鼭 ���� delete
	for (auto* actor : destroyRequestedActors)
	{
		// ���Ͱ� �׷ȴ� �� �����
		Utils::SetCursorPosition(actor->position);

		// �ֿܼ� ���� ����ؼ� �����
		for (int i = 0; i < actor->width; ++i)
		{
			std::cout << " ";
		}

		// ���ҽ� ����
		SafeDelete(actor);
	}

	// �迭 �ʱ�ȭ
	destroyRequestedActors.clear();

	// addRequestedActors �迭�� ��ȸ�ϸ鼭 ���ο� ���� add
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
			// sortingOrder ���� Ŭ���� �� �ʿ� ��ġ
			if (actors[j]->sortingOrder > actors[j + 1]->sortingOrder)
			{
				std::swap(actors[j], actors[j + 1]);
			}
		}
	}
}
