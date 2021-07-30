// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "NavComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include <algorithm>

//연습 4.1
#include "AIState.h"
#include "AIComponent.h"

Enemy::Enemy(class Game* game)
	:Actor(game)
	
{
	// Add to enemy vector
	game->GetEnemies().emplace_back(this);
	
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Airplane.png"));
	// Set position at start tile
	SetPosition(GetGame()->GetGrid()->GetStartTile()->GetPosition());
	// Setup a nav component at the start tile
	NavComponent* nc = new NavComponent(this);
	nc->SetForwardSpeed(150.0f);
	nc->StartPath(GetGame()->GetGrid()->GetStartTile());
	// Setup a circle for collision
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(25.0f);

	//연습 4.1
	mAI = new AIComponent(this);
	AIDeath* dead = new AIDeath(mAI);
	AIPatrol* patrol = new AIPatrol(mAI);
	mAI->RegisterState(dead);
	mAI->RegisterState(patrol);
	mAI->ChangeState("Patrol");
}

Enemy::~Enemy()
{
	// Remove from enemy vector
	auto iter = std::find(GetGame()->GetEnemies().begin(),
						  GetGame()->GetEnemies().end(),
						  this);
	GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	
	// Am I near the end tile?
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Length(), 10.0f))
	{
		mAI->ChangeState("Death");
		SetState(EDead);
	}
}
