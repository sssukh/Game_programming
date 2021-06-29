#include "Game.h"

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