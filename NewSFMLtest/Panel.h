#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include "Save.h"
#include "Player.h"
#include "Menu.h"

bool alert(sf::RenderWindow& window, std::string path, bool* inPause, float px, float py);

std::wstring getDialog(std::string path);

bool Pause(sf::RenderWindow& window, Player& p, float& time, Sprite GamePausedSprite, Sprite ContinueS, Sprite GoToMenuS, Clock* clock, bool* gameWasStarted, int* menuButtonNumPaused, bool* inDialog, bool* inPause, int* savedPlayerNumberOfMap, float vx, float vy);