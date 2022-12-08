#pragma once
#include "Entity.h"
class Bullet :public Entity 
{
public:
	int direction;
	Bullet(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H, int dir);
	void update(float time);
};