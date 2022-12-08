#pragma once
#include <fstream>

void save(float x, float y, int health, int playerScore, int numberOfMap);
void load(float* x, float* y, int* health, int* playerScore, int* numberOfMap);

bool fileExist();
