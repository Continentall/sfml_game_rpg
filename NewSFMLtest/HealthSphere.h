#pragma once
#include "Entity.h"

class HealthSphere :public Entity {
	float CurrentFrame = 0;
public:
	HealthSphere(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H);
	void update(float time);
};