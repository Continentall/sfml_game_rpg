#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "View.h"
using namespace sf;
extern int x; //���������� ������ �� X
extern int y; //���������� ������ �� Y
extern int MenuMode;
extern bool inMenu;
void adaptPicture(Sprite* sprite, RenderWindow& window);
void menu(RenderWindow& window);