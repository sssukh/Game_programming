#include "Asteroid.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) :Actor(game)
{
	//�����ϰ� ��ġ�� ������ �ʱ�ȭ�Ѵ�
	Vector2 randPos = Random::GetVector(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// ��������Ʈ ������Ʈ�� �����ϰ� �ؽ�ó�� �����Ѵ�.
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));
	// �̵� ������Ʈ�� �����ϰ� ���� �ӵ��� �����Ѵ�.
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}