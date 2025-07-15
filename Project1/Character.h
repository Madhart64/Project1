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
	Texture2D hold = LoadTexture("characters/sword5.png");
	Texture2D slash = LoadTexture("characters/Slash.png");
	
	Vector2 screenPos{};
	Vector2 worldPos{};
	float base_speed{ 6.0 };
	
	
	float runningTime{};
	float s_runningTime{};
	float sl_runningTime{};
	int frame{};
	int maxFrames{ 6 };
	int s_maxFrames{ 10 };
	int sl_maxFrames{ 12 };
	float updateTime{ 1.f / 12.f };
	int s_frame{};
	




public:
	float health{ 100 };
	float max_health{ 100 };
	Vector2 getWorldPos() { return worldPos; }
	Vector2 getScreenPos() { return screenPos; }
	void setScreenPos(int winWidth, int winHeight);
	void getMovementInput(Vector2& direction);
	void drawCharacter(Texture2D& texture);
	void undoMovement();
	Vector2 WorldPosLastFrame{};
	void tick(float deltaTime);
	void UpdateSwordAnim();
	void animation(int& frame, int maxFrames, float& runningTime, float updateTime, bool isSword, float animsp);
	float rotate{};
	Vector2 swordPiv{};
	float rotate2{};
	int test{};
	float knightanimmod{};
	bool swing{};
	bool isDead{};
	bool getSwing() { return swing; };
    void  setSwing() { swing = true; };
	Rectangle s_source{};
	Rectangle s_dest{};
	Rectangle dest{};
	Rectangle sl_dest{};
	float rightLeft{ 1.0f };
	Texture2D getTexture() { return texture; }
	Texture2D getIdle() { return idle; }
	Texture2D getRun() { return run; }
	Texture2D getHold() { return hold; }
	Texture2D getSlash() { return slash; }
	Texture2D getSword() { return sword; }
	int rotate3{};
	float power{1.0f};
	int damage(float damage) { return health -= damage; }
	void random_powerup();
	float random{};
	int cooldown_Time = 12;
	float heal{};
	float knockback{};
	float speed{ 6.0 };
	Character()
	{



	}
	~Character()
	{


	}
};

