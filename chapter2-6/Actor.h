#pragma once

#include <vector>
#include "Math.h"
class Actor
{
public:
	// ������ ���¸� �����ϴµ� ���ȴ�.
	enum State
	{
		EActive,
		EPasued,
		EDead
	};
	// ������, �Ҹ���
	Actor(class Game* game);
	virtual ~Actor();

	// Game���� ȣ���ϴ� Update �Լ�( �����Լ� �ƴ�)
	void Update(float deltaTime);

	//���Ϳ� ������ ��� ������Ʈ�� ������Ʈ ( �����Լ� �ƴ�)
	void UpdateComponents(float deltaTime);

	// Ư�� ���Ϳ� Ưȭ�� ������Ʈ �ڵ� (�������̵� ����)
	virtual void UpdateActor(float deltaTime);

	//Getters/Setters
	State GetState() const { return mState; }
	void SetState(State state)  { mState = state; }
	float GetScale() { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotate(float rotation) { mRotation = rotation; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }

	class Game* GetGame() { return mGame; }


	// ������Ʈ �߰�/����
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	//������ ����
	State mState;

	//��ȯ
	Vector2 mPosition;	//������ �߽���
	float mScale;		//������ ����(100%�� ��� 1.0f)
	float mRotation;	//ȸ�� ���� (����)

	//�� ���Ͱ� ������ ������Ʈ��
	std::vector<class Component*> mComponents;
	class Game* mGame;
};
