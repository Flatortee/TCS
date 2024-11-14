#include "player.h"

sfTexture* playerTexture;
sfSprite* playerSprite;
sfIntRect playerRect = { 0,0,17,23 };
sfVector2f playerVelocity = { 100.0f, 100.0f };

typedef enum PlayerState
{
	BAS,
	DROITE,
	GAUCHE,
	HAUT,
	IDLE
}PlayerState;

float animTime;
float idleTime;
sfVector2i frame;
sfBool hasMoved;

void initPlayer()
{
	playerTexture = sfTexture_createFromFile(TEXTURE_PATH"link.png", NULL);
	playerSprite = sfSprite_create();
	sfSprite_setTexture(playerSprite, playerTexture, sfTrue);
	playerPosition.x = 100.0f;
	playerPosition.y = 100.0f;
}

void updatePlayer(sfRenderWindow* _window)
{
	hasMoved = sfFalse;
	if (sfKeyboard_isKeyPressed(sfKeyZ))
	{
		if (playerPosition.y > 0)
			playerPosition.y -= playerVelocity.y * GetDeltaTime();
		frame.y = HAUT;
		animTime += GetDeltaTime();
		hasMoved = sfTrue;
	}
	if (sfKeyboard_isKeyPressed(sfKeyS))
	{
		if (playerPosition.y + 23 < sfRenderWindow_getSize(_window).y)
			playerPosition.y += playerVelocity.y * GetDeltaTime();
		frame.y = BAS;
		animTime += GetDeltaTime();
		hasMoved = sfTrue;
	}
	if (sfKeyboard_isKeyPressed(sfKeyQ))
	{
		if (playerPosition.x > 0)
			playerPosition.x -= playerVelocity.x * GetDeltaTime();
		frame.y = GAUCHE;
		animTime += GetDeltaTime();
		hasMoved = sfTrue;
	}
	if (sfKeyboard_isKeyPressed(sfKeyD))
	{
		if (playerPosition.x + 17 < sfRenderWindow_getSize(_window).x)
			playerPosition.x += playerVelocity.x * GetDeltaTime();
		frame.y = DROITE;
		animTime += GetDeltaTime();
		hasMoved = sfTrue;
	}
	sfSprite_setPosition(playerSprite, playerPosition);

	if (hasMoved)
	{
		if (animTime > 0.2f)
		{
			if (frame.x < 7)
				frame.x++;
			else frame.x = 0;
			animTime = 0.0f;
		}
	}
	else
	{
		animTime += GetDeltaTime();
		idleTime += GetDeltaTime();
		if (idleTime < 5.0f)
			frame.x = 0;
		else
		{
			if (animTime > 0.4f)
			{
				frame.y = IDLE;
				if (frame.x < 3)
					frame.x++;
				else
				{
					frame.x = 0;
					idleTime = 0.0f;
					frame.y = BAS;
				}
				animTime = 0.0f;
			}
		}
	}
}

void displayPlayer(sfRenderWindow* _window)
{
	playerRect.left = frame.x * playerRect.width;
	playerRect.top = frame.y * playerRect.height;

	sfSprite_setTextureRect(playerSprite, playerRect);
	sfRenderWindow_drawSprite(_window, playerSprite, NULL);
}
