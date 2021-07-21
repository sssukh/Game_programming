#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"

Ship::Ship(Game* game)
	:Actor(game)
	, mLaserCooldown(0.0f)
	, mRespawnTime(0.0f)
{
	
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("Assets/Ship.png"));
	

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_W);
	ic->SetBackKey(SDL_SCANCODE_S);
	ic->SetClockwiseKey(SDL_SCANCODE_A);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);

	// 연습 3.2
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	mRespawnTime -= deltaTime;

	// 연습 3.2
	
	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			
			mRespawnTime = 2.0f;
			this->SetScale(0.0f);
			mLaserCooldown = 1.5f;
			break;
		}
	}
	if (mRespawnTime < 0.5f&&mRespawnTime>0.0f)
	{	
		SetPosition(Vector2(512.0f, 384.0f));
		this->SetScale(1.0f);
		
		
	}
	
}

void Ship::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown < 0.0f)
	{
		// 레이저를 생성하고 레이저의 위치와 회전값을 설정
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// 레이저의 쿨다운 값 재설정(0.5초)
		mLaserCooldown = 0.5f;
	}
}