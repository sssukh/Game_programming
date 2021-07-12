#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include<algorithm>

Actor::Actor(Game* game)
	:mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	// component를 삭제해야한다.
	// ~Component가 RemoveComponent를 호출하기 때문에 다른 스타일의 루프가 필요
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	// 정렬된 벡터에서 새로 삽입할 지점을 찾는다.
	// (삽입할 component보다 order가 높은 첫번째 component)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; 
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}