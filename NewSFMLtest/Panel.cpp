#include "Panel.h"

bool alert(sf::RenderWindow& window, std::string path, bool* inPause, float px, float py) {
	sf::Texture texture;
	texture.loadFromFile(path);
	sf::Sprite img(texture);
	float xsize = ((float)window.getView().getSize().x / (float)texture.getSize().x);
	float ysize = ((float)window.getView().getSize().y / (float)texture.getSize().y);
	img.setScale(xsize, ysize);
	img.setPosition(px, py);
	*inPause = 1;
	window.draw(img);
	window.display();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		*inPause = 0;
		return false;

	}
	return true;
}

std::wstring getDialog(std::string path) {
	std::ifstream fin(path);
	if (!fin.good()) return L"Dialog " + path + L" not foung";
	fin.seekg(0, std::ios_base::end);
	size_t uSize = fin.tellg();
	fin.seekg(0);
	char* t = new char[uSize + 1];
	fin.read(t, uSize);
	t[fin.gcount()] = 0; //реальная длина строки может быть меньше размера файла
	std::string str(t);
	int wchars_num = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	std::wstring wide;
	wide.resize(wchars_num); // или через конструктор wide(wchars_num, 0);
	MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, &wide[0], wchars_num);
	return wide;
}

bool Pause(sf::RenderWindow& window, Player& p, float& time, Sprite GamePausedSprite, Sprite ContinueS, Sprite GoToMenuS, Clock* clock, bool* gameWasStarted, int* menuButtonNumPaused, bool* inDialog, bool* inPause, int* savedPlayerNumberOfMap, float vx, float vy) {
	Vector2f centerPos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		p.update(time);
		window.setMouseCursorVisible(true);
		*inPause = 1;
		sf::Vector2u size = GamePausedSprite.getTexture()->getSize();
		float xsize = ((float)window.getView().getSize().x / (float)size.x);
		float ysize = ((float)window.getView().getSize().y / (float)size.y);
		GamePausedSprite.setScale(xsize, ysize);
		GamePausedSprite.setPosition(vx, vy);
		ContinueS.setScale(xsize, ysize);
		GoToMenuS.setScale(xsize, ysize);
		ContinueS.setPosition(window.getView().getCenter().x - ContinueS.getLocalBounds().width * xsize / 2 + 1, window.getView().getCenter().y - ContinueS.getLocalBounds().height / 2 + 10);
		GoToMenuS.setPosition(window.getView().getCenter().x - GoToMenuS.getLocalBounds().width * xsize / 2 + 1, window.getView().getCenter().y - GoToMenuS.getLocalBounds().height / 2 + 120);
		while (*inPause == 1 && *inDialog == 0) {
			Event eventPause;
			while (window.pollEvent(eventPause))
			{
				if (eventPause.type == sf::Event::Closed) { window.close(); }
			}
			ContinueS.setColor(Color::White);
			GoToMenuS.setColor(Color::White);
			if (IntRect(centerPos.x - ContinueS.getGlobalBounds().width / 2, centerPos.y - ContinueS.getGlobalBounds().height / 2 + 10, 600, 100).contains(Mouse::getPosition(window))) { ContinueS.setColor(Color(128, 128, 128)); *menuButtonNumPaused = 1; }
			if (IntRect(centerPos.x - GoToMenuS.getGlobalBounds().width / 2, centerPos.y - GoToMenuS.getGlobalBounds().height / 2 + 120, 600, 100).contains(Mouse::getPosition(window))) { GoToMenuS.setColor(Color(128, 128, 128)); *menuButtonNumPaused = 2; }
			if (Mouse::isButtonPressed(Mouse::Left)) {
				if (*menuButtonNumPaused == 1)
				{
					*inPause = 0;
					window.setMouseCursorVisible(false);
					(*clock).restart();
					return false;
				}
				if (*menuButtonNumPaused == 2)
				{
					window.setMouseCursorVisible(true);
					save(p.x, p.y, p.health, p.playerScore, *savedPlayerNumberOfMap);
					*inPause = 0;
					inMenu = 1;
					window.clear();
					*gameWasStarted = 0;
					return true;
				}
			}
			window.draw(GamePausedSprite);
			window.draw(ContinueS);
			window.draw(GoToMenuS);
			window.display();
		}
	}
}