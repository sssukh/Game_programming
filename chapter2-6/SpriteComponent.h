#pragma once
#include "Component.h"
#include "SDL/SDL.h"

class SpriteComponent : public Component
{
public:
	// (�׸��� �������� �������� �� ���ʿ��� �׸���.)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();
	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* textrue);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth()	const { return mTexWidth; }

protected:
	// �׸� �ؽ�ó
	SDL_Texture* mTexture;
	// ȭ�� �˰��򿡼� ����ϴ� �׸��� ����
	int mDrawOrder;
	// �ؽ�ó�� �ʺ�/����
	int mTexWidth;
	int mTexHeight;
};