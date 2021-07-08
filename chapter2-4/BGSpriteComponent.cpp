#include "BGSpriteComponent.h"

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		//�� �ؽ�ó�� �������� ȭ���� �ʺ� * count ��.
		temp.mOffset.x = count;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
		count++;
	}
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGTextures)
	{
		//x������ ���� ����
		bg.mOffset.x -= mScrollSpeed * deltaTime;
		//�� �ؽ�ó�� ȭ���� ������ ����� ������ ����
		// ������ ��� �ؽ�ó�� ������ ��ġ�� �ʱ�ȭ�Ѵ�.
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}