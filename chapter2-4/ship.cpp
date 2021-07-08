#include "ship.h"

Ship::Ship(class Game* game)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anim = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	//�ӵ��� ��Ÿ �ð����� ��ġ�� ����
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// ȭ���� ���� ������ ��ġ�� ����
	// ... SetPosition(pos);
}