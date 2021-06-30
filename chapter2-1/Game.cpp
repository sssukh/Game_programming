#include "Game.h"

Game::Game()
{
	mTicksCount = 0;
}

void Game::AddActor(Actor* actor)
{
	//액터를 갱신 중이라면 대기 벡터에 액터를 추가
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)// actor 삭제
{
	for (int i=0;i<mActors.size();i++)
	{
		if (mActors[i] == actor)
		{
			mActors.erase(mActors.begin()+i);
			return;
		}
	}
	for (int i = 0; i < mPendingActors.size(); i++)
	{
		if (mPendingActors[i] == actor)
		{
			mPendingActors.erase(mPendingActors.begin() + i);
			break;
		}
	}
}

void Game::UpdateGame()
{

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 모든 액터를 갱신
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//대기 중인 액터를 mActors로 이동
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 죽은 액터를 임시 벡터에 추가
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}


	// 죽은 액터 제거(mActors에서 추려낸 액터들)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}