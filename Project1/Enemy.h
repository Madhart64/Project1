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
        int max_frames{ 6 };
     
        float tspeed{ 4 };
   
        float updateTime{ 1.f / 12.f };
        int direction{};
        float runningTime{};
        float spawntimer{};
        float spawninterval{ 30 };

public:
    bool spawned{};
    int health{ 3 };
    //void spawn_enemy(float deltaTime);
    Vector2 getWorldPos() { return worldPosE; }
    void tick(float deltaTime, Vector2 worldPos, Vector2 screenPos);
    void getTarget(float playerx, float playery, float deltaTime);
    void setSpawnPos(Vector2 spawnPos) { Vector2 spawnPosE = spawnPos; }
    float rightLeft{1.0f};
    Rectangle source{};
    Rectangle dest{};
    bool isDead;
    void knockback(Vector2 screenPos);
    Color tint{};
    int hitstun{};
    float power{ 1 };
    int damage(float damage) { return health -= damage; }
    Texture2D gets_idle() { return s_idle; }
    Texture2D getg_idle() { return g_idle; }
    Texture2D getg_run() { return g_run; }
    Texture2D gets_run() { return s_run; }
    Texture2D gettexture() { return texture; }
    float kspeed{ -8 };
    float waveCount{};
    float speed{ 4 };
    float bspeed{ 4 };
    Enemy(Vector2 spawnPos, float inc_speed, float inc_power, float inc_health, float inc_kspeed)
    {
        isDead = false;
        spawnPosE = spawnPos;
        bspeed += inc_speed;
        power += inc_power;
        health += inc_health;

    }
    ~Enemy()
    {

    }

};

