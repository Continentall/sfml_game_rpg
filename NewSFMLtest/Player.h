#pragma once
#include "Entity.h"
#include "view.h"
#include <fstream>
//Класса игрок, наследующий класс сущность
class Player :public Entity {
public:
	//переменная хранящая номер кадра анимации
	float CurrentFrame = 0;
	//переменная хранящая информацию жив герой или мертв
	bool alive = 1;
	//Перечесление возможных состояний героя
	enum { left, right, up, down } state;
	//переменная хранящая очки заработанные героем
	int playerScore;
	//переменная хранящая данные стреляет герой или нет
	bool isShoot;
	//переменная хранящая информацию атакует герой или нет
	bool fight = 0;
	//переменная влияющая на ускорение игрока
	float speedBoost = 1;
	//переменная хранящая информацию нажата ли левая кнопка мыши
	bool lbm_pressed = 0;
	//переменная хранящая данные о том закончилась ли анимация
	bool animend = 1;
	//переменная хранящая данные идет герой или нет
	bool go=0;
	//Конструктор класса игрок
	Player(Image& image, String Name, TileMap& lev, float X, float Y, int W, int H);
	//Функция управления игроком
	void control(float time);
	void checkCollisionWithMap(float Dx, float Dy);
	bool attackAnimation(int position, float time);
	void update(float time);
	void attack(sf::RenderWindow& window, Player& p, Sprite& attackZone, bool& weMiss);
};
