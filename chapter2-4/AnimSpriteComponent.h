#pragma once
#include "SpriteComponent.h"

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	// �ִϸ��̼��� �����Ӹ��� ���� (Component�� Update �޼ҵ带 �������̵�)
	void Update(float deltaTime) override;
	//�ִϸ��̼ǿ� ���Ǵ� �ؽ�ó ����
	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	// �ִϸ��̼� FPS�� ��ų� �����ϴ� �Լ�
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

	//SetTexture �� �������Ͽ� ���(SpriteComponent���� ��ӹ���)
private:
	//�ִϸ��̼ǿ� ���Ǵ� ��� �ؽ�ó
	std::vector<SDL_Texture*> mAnimTextures;
	//���� ������
	float mCurrFrame;
	// �ִϸ��̼� ������ ����Ʈ
	float mAnimFPS;
};