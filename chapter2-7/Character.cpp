#include "Character.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Character::Character(class Game* game)
	:Actor(game), mRightSpeed(0.0f), mJumpSpeed(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Character01.png"),
		game->GetTexture("Assets/Character02.png"),
		game->GetTexture("Assets/Character03.png"),
		game->GetTexture("Assets/Character04.png"),
		game->GetTexture("Assets/Character05.png"),
		game->GetTexture("Assets/Character06.png"),
		
		game->GetTexture("Assets/Character07.png"),
		game->GetTexture("Assets/Character08.png"),
		game->GetTexture("Assets/Character09.png"),
		game->GetTexture("Assets/Character10.png"),
		game->GetTexture("Assets/Character11.png"),
		game->GetTexture("Assets/Character12.png"),
		game->GetTexture("Assets/Character13.png"),
		game->GetTexture("Assets/Character14.png"),
		game->GetTexture("Assets/Character15.png"),
		game->GetTexture("Assets/Character16.png"),
		game->GetTexture("Assets/Character17.png"),
		game->GetTexture("Assets/Character18.png")
		
	};
	asc->SetAnimTextures(anims);
	asc->SetRoutine(false);
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mJumpSpeed * deltaTime;

	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 700.0f) 
	{
		pos.y = 700.0f;
	}
	SetPosition(pos);
}

void Character::ProcessKeyboard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mJumpSpeed = 0.0f;

	if (state[SDL_SCANCODE_RIGHT])
	{
		mRightSpeed += 150.0f;
	}
	if (state[SDL_SCANCODE_LEFT])
	{
		mRightSpeed -= 150.0f;
	}
	if (state[SDL_SCANCODE_UP])
	{
		mJumpSpeed -= 300.0f;
	}
	if (state[SDL_SCANCODE_DOWN])
	{
		mJumpSpeed += 300.0f;
	}
}