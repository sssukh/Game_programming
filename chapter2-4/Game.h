#pragma once

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include<unordered_set>

struct Vector2
{
	float x;
	float y;
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
	void AddSprite(class SpriteComponent*);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	bool mUpdatingActors;
	Uint32 mTicksCount;

	std::vector<SpriteComponent*> mSprites;
};

