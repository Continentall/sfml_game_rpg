#pragma once
#include "Entity.h"
#include "view.h"
#include <fstream>
//������ �����, ����������� ����� ��������
class Player :public Entity {
public:
	//���������� �������� ����� ����� ��������
	float CurrentFrame = 0;
	//���������� �������� ���������� ��� ����� ��� �����
	bool alive = 1;
	//������������ ��������� ��������� �����
	enum { left, right, up, down } state;
	//���������� �������� ���� ������������ ������
	int playerScore;
	//���������� �������� ������ �������� ����� ��� ���
	bool isShoot;
	//���������� �������� ���������� ������� ����� ��� ���
	bool fight = 0;
	//���������� �������� �� ��������� ������
	float speedBoost = 1;
	//���������� �������� ���������� ������ �� ����� ������ ����
	bool lbm_pressed = 0;
	//���������� �������� ������ � ��� ����������� �� ��������
	bool animend = 1;
	//���������� �������� ������ ���� ����� ��� ���
	bool go=0;
	//����������� ������ �����
	Player(Image& image, String Name, TileMap& lev, float X, float Y, int W, int H);
	//������� ���������� �������
	void control(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	bool attackAnimation(int position, float time);
	void update(float time);
	void attack(sf::RenderWindow& window, Player& p, Sprite& attackZone, bool& weMiss);
};
