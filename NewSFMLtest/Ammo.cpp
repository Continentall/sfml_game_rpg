#include "Ammo.h"

Bullet::Bullet(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H, int dir) :Entity(image, Name, X, Y, W, H)
{
	obj = lvl.getObjectsByType("solid");
	x = X;
	y = Y;
	direction = dir;
	speed = 0.8;
	w = h = 16;
	life = true;
}
void Bullet::update(float time)
{
	switch (direction)
	{
	case 0: dx = -speed; dy = 0;   break;//������� �������� state = left
	case 1: dx = speed; dy = 0;   break;//������� �������� state = right
	case 2: dx = 0; dy = -speed;   break;//������� �������� state = up
	case 3: dx = 0; dy = speed;   break;//������� �������� state = down
	case 4: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������
	case 5: dx = 0; dy = -speed;   break;//������� �������� �� ������� ��������� � �����������
	}

	x += dx * time;//�������� ���� �� �
	y += dy * time;//�� �

	if (x <= 0)
		x = 1;
	if (y <= 0)
		y = 1;

	for (int i = 0; i < obj.size(); i++)//������ �� �������� solid
		if (getRect().intersects(obj[i].rect)) //���� ���� ������ ���������� � �����,
			life = false;
	sprite.setPosition(x + w / 2 + 20, y + h / 2 + 30);//�������� ������� ����
}