#define _CRT_SECURE_NO_WARNINGS
#include "tools.h"



sfTime sftime;
sfClock* sfclock;

void initTools()
{
	sfclock = sfClock_create();
	srand(time(NULL));
}

void restartClock()
{
	sftime = sfClock_restart(sfclock);
}

float GetDeltaTime()
{
	return sfTime_asSeconds(sftime);
}

sfVector2f vector2f(float _x, float _y)
{
	sfVector2f tmp = { _x, _y };
	return tmp;
}

sfVector2i vector2i(int _x, int _y)
{
	sfVector2i tmp = { _x, _y };
	return tmp;
}

sfVector3f vector3f(float _x, float _y, float _z)
{
	sfVector3f tmp = { _x, _y, _z };
	return tmp;
}

sfFloatRect FlRect(float _left, float _top, float _width, float _height)
{
	sfFloatRect rectTmp = { _left, _top,  _width, _height };
	return rectTmp;
}

sfIntRect IntRect(int _left, int _top, int _width, int _height)
{
	sfIntRect rectTmp = { _left, _top,  _width, _height };
	return rectTmp;
}



sfSprite* CreateSprite(char* _path)
{
	sfTexture* tmp = sfTexture_createFromFile(_path, NULL);
	sfSprite* spTmp = sfSprite_create();
	sfSprite_setTexture(spTmp, tmp, sfTrue);
	return spTmp;
}

sfText* CreateText(char* _path)
{
	sfFont* tmp = sfFont_createFromFile(_path);
	sfText* txtTmp = sfText_create();
	sfText_setFont(txtTmp, tmp);
	return txtTmp;
}

sfBool Circle_Collision(sfVector2f _pos1, sfVector2f _pos2, float _rayon1, float _rayon2)
{
	if (sqrt(pow(_pos1.x - _pos2.x, 2) + pow(_pos1.y - _pos2.y, 2)) < _rayon1 + _rayon2)
	{
		return sfTrue;
	}
	else return sfFalse;
}

int iRand(int _min, int _max)
{
	if (_max > _min)
		return rand() % (_max - _min + 1) + _min;
	else
		return _min;
}


void screenshot(sfRenderWindow* _window)
{
	char hours[9] = { 0 }, date[9] = { 0 }, tmph[7] = { 0 }, tmpd[7] = { 0 };
	_strtime(hours);
	_strdate(date);
	sfVector2u windowSize;


	windowSize = sfRenderWindow_getSize(_window);
	sfTexture* texture = sfTexture_create(windowSize.x, windowSize.y);
	sfTexture_updateFromRenderWindow(texture, _window, 0, 0);
	sfImage* screenshot = sfTexture_copyToImage(texture);
	char filename[100];
	int j = 0;
	for (int i = 0; i < 9; i++) if (hours[i] != ':') tmph[j++] = hours[i];
	j = 0;
	for (int i = 0; i < 9; i++) if (date[i] != '/') tmpd[j++] = date[i];

	sprintf(filename, "../Ressources/Screenshots/Screenshot-%s-%s.jpg", tmpd, tmph);
	sfImage_saveToFile(screenshot, filename);
}