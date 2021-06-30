#include "Game.h"

Game::Game()
{
	mTicksCount = 0;
}

void Game::AddActor(Actor* actor)
{
	//���͸� ���� ���̶�� ��� ���Ϳ� ���͸� �߰�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)// actor ����
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

	// ��� ���͸� ����
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//��� ���� ���͸� mActors�� �̵�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���� ���͸� �ӽ� ���Ϳ� �߰�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}


	// ���� ���� ����(mActors���� �߷��� ���͵�)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}