#include "Game.h"
#include "SDL/SDL_image.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "BGSpriteComponent.h"
#include "Character.h"
#include <algorithm>

Game::Game()
	:mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mUpdatingActors(false)
{
	
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
	//pending actors에 있는가?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		//벡터의 끝부분과 자리를 바꾸고 삭제 (erase 복사를 피한다.)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// actors에 있는가?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// 벡터의 끝부분과 자리를 바꾸고 삭제 (erase 복사를 피한다.)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::UpdateGame()
{

	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

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

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

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
	LoadData();
	mTicksCount = SDL_GetTicks();


	return true;
}

void Game::Shutdown()
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

void Game::RemoveSprite(SpriteComponent* sprite)
{
	// (스왑은 순서를 망치기 때문에 사용하지 않는다.)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mShip->ProcessKeyboard(state);
	mCharacter->ProcessKeyboard(state);
}

void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	// 모든 sprite component를 그린다.
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);

}

void Game::LoadData()
{
	// 플레이어의 ship을 만든다.
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(100.0f, 384.0f));
	mShip->SetScale(1.5f);

	//연습2.2
	mCharacter = new Character(this);
	mCharacter->SetPosition(Vector2(200.0f, 100.0f));
	mCharacter->SetScale(1.5f);


	// 배경 액터를 생성(이 경우 서브클래스가 필요없다)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	// 뒤에 있는 배경을 만든다.
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*>bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// 가까운 배경화면 만든다.
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}

void Game::UnloadData()
{
	//actors 삭제
	// 액터 소멸자가 RemoveActor를 호출하기 때문에 다른 스타일의 루프 생성
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// texture 삭제
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// map에 texture가 이미 존재하는가?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// file에서 load
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}
		
		// surface에서 texture를 생성한다.
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}
