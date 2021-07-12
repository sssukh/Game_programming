#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
	Character(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ProcessKeyboard(const uint8_t* state);
	float GetRightSpeed() const { return mRightSpeed; }
	float GetJumpSpeed() const { return mJumpSpeed; }
private:
	float mRightSpeed;
	float mJumpSpeed;
};