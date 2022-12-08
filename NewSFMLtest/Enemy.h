#pragma once
#include "Entity.h"
class Enemy :public Entity {
public:
	float CurrentFrame = 0;
	enum { left, right, up, down } estate;
	int jumpX = 0;
	int jumpY = 0;
	float solidx;
	float solidy;
	Clock clockIntel;
	float itime = 0;
	bool clockIrestart = 0;
	bool intersect = 0;
	int viewradius = 300;
	Enemy(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H);
	void AnimationEnemy(float time, int Frames, int x, int y, double speed);
	
	void checkCollisionWithMap(float Dx, float Dy);
	

	void Intelligence(float* px, float* py, int ph, int pw, int* phealth, float* pspeed, int mapWidth, int mapHeight, float time);

	void update(float time);
};




