#include "Game.h"
#include "fstream"
using namespace sf;

int main() {
	setlocale(0, "Russian");
	std::ifstream in;
	in.open("winprop.txt");
	int i;
	bool VSYNC;
	char buff[50];
	if (in.is_open())
	{
		in.getline(buff, 50);
		if (atoi(buff) == 1) {
			i = 8;
		}
		else {
			i = 7;
		}
		std::memset(buff, 0, sizeof(buff));
		in.getline(buff, 50);
		if (atoi(buff) == 1) {
			VSYNC = 1;
		}
		else{
			VSYNC = 0;
		}
		std::memset(buff, 0, sizeof(buff));
	}
	in.close();
	Image icon;
	icon.loadFromFile("images/Icon.png");
	RenderWindow window(VideoMode::getDesktopMode(), "Indifference", i);
	window.setIcon(32,32,icon.getPixelsPtr());
	if (VSYNC = 1) {
		window.setVerticalSyncEnabled(true);
	}
	else {
		window.setVerticalSyncEnabled(false);
	}
	gameRun(window);
	return 0;
}



