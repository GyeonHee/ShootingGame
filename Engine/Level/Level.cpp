#include "Level.h"
#include "Actor/Actor.h"


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
	actors.emplace_back(newActor);
	newActor->SetOwner(this);
}

// �̺�Ʈ �Լ�

// ��ü �����ֱ�(Lifetime)�� 1���� ȣ��� (�ʱ�ȭ ����)
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

// ������ ���� ȣ�� (�ݺ��� �۾� / ���Ӽ��� �ʿ��� �۾�)
void Level::Tick(float deltaTime)
{
	for (Actor* const actor : actors)
	{
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
