#pragma once
#include <iostream>
#include "Character.h"
#include "raylib.h"
#include "raymath.h"
#include <vector>

class Enemy :
    public Character
{
private:
        Texture2D s_idle = LoadTexture("Characters/slime_idle_spritesheet.png");
        Texture2D g_idle = LoadTexture("Characters/goblin_idle_spritesheet.png");
        Texture2D s_run = LoadTexture("Characters/slime_run_spritesheet.png");
        Texture2D g_run = LoadTexture("Characters/goblin_run_spritesheet.png");
        Texture2D texture = LoadTexture("Characters/goblin_run_spritesheet.png");
        Vector2 spawnPosE{};
        Vector2 worldPosE{spawnPosE};
        Vector2 screenPosE{};
      
        int Eframe{};
        const int max_frames{ 6 };
        float speed{ 4 };
        float updateTime{ 1.f / 12.f };
        int direction{};
        float runningTime{};
        float spawntimer{};
        float spawninterval{ 30 };

public:
    int health{ 1 };
    //void spawn_enemy(float deltaTime);
    Vector2 getWorldPos() { return worldPosE; }
    void tick(float deltaTime, Vector2 worldPos, Vector2 screenPos);
    void getTarget(float playerx, float playery, float deltaTime);
    void setSpawnPos(Vector2 spawnPos) { Vector2 spawnPosE = spawnPos; }
    float rightLeft{1.0f};
    Rectangle source{};
    
    int damage() { health -= 1.0f; }

    Enemy(Vector2 spawnPos)
    {
        spawnPosE = spawnPos;
    }

    ~Enemy()
    {

    }

};

