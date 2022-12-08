#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>
using namespace sf;
extern int wx;
extern int wy;
class HealthBar
{
public:
	Image image;
	Texture t;
	Sprite s;
	int max;
	int min;
	RectangleShape bar;
	HealthBar();
	void update(int k);
	void draw(RenderWindow& window);
};
