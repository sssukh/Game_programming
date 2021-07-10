#pragma once

#include "SDL/SDL.h"
#include<unordered_map>
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
	//게임에 있는 모든 actors
	std::vector<Actor*> mActors;
	// 모든 pending actors
	std::vector<Actor*> mPendingActors;
	// 현재 actors를 업데이트중인지 나타낸다.
	bool mUpdatingActors;
	Uint32 mTicksCount;
	// 모든 sprites components
	std::vector<SpriteComponent*> mSprites;
	
	// Map에 texture 저장
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	class Ship* mShip;
};

