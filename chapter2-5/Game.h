#pragma once

#include "SDL/SDL.h"
#include<unordered_set>
#include<vector>
#include<string>



class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor*);
	void RemoveActor(class Actor*);
	void AddSprite(class SpriteComponent*);
	void RemoveSprite(class SpriteComponent*);

	SDL_Texture* GetTexture(const std::string& fileName);


private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	bool mUpdatingActors;
	Uint32 mTicksCount;

	std::vector<SpriteComponent*> mSprites;
};

