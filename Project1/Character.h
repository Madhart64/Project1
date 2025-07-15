#pragma once
#include "raylib.h"
#include "raymath.h"
class Character
{
	
private:
	Texture2D idle = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D run = LoadTexture("characters/knight_run_spritesheet.png");
	Texture2D texture = LoadTexture("characters/knight_idle_spritesheet.png");
	Texture2D sword = LoadTexture("characters/sword5.png");
	Vector2 screenPos{};
	Vector2 worldPos{};
	float speed{ 6.0 };
	
	float runningTime{};
	float s_runningTime{};
	int frame{};
	const int maxFrames{ 6 };
	const int s_maxFrames{ 10 };
	const float updateTime{ 1.f / 12.f };
	int s_frame{};
	




public:
	Vector2 getWorldPos() { return worldPos; }
	Vector2 getScreenPos() { return screenPos; }
	void setScreenPos(int winWidth, int winHeight);
	void getMovementInput(Vector2& direction);
	void drawCharacter(Texture2D& texture);
	void undoMovement();
	Vector2 WorldPosLastFrame{};
	void tick(float deltaTime);
	void UpdateSwordAnim();
	void animation(int& frame, int maxFrames, float& runningTime, float updateTime, bool isSword);
	float rotate{};
	Vector2 swordPiv{};
	float rotate2{};
	int test{};
	bool swing{};
	bool getSwing() { return swing; };
    void  setSwing() { swing = true; };
	Rectangle s_source{};
	float rightLeft{ 1.0f };
	Texture2D getTexture() { return texture; }
	Character()
	{



	}
	~Character()
	{


	}
};

