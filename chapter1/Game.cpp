#include "Game.h"

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter 1)",//������ ����
		100,//�������� ���� ��� x��ǥ
		100,//�������� ���� ��� y��ǥ
		1024,//������ �ʺ�
		768,//������ ����
		0	// �÷���(0�� ��� �÷��׵� �������� ������ �ǹ�)
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
	//ť�� ������ �̺�Ʈ�� ���� �ִ� ����
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		//���⼭ ���� ������ �̺�Ʈ�� �ٷ��
		//�̺�Ʈ�� SDL_QUIT�̸� ���� ����
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
	// Ű������ ���� ���
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// �̽������� Ű�� �����ٸ� ���� ����
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}
