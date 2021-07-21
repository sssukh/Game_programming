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

	// ���� 3.2
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	mRespawnTime -= deltaTime;

	// ���� 3.2
	
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
		// �������� �����ϰ� �������� ��ġ�� ȸ������ ����
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		// �������� ��ٿ� �� �缳��(0.5��)
		mLaserCooldown = 0.5f;
	}
}