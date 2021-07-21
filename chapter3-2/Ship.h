#pragma once
#include "Actor.h"

class Ship :public Actor
{
public:
	Ship(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	//연습3.2
	class CircleComponent* GetCircle() { return mCircle; }
	
private:
	float mLaserCooldown;
	// 연습 3.2
	class CircleComponent* mCircle;
	float mRespawnTime;

};
