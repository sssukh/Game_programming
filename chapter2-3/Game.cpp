#include "Game.h"

Game::Game()
{
	mTicksCount = 0;
}

void Game::AddActor(Actor* actor)
{
	//���͸� ���� ���̶�� ��� ���Ϳ� ���͸� �߰�
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)// actor ����
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

	// ��� ���͸� ����
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//��� ���� ���͸� mActors�� �̵�
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// ���� ���͸� �ӽ� ���Ϳ� �߰�
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}


	// ���� ���� ����(mActors���� �߷��� ���͵�)
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

	// ���Ϸκ��� �̹��� �ε�
	// �����ϸ� SDL_Surface �����͸� �����ϰ� �����ϸ� nullptr ��ȯ
	/*
	SDL_Surface* IMG_Load(
		const char* file
	);


	//SDL_Surface�� SDL_Texture�� ��ȯ
	// �����ϸ� SDL_Texture �����͸� �����ϰ�����ϸ� nullptr ��ȯ
	SDL_Texture* SDL_CreateTextureFromSurface(
		SDL_Renderer * renderer, // ����� ������
		SDL_Surface * surface // ��ȯ�� SDL_Surface
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
	//���ĵ� ���Ϳ��� �����ؾ� �� ��ġ�� ã�´�.
	//(�ڽź��� �׸��� �������� ū ���� ���)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	//�ݺ��� ��ġ �տ� ��Ҹ� �����Ѵ�.
	mSprites.insert(iter, sprite);
}