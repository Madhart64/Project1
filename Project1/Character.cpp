#include "Character.h"


void Character::setScreenPos(int winWidth, int winHeight)
{
	screenPos =
	{
		(float)winWidth / 2.0f - 4.0f * (0.5f * (float)texture.width / 6.0f),
		(float)winHeight / 2.0f - 4.0f * (0.5f * (float)texture.height)
	};
	
}

void Character::getMovementInput(Vector2& direction)
{
	if (IsKeyDown(KEY_A)) direction.x += 1;
	if (IsKeyDown(KEY_D)) direction.x -= 1;
	if (IsKeyDown(KEY_W)) direction.y += 1;
	if (IsKeyDown(KEY_S)) direction.y -= 1;
	
}

void Character::tick(float deltaTime)
{
	
	Vector2 direction{};
	WorldPosLastFrame = worldPos;
	getMovementInput(direction);

	if (Vector2Length(direction) != 0.0)
	{
		//set mapPos = mapPos - direction
		worldPos = Vector2Subtract(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
		texture = run;

	}
	else
	{
		texture = idle;
	}
	if ((direction.x) != 0.0)
	{
		rightLeft = direction.x < 0.f ? -1.f : 1.f;
	}
	if (rightLeft == 1) {
		rotate = 20;
		rotate3 = 38;
		test = 0;
	}
	else
	{
		rotate = 55;
		rotate3 = 55;
		test = 1;
	}

	swordPiv = {  (sword.width / 12) / 5 + rightLeft, (float)sword.height / 5};


	// update animation frames
	
	knightanimmod = 1 + (speed - base_speed) / 5;
	

	animation(frame, maxFrames, runningTime, updateTime, false, knightanimmod);


	Rectangle source{ frame * (float)texture.width / 6.0f, 0.0, -rightLeft* (float)texture.width / 6.0f ,(float)texture.height };
	dest = { screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height };
	DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);

	
	
		s_source = { (float)sword.width / 10.0f, 0.0, -rightLeft * (float)sword.width / 10.0f, (float)sword.height };
		s_dest = { screenPos.x - rightLeft * rotate, screenPos.y + 10.0f, 0.8f * (float)sword.width / 10.0f, 0.8f * (float)sword.height };
		if (swing == false) {
			DrawTexturePro(sword, s_source, s_dest, swordPiv, 0.0f, WHITE);
		}
	
	
		Rectangle sl_source = { s_frame * (float)sword.width / 12.0f, 0.0, -rightLeft * (float)sword.width / 12.0f, (float)sword.height };
		sl_dest = { screenPos.x - rightLeft * rotate3, screenPos.y + 12.0f, 0.8f * (float)sword.width / 12.0f, 0.8f * (float)sword.height };
		DrawTexturePro(slash, sl_source, sl_dest, swordPiv, 0.0f, WHITE);
	
	

}

void Character::UpdateSwordAnim()
{
	sword = slash;
	animation(s_frame, sl_maxFrames, sl_runningTime, updateTime, true, 5);
	
}

void Character::animation(int& frame, int maxFrames, float& runningTime, float updateTime, bool isSword, float animsp )
{
	
	runningTime += GetFrameTime() * animsp;
	if (runningTime >= updateTime)
	{

		frame++;
		runningTime = 0.f;
		if (frame > maxFrames) 
		{
			frame = 0;
			if (isSword == true)
			{
				sword = hold;
				swing = false;
			}
		}
	}
}



//void Character::drawCharacter(Texture2D& texture)
//{
	//Rectangle source{ frame*(float)texture.width / 6.0f, (float)texture.height };
	//Rectangle dest{ screenPos.x, screenPos.y, 4.0f * (float)texture.width / 6.0f, 4.0f * (float)texture.height };

	

	//Rectangle s_source{ (float)sword.width / 10.0, (float)sword.height };
	//Rectangle s_dest{ screenPos.x + rightLeft * 200, screenPos.y, 4.0f * (float)sword.width / 10.0f, 4.0f * (float)sword.height };
	//DrawTexturePro(sword, s_source, s_dest, Vector2{},2.f, BLACK);
	//DrawTexturePro(texture, source, dest, Vector2{}, 0.0f, WHITE);

//}

void Character::undoMovement()
{
	worldPos = WorldPosLastFrame;
}
void Character::random_powerup()
{
	random = GetRandomValue(1, 6);
	if (random == 1)
	{
		speed += 1;
	}
	if (random == 2)
	{
		health += 10;
		max_health += 10;
	}
	if (random == 3)
	{
		power += 1;
	}
	if (random == 4)
	{
		if (cooldown_Time >= 1)
		{
			cooldown_Time -= 1;
		}
	}
	if (random == 5)
	{
		if (heal < 1) 
		{
			heal += 0.05;
		}
		
	}
	if (random == 6)
	{
		knockback += 1;
	}
	

}