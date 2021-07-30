// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "AIComponent.h"
#include "Actor.h"
#include "AIState.h"
#include <SDL/SDL_log.h>

AIComponent::AIComponent(class Actor* owner)
:Component(owner)
,mCurrentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
	if (mCurrentState)
	{
		mCurrentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	// ���� ���� ���¸� ���� ���´�
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}
	
	// �ʿ��� ���ο� ���¸� ã�´�
	auto iter = mStateMap.find(name);
	if (iter != mStateMap.end())
	{
		mCurrentState = iter->second;
		// ���ο� ���·� �����Ѵ�
		mCurrentState->OnEnter();
	}
	else
	{
		SDL_Log("Could not find AIState %s in state map", name.c_str());
		mCurrentState = nullptr;
	}
}

void AIComponent::RegisterState(AIState* state)
{
	mStateMap.emplace(state->GetName(), state);
}
