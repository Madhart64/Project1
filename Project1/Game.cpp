#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Enemy.h"
#include <vector>
int main()
{
	const int windowWidth{ 1384 };
	const int windowHeight{ 1384 };
	InitWindow(windowWidth, windowHeight, "Top Down");
	Texture2D map = LoadTexture("nature_tileset/map.png");
	Vector2 mapPos{ 0.0, 0.0 };
	Texture2D masword = LoadTexture("characters/sword.png");
	Character knight{};


	knight.setScreenPos(windowWidth, windowHeight);
	int direction = 0.0;
	 float spawntimer {};
	 float spawninterval{ 10 };
	 std::vector<Vector2> enemiesPos;
	 std::vector<Enemy> enemies;
	 std::vector<int> hitlist;
	 knight.swing = false;
	//if the knight is facing right it'll 1, if the knight facing left then -1
	

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		float deltatime = GetFrameTime();
		mapPos = Vector2Scale(knight.getWorldPos(), -1);
		if (knight.getWorldPos().x < 0.f ||
			knight.getWorldPos().y < 0.f ||
			knight.getWorldPos().x + windowWidth > map.width * 4 ||
			knight.getWorldPos().y + windowHeight > map.height * 4
			)
		{
			knight.undoMovement();
		}
		
		
		
		
		DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
		


		spawntimer += deltatime;
		if (spawntimer >= spawninterval && enemiesPos.size()<10)
		{
			float startx = GetRandomValue(1, 1384);
			float starty = GetRandomValue(1, 1384);
			Vector2 spawnPos = { startx, starty };
			enemiesPos.push_back(/*startx, starty*/ spawnPos);
			enemies.emplace_back(spawnPos);
			spawntimer = 0;
			
		}

		for (int I = 0;I < enemiesPos.size();I++)
		{

			enemies[I].setSpawnPos(enemiesPos[I]);
			//enemies[I].setSpawnPos(enemiesPos[I]);
			//sett enemy position to enemies[i]
			//enemies[i].setWorldPos(enemiesPos[i]
		}
		int index = 0;

		for (auto& Enemy : enemies)
		{
			index++;
			if (CheckCollisionRecs(knight.s_source, Enemy.source))
			{
				Enemy.damage();
					if (Enemy.health <= 0)
					{
						hitlist.push_back(index);
					}
			}
		}

		for (auto& hit : hitlist)
		{
			enemies.erase(enemies.begin() + hit);
		}

		for (auto& Enemy : enemies)
		{
			Enemy.tick(deltatime, knight.getWorldPos(), knight.getScreenPos());
		}

		if (IsKeyDown(KEY_E) && knight.swing == false)
		{
			knight.swing = true;
			
		}
		if (knight.swing == true)
		{
			knight.UpdateSwordAnim();
		}

		knight.tick(deltatime);
		
	
		
		EndDrawing();
	}
		CloseWindow();
	
	return 0;

}


