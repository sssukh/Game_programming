#pragma once

#include "SDL/SDL.h"
#include<unordered_set>

struct Vector2
{

};

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void ShutDown();

	void AddActor(class Actor*);
	void RemoveActor(class Actor*);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	bool mIsRunning;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	bool mUpdatingActors;
	Uint32 mTicksCount;
};

class GameObject
{
public:
	// component �߰�
	void AddComponent(Component* comp);
	// component ����
	void RemoveComponent(Component* comp);
private:
	// component �����ϴ� set
	std::unordered_set<Component*> mComponents;
};

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
	State GetState()
	{
		return mState;
	}

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

class Component
{
public:
	//������
	//(������Ʈ �������� �������� ������Ʈ�� �� ���� ���ŵȴ�.)
	Component(class Actor* owner, int updateOrder = 100);
	//�Ҹ���
	virtual ~Component();
	//��Ÿ �ð����� �� ������Ʈ�� ������Ʈ
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//������ ����
	class Actor* mOwner;
	//������Ʈ�� ������Ʈ ����
	int mUpdateOrder;
};