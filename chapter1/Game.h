#pragma once
#include "SDL/SDL.h"
class Game {
public:
	Game();
	//���� �ʱ�ȭ
	bool Initialize();
	//������ ������ �������� ���� ������ ����
	void RunLoop();
	//���� ����
	void Shutdown();
private:
	//���� ������ ���� ���� �Լ�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	//SDL�� ������ ������
	SDL_Window* mWindow;
	//������ ��� ����ž� �ϴ����� �Ǵ�
	bool mIsRunning;
};