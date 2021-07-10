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
	//���ӿ� �ִ� ��� actors
	std::vector<Actor*> mActors;
	// ��� pending actors
	std::vector<Actor*> mPendingActors;
	// ���� actors�� ������Ʈ������ ��Ÿ����.
	bool mUpdatingActors;
	Uint32 mTicksCount;
	// ��� sprites components
	std::vector<SpriteComponent*> mSprites;
	
	// Map�� texture ����
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	class Ship* mShip;
};

