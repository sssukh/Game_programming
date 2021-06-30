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
	// component 추가
	void AddComponent(Component* comp);
	// component 삭제
	void RemoveComponent(Component* comp);
private:
	// component 관리하는 set
	std::unordered_set<Component*> mComponents;
};

class Actor
{
public:
	// 액터의 상태를 추적하는데 사용된다.
	enum State
	{
		EActive,
		EPasued,
		EDead
	};
	// 생성자, 소멸자
	Actor(class Game* game);
	virtual ~Actor();
	// Game에서 호출하는 Update 함수( 가상함수 아님)
	void Update(float deltaTime);
	//액터에 부착된 모든 컴포넌트를 업데이트 ( 가상함수 아님)
	void UpdateComponents(float deltaTime);
	// 특정 액터에 특화된 업데이트 코드 (오버라이딩 가능)
	virtual void UpdateActor(float deltaTime);

	//Getters/Setters
	State GetState()
	{
		return mState;
	}

	// 컴포넌트 추가/제거
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	//액터의 상태
	State mState;
	//변환
	Vector2 mPosition;	//액터의 중심점
	float mScale;		//액터의 배율(100%의 경우 1.0f)
	float mRotation;	//회전 각도 (라디안)
	//이 액터가 보유한 컴포넌트들
	std::vector<class Component*> mComponents;
	class Game* mGame;
};

class Component
{
public:
	//생성자
	//(업데이트 순서값이 작을수록 컴포넌트는 더 빨리 갱신된다.)
	Component(class Actor* owner, int updateOrder = 100);
	//소멸자
	virtual ~Component();
	//델타 시간으로 이 컴포넌트를 업데이트
	virtual void Update(float deltaTime);
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	//소유자 액터
	class Actor* mOwner;
	//컴포넌트의 업데이트 순서
	int mUpdateOrder;
};