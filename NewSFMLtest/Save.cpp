#include "Save.h"

void save(float x, float y, int health, int playerScore, int numberOfMap) {
	std::ofstream out;// поток для записи
	out.open("saves\\save.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		out << x << std::endl;
		out << y << std::endl;
		out << health << std::endl;
		out << playerScore << std::endl;
		out << numberOfMap << std::endl;
	}
	out.close();
}

void load(float* x, float* y, int* health, int* playerScore, int* numberOfMap) {
	std::ifstream in;// поток для чтения
	in.open("saves\\save.txt"); // окрываем файл для чтения
	char buff[50];
	if (in.is_open())
	{
		in.getline(buff, 50);
		(*x) = atoi(buff);
		std::memset(buff, 0, sizeof(buff));
		in.getline(buff, 50);
		(*y) = atoi(buff);
		std::memset(buff, 0, sizeof(buff));
		in.getline(buff, 50);
		(*health) = atoi(buff);
		std::memset(buff, 0, sizeof(buff));
		in.getline(buff, 50);
		(*playerScore) = atoi(buff);
		std::memset(buff, 0, sizeof(buff));
		in.getline(buff, 50);
		(*numberOfMap) = atoi(buff);
		std::memset(buff, 0, sizeof(buff));
	}
	in.close();
}

bool fileExist() {
	std::ifstream iff("saves\\save.txt");
	if (iff.bad() == true) {
		iff.close();
		return false;
	}
	else {
		iff.close();
		return true;
	}
}