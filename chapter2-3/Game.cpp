#include "Game.h"

Game::Game()
{
	mTicksCount = 0;
}

void Game::AddActor(Actor* actor)
{
	//액터를 갱신 중이라면 대기 벡터에 액터를 추가
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)// actor 삭제
{
	for (int i=0;i<mActors.size();i++)
	{
		if (mActors[i] == actor)
		{
			mActors.erase(mActors.begin()+i);
			return;
		}
	}
	for (int i = 0; i < mPendingActors.size(); i++)
	{
		if (mPendingActors[i] == actor)
		{
			mPendingActors.erase(mPendingActors.begin() + i);
			break;
		}
	}
}

void Game::UpdateGame()
{

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	mTicksCount = SDL_GetTicks();
	
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// 모든 액터를 갱신
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//대기 중인 액터를 mActors로 이동
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 죽은 액터를 임시 벡터에 추가
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}


	// 죽은 액터 제거(mActors에서 추려낸 액터들)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL : %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow(
		"Game Programming in C++ (Chapter2)",
		100,
		100,
		1024,
		768,
		0
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	IMG_Init(IMG_INIT_PNG);

	// 파일로부터 이미지 로드
	// 성공하면 SDL_Surface 포인터를 리턴하고 실패하면 nullptr 반환
	/*
	SDL_Surface* IMG_Load(
		const char* file
	);


	//SDL_Surface를 SDL_Texture로 변환
	// 성공하면 SDL_Texture 포인터를 리턴하고실패하면 nullptr 반환
	SDL_Texture* SDL_CreateTextureFromSurface(
		SDL_Renderer * renderer, // 사용할 렌더러
		SDL_Surface * surface // 변환될 SDL_Surface
	);

	*/



	return true;
}

void Game::ShutDown()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	SDL_DestroyRenderer(mRenderer);
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	//정렬된 벡터에서 삽입해야 할 위치를 찾는다.
	//(자신보다 그리기 순서값이 큰 최초 요소)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	//반복자 위치 앞에 요소를 삽입한다.
	mSprites.insert(iter, sprite);
}