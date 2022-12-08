#include "Enemy.h"

Enemy::Enemy(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	obj = lvl.getAllObjects();
	if (name == "enemy1") {
		sprite.setTextureRect(IntRect(100, 100, w, h));
		speed = 0.1;
	}
	else if (name == "enemy2") {
		sprite.setTextureRect(IntRect(110, 110, w, h));
		speed = 0.15;
	}
	else if (name == "enemy3") {
		sprite.setTextureRect(IntRect(220, 220, w, h));
		speed = 0.15;
		health = 500;
	}
}
void Enemy::AnimationEnemy(float time, int Frames, int x, int y, double speed)
{
	if (name == "enemy1")
	{
		CurrentFrame += speed * time;
		if (CurrentFrame > Frames) CurrentFrame -= Frames;
		sprite.setTextureRect(IntRect(x * int(CurrentFrame), y, w, h));
	}
	else if (name == "enemy2")
	{
		if (intersect == 0) {
			if (dx < 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), y * 2, w, h));
			}
			else if (dx > 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), y, w, h));
			}
			else if (dy < 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), y * 3, w, h));
			}
			else if (dy > 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), 0 * y, w, h));
			}
		}
	}
	else if (name == "enemy3") {
		if (intersect == 0) {
			if (dx < 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), y * 2, w, h));
			}
			else if (dx > 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), y, w, h));
			}
			else if (dy < 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), y * 3, w, h));
			}
			else if (dy > 0) {
				CurrentFrame += speed * time;
				if (CurrentFrame > 4) CurrentFrame -= 4;
				sprite.setTextureRect(IntRect(x * int(CurrentFrame), 0 * y, w, h));
			}
		}
	}
}
void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = 0; i < obj.size(); i++)
	{
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].type == "solid")
			{
				if (Dy > 0) {
					y = obj[i].rect.top - h;
					dy = 0;
				}
				if (Dy < 0) {
					y = obj[i].rect.top + obj[i].rect.height;
					dy = 0;
				}
				if (Dx > 0) {
					x = obj[i].rect.left - w;
				}
				if (Dx < 0) {
					x = obj[i].rect.left + obj[i].rect.width;
				}

			}
		}
	}
}
void Enemy::Intelligence(float* px, float* py, int ph, int pw, int* phealth, float* pspeed, int mapWidth, int mapHeight, float time) {
	*pspeed = 1;
	if (name == "enemy1" || name == "enemy2" || name == "enemy3") {

		if (name == "enemy1") viewradius = 200;
		else if (name == "enemy2") viewradius = 300;
		else if (name == "enemy3") viewradius = 500;
		if (abs(*px - x) < viewradius && abs(*py - y) < viewradius || abs(*px - x) < 20)
		{
			if (name == "enemy2" || name == "enemy3")
			{
				if (dx == speed) { estate = right; }
				else if (dx == -speed) { estate = left; }
				else if (dy == speed) { estate = down; }
				else if (dy == -speed) { estate = up; }
			}

			if (getRect().intersects(FloatRect(*px, *py, pw, ph)))
			{
				if (intersect == 0) {
					CurrentFrame = 0;
					intersect = 1;
				}
				if (name == "enemy2") {
					if (estate == left) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(110 * int(CurrentFrame), 110 * 5, w, h));
					}
					else if (estate == right) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(110 * int(CurrentFrame), 110 * 6, w, h));
					}
					else if (estate == up) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(110 * int(CurrentFrame), 110 * 7, w, h));
					}
					else if (estate == down) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(110 * int(CurrentFrame), 4 * 110, w, h));
					}
				}
				if (name == "enemy3") {
					if (estate == left) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(220 * int(CurrentFrame), 220 * 5, w, h));
					}
					else if (estate == right) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(220 * int(CurrentFrame), 220 * 6, w, h));
					}
					else if (estate == up) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(220 * int(CurrentFrame), 220 * 7, w, h));
					}
					else if (estate == down) {
						CurrentFrame += 0.002 * time;
						if (CurrentFrame > 2) CurrentFrame -= 2;
						sprite.setTextureRect(IntRect(220 * int(CurrentFrame), 4 * 220, w, h));
					}
				}
				if (itime > 1.0) {
					*phealth -= 5;
					if (name == "enemy2") *phealth -= 10;
					if (name == "enemy3") *phealth -= 20;
					itime = 0;
					clockIrestart = 1;
				}
			}
			else
			{
				intersect = 0;
			}
			if (abs(*px - x) < abs(*py - y))
			{
				if (*py - y > 0)
				{
					dy = speed;
					dx = 0;

				}
				else if (*py - y < 0)
				{
					dy = -speed;
					dx = 0;
				}
			}
			if (abs(*px - x) > abs(*py - y))
			{
				if (*px - x > 0)
				{
					dx = speed;
					dy = 0;
				}
				else if (*px - x < 0)
				{
					dx = -speed;
					dy = 0;
				}
			}
		}
	}
}
void Enemy::update(float time)
{
	x += dx * time;
	y += dy * time;
	if (name == "enemy1") {
		AnimationEnemy(time, 4, 50, 0, 0.003);
		checkCollisionWithMap(dx, 0);
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
	}
	else if (name == "enemy2") {
		AnimationEnemy(time, 0, 110, 110, 0.005);
		checkCollisionWithMap(dx, 0);
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
	}
	else if (name == "enemy3") {
		AnimationEnemy(time, 0, 220, 220, 0.005);
		checkCollisionWithMap(dx, 0);
		checkCollisionWithMap(0, dy);
		sprite.setPosition(x + w / 2, y + h / 2);
		if (health <= 0) { life = false; }
	}
}