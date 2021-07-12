#include "AnimSpriteComponent.h"
#include "Math.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
	:SpriteComponent(owner, drawOrder)
	, mCurrFrame(0.0f)
	, mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		//������ ����Ʈ�� ��Ÿ �ð��� �������
		// ���� ������ ����
		mCurrFrame += mAnimFPS * deltaTime;

		//�ִϸ��̼� �ؽ�ó ���� �ʰ��ϸ� ���� �������� �����Ѵ�.
		if (mRoutine)
		{
			while (mCurrFrame >= mAnimTextures.size())
			{
				mCurrFrame -= mAnimTextures.size();
			}
		}
		else
		{
			if (mCurrFrame >= mAnimTextures.size())
			{
				mCurrFrame = mAnimTextures.size()-1;
			}
		}

		// ���� �ؽ�ó�� ����
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		// active �ؽ�ó�� ù��° ���������� ����
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}