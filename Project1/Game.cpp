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
	Texture2D map = LoadTexture("characters/map3.png");
	Vector2 mapPos{ 0.0, 0.0 };
	Texture2D masword = LoadTexture("characters/sword.png");
	Character knight{};
	
	Texture2D heart = LoadTexture("characters/heart.png");


	knight.setScreenPos(windowWidth, windowHeight);
	int direction = 0.0;
	 float spawntimer {};
	 float spawninterval{ 2 };
	 std::vector<Vector2> enemiesPos;
	 std::vector<Enemy> enemies;
	 std::vector<int> hitlist;
	 knight.swing = false;
	 float Espeed{};
	 float Epower{};
	 float Ehealth{};
	 float cooldown{};
	 float waveCount{ 6 };
	 float spawned{};
	 bool begin = false;
	 int alive = 0;
	 bool game_over = false;
	 Vector2 heartPos{ windowWidth / 2, windowHeight };
	 int randomE{};
	 void ERandom_Powerup();

	//if the knight is facing right it'll 1, if the knight facing left then -1
	

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		float deltatime = GetFrameTime();
		DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
		if (game_over == false)
		{
			mapPos = Vector2Scale(knight.getWorldPos(), -1);
			if (knight.getWorldPos().x < 0.f ||
				knight.getWorldPos().y < 0.f ||
				knight.getWorldPos().x + windowWidth > map.width * 4 ||
				knight.getWorldPos().y + windowHeight > map.height * 4
				)
			{
				knight.undoMovement();
			}





			float multi = 1;
			Rectangle h2source{ (float)heart.width / 2.0F, 0.0f, (float)heart.width / 2, (float)heart.height * (knight.health / knight.max_health) };
			Rectangle h2dest{ 692 - multi * (float)heart.width / 4, 1384 - multi * (float)heart.height, (float)heart.width / 2, (float)heart.height };
			//DrawTexturePro(heart, h2source, h2dest, Vector2{}, 0.0, WHITE);

			Rectangle hsource{ 0.0f, 0.0f, (float)heart.width / 2, (float)heart.height };
			Rectangle hdest{ 692 - (float)heart.width / 4, 1384 - (float)heart.height, (float)heart.width / 2, (float)heart.height };
			DrawTexturePro(heart, hsource, hdest, Vector2{}, 0.0, WHITE);
			DrawTextureRec(heart, h2source, Vector2{ 692 - multi * (float)heart.width / 4, 1384 - multi * (float)heart.height }, WHITE);



			if (spawned <= waveCount)
			{
				spawntimer += deltatime;
			}
			if (spawntimer >= spawninterval && spawned < waveCount)
			{
				spawninterval = 2;
				float startx = GetRandomValue(1, map.width * 4);
				float starty = GetRandomValue(1, map.height * 4);
				Vector2 spawnPos = { startx, starty };
				enemiesPos.push_back(/*startx, starty*/ spawnPos);
				enemies.emplace_back(spawnPos, Espeed, Epower, Ehealth, knight.knockback);
				
				spawntimer = 0;
				spawned += 1;
				alive += 1;
				begin = true;
			}

			if (begin && alive == 0) //wave complete
			{
				spawninterval = 9;
				begin = false;
				spawned = 0;
				
				
				knight.random_powerup();
				
				if (knight.max_health - knight.health <= knight.max_health * knight.heal) {
					knight.health = knight.max_health;
				}
				else {
					knight.health += knight.max_health * knight.heal;
				}
				
				randomE = GetRandomValue(1, 4);
				if (randomE == 1)
				{
					waveCount += 1;
				}
				if (randomE == 2)
				{
					Espeed += 1;
				}
				if (randomE == 3)
				{
					Epower += 1;
				}
				if (randomE == 4)
				{
					Ehealth += 1;
				}
			
				 
			}

			for (int I = 0;I < enemiesPos.size();I++)
			{
				if (enemies.size() > 0) {
					enemies[I].setSpawnPos(enemiesPos[I]);
				}
				
				//enemies[I].setSpawnPos(enemiesPos[I]);
				//sett enemy position to enemies[i]
				//enemies[i].setWorldPos(enemiesPos[i]
			}
			int index = 0;

			//for (auto& Enemy : enemies)


			/*for (auto& hit : hitlist)
			{
				enemies.erase(enemies.begin() + hit);
			}*/
			if (enemies.size() > 0) {
				for (auto& Enemy : enemies)
				{
					Enemy.tick(deltatime, knight.getWorldPos(), knight.getScreenPos());

					if (CheckCollisionRecs(knight.dest, Enemy.dest) && Enemy.isDead == false)
					{
						knight.damage(Enemy.power);
					}
				}
			}

			if (IsKeyDown(KEY_E) && knight.swing == false && cooldown <= 0)
			{
				knight.swing = true;

			}
			if (knight.swing == true)
			{
				cooldown = knight.cooldown_Time;
				knight.UpdateSwordAnim();
				if (enemies.size() > 0) {
					for (auto& Enemy : enemies)
					{
						index++;
						if (CheckCollisionRecs(knight.sl_dest, Enemy.dest))
						{
							if (Enemy.hitstun <= 1)
							{
								Enemy.damage(knight.power);
							}
							if (Enemy.health <= 0)
							{
								//hitlist.push_back(index);
								if (Enemy.isDead == false) { alive -= 1; }

								Enemy.isDead = true;

							}
							else
							{
								Enemy.knockback(knight.getScreenPos());
							}
						}

					}
				}
			}
			else { cooldown -= 1; }

			knight.tick(deltatime);
			
		}
		if (knight.health <= 0) {
			DrawText("Game over", windowWidth / 4, windowHeight / 3, 144, RED);
			game_over = true;
		}
		
		DrawText(TextFormat("Power: %02f", knight.power), 10, 20, 20, RED);
		DrawText(TextFormat("Speed: %2f", knight.speed), 10, 40, 20, RED);
		DrawText(TextFormat("Attack Speed: %2f", knight.cooldown_Time), 10, 60, 20, RED);
		DrawText(TextFormat("Max Health: %2f", knight.max_health), 10, 80, 20, RED);
		DrawText(TextFormat("Knockback: %2f", knight.knockback), 10, 100, 20, RED);
		DrawText(TextFormat("Regen: %2f", knight.heal), 10, 120, 20, RED);

		

		EndDrawing();
	}
		CloseWindow();
		UnloadTexture(knight.getTexture());
		UnloadTexture(map);
		UnloadTexture(knight.getSword());
		UnloadTexture(knight.getIdle());
		UnloadTexture(knight.getRun());
		UnloadTexture(knight.getSlash());
		UnloadTexture(knight.getHold());
		UnloadTexture(masword);
		UnloadTexture(heart);
	return 0;
	
}

