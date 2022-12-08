#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Level.h"
using namespace sf;
class Entity {
public:
	std::vector<Object> obj;
	float dx, dy, x, y, speed, moveTimer;
	float w, h;
	int health;
	bool life, isMove;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image& image, String Name, float X, float Y, int W, int H);
	FloatRect getRect();
	virtual void update(float time) = 0;
};