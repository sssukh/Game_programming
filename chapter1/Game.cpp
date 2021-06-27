#include "Game.h"

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter 1)",//윈도우 제목
		100,//윈도우의 좌측 상단 x좌표
		100,//윈도우의 좌측 상단 y좌표
		1024,//윈도우 너비
		768,//윈도우 높이
		0	// 플래그(0은 어떠한 플래그도 설정되지 않음을 의미)
	);
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
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

void Game::ProcessInput()
{
	SDL_Event event;
	//큐에 여전히 이벤트가 남아 있는 동안
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		//여기서 여러 유형의 이벤트를 다룬다
		//이벤트가 SDL_QUIT이면 루프 종료
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	// 키보드의 상태 얻기
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// 이스케이프 키를 눌렀다면 루프 종료
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}
