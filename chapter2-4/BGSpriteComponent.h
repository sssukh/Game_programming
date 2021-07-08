#pragma once
#include "SpriteComponent.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	//�⺻ �׸��� �������� ���� ������ ����( ����̹Ƿ�)
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	//�θ�κ��� �������̵��� Update/draw �Լ�
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer)	override;
	//��濡 ���Ǵ� �ؽ�ó ����
	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	//ȭ�� ũ�⸦ ��ų� ��ũ�� �ӵ����� ���� �� ��� �Լ�
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }
	float GetScrollSpeed() const { return mScrollSpeed; }
private:
	//�� ��� �̹����� ��� �̹����� ������ ���� ĸ��ȭ�� ����ü
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};
