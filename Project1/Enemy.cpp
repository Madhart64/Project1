#include "Enemy.h"


void Enemy::tick(float deltaTime, Vector2 worldPos, Vector2 screenPos)
{
	
	
		Vector2 toTarget = Vector2Subtract(screenPos, screenPosE);
		toTarget = Vector2Normalize(toTarget);
		toTarget = Vector2Scale(toTarget, speed);
		worldPosE = Vector2Add(worldPosE, toTarget);
		screenPosE = Vector2Subtract(worldPosE, worldPos);
		texture = g_run;

		runningTime += GetFrameTime();
		if (runningTime >= updateTime)
		{
			Eframe++;
			runningTime = 0.f;
			if (Eframe > max_frames) Eframe = 0;
		}
		if (screenPosE.x > screenPos.x) //changes faced direction 
		{
			rightLeft = 1.f;
		}
		else 
		{
			rightLeft = -1.f;
		}
		
		Rectangle source{ Eframe * (float)texture.width / 6.0f, 0.0, -rightLeft* (float)texture.width / 6.0f, (float)texture.height };
		Rectangle dest{ screenPosE.x, screenPosE.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height };

		DrawTexturePro(texture, source, dest, Vector2{}, 0.0, WHITE);
	
}


void Enemy::getTarget(float playerx, float playery, float deltaTime)
{
	float distancex = playerx - worldPosE.x;
	float distancey = playery - worldPosE.y;

	float magnitude = sqrt((distancex * distancex) + (distancey * distancey));
	if (magnitude != 0)
	{
		worldPosE.x += speed * deltaTime * (distancex / magnitude);
		worldPosE.y += speed * deltaTime * (distancey / magnitude);

	}
	
	
	rightLeft = distancex < 0.f ? -1.f : 1.f;
	
	
}




