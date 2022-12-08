#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "View.h"
using namespace sf;
extern int x; //Разрешение экрана по X
extern int y; //Разрешение экрана по Y
extern int MenuMode;
extern bool inMenu;
void adaptPicture(Sprite* sprite, RenderWindow& window);
void menu(RenderWindow& window);