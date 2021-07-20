#include "Asteroid.h"
#include "Game.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Actor.h"

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
}