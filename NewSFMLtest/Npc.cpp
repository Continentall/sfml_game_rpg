#include "Npc.h"

Npc::Npc(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	obj = lvl.getAllObjects();
}

bool Npc::talking(RenderWindow& window, float px, float py, float pdx, float pdy, std::wstring text, Font mainFont, Sprite dialogScreenSprite, bool* inDialog, bool* contDialog, bool* inPause) {
	if (abs(px - x) < 200 && abs(py - y) < 200 && Keyboard::isKeyPressed(Keyboard::E) && pdx == 0 && pdy == 0 || (*contDialog == true && abs(px - x) < 200 && abs(py - y) < 200)) {
		nearToNPC = 1;
		float camx = view.getCenter().x - (view.getSize().x / 2);
		float camy = view.getCenter().y - (view.getSize().y / 2);
		sf::Vector2u size = dialogScreenSprite.getTexture()->getSize();
		float xsize = ((float)window.getView().getSize().x / (float)size.x);
		float ysize = ((float)window.getView().getSize().y / (float)size.y);
		dialogScreenSprite.setScale(xsize, ysize);
		if (name == "Tyannus") {
			npcname = L"Тианий";
			*inPause = 1;
			Text gidName(npcname, mainFont, 20);
			Text gidSpeach(text, mainFont, 20);
			gidName.setPosition(window.getView().getCenter().x - gidName.getLocalBounds().width / 2, window.getView().getCenter().y - gidName.getLocalBounds().height / 2 - 220);
			dialogScreenSprite.setPosition(camx, camy);
			gidSpeach.setPosition(window.getView().getCenter().x - gidSpeach.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach.getLocalBounds().height / 2);
			if (*inDialog == 1) {
				window.draw(dialogScreenSprite);
				window.draw(gidName);
				window.draw(gidSpeach);
				window.display();
			}
		}
		else if (name == "Piano") {
			npcname = L"Рояль";
			*inPause = 1;
			Text gidName(npcname, mainFont, 20);
			Text gidSpeach1(L"Четыре первые клавиши сильно потёрты\nВозможно вы можете ввести числовой пароль\n", mainFont, 20);
			Text gidSpeach(text, mainFont, 20);
			gidName.setPosition(window.getView().getCenter().x - gidName.getLocalBounds().width / 2, window.getView().getCenter().y - gidName.getLocalBounds().height / 2 - 220);
			gidSpeach1.setPosition(window.getView().getCenter().x - gidSpeach1.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach1.getLocalBounds().height / 2);
			gidSpeach.setPosition(window.getView().getCenter().x - gidSpeach.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach.getLocalBounds().height / 2 + 50);
			dialogScreenSprite.setPosition(camx, camy);
			if (*inDialog == 1) {
				window.draw(dialogScreenSprite);
				window.draw(gidName);
				window.draw(gidSpeach1);
				window.draw(gidSpeach);
				window.display();
			}
		}
		else if (name == "Lira") {
			npcname = L"Лира";
			*inPause = 1;
			Text gidName(npcname, mainFont, 20);
			Text gidSpeach(text, mainFont, 20);
			gidName.setPosition(window.getView().getCenter().x - gidName.getLocalBounds().width / 2, window.getView().getCenter().y - gidName.getLocalBounds().height / 2 - 220);
			dialogScreenSprite.setPosition(camx, camy);
			gidSpeach.setPosition(window.getView().getCenter().x - gidSpeach.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach.getLocalBounds().height / 2);
			if (*inDialog == 1) {
				window.draw(dialogScreenSprite);
				window.draw(gidName);
				window.draw(gidSpeach);
				window.display();
			}
		}
		else if (name == "Teodor") {
			npcname = L"Теодор";
			*inPause = 1;
			Text gidName(npcname, mainFont, 20);
			Text gidSpeach(text, mainFont, 17);
			gidName.setPosition(window.getView().getCenter().x - gidName.getLocalBounds().width / 2, window.getView().getCenter().y - gidName.getLocalBounds().height / 2 - 220);
			dialogScreenSprite.setPosition(camx, camy);
			gidSpeach.setPosition(window.getView().getCenter().x - gidSpeach.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach.getLocalBounds().height / 2);
			if (*inDialog == 1) {
				window.draw(dialogScreenSprite);
				window.draw(gidName);
				window.draw(gidSpeach);
				window.display();
			}
		}
		else if (name == "Teodor2") {
			npcname = L"Теодор";
			*inPause = 1;
			Text gidName(npcname, mainFont, 20);
			Text gidSpeach(text, mainFont, 20);
			gidName.setPosition(window.getView().getCenter().x - gidName.getLocalBounds().width / 2, window.getView().getCenter().y - gidName.getLocalBounds().height / 2 - 220);
			dialogScreenSprite.setPosition(camx, camy);
			gidSpeach.setPosition(window.getView().getCenter().x - gidSpeach.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach.getLocalBounds().height / 2);
			if (*inDialog == 1) {
				window.draw(dialogScreenSprite);
				window.draw(gidName);
				window.draw(gidSpeach);
				window.display();
			}
		}
		else if (name == "Cross") {
			npcname = L"Крест";
			*inPause = 1;
			altarwasbroken = 1;
			Text gidName(npcname, mainFont, 20);
			Text gidSpeach(text, mainFont, 20);
			gidName.setPosition(window.getView().getCenter().x - gidName.getLocalBounds().width / 2, window.getView().getCenter().y - gidName.getLocalBounds().height / 2 - 220);
			dialogScreenSprite.setPosition(camx, camy);
			gidSpeach.setPosition(window.getView().getCenter().x - gidSpeach.getLocalBounds().width / 2, window.getView().getCenter().y - gidSpeach.getLocalBounds().height / 2);
			if (*inDialog == 1) {
				window.draw(dialogScreenSprite);
				window.draw(gidName);
				window.draw(gidSpeach);
				window.display();
			}
		}
	}
	else
	{
		nearToNPC = 0;
		*inPause = 0;

	}
	if (Keyboard::isKeyPressed(Keyboard::E) && !e_pressed && nearToNPC == 1) {
		if (*inDialog == 1) { *inDialog = 0; }
		else
			*inDialog = 1;
		e_pressed = true;
	}
	if (!Keyboard::isKeyPressed(Keyboard::E))
		e_pressed = false;
	if (*inDialog == 1) {
		return true;
	}
	else {
		return false;
	}
}
void Npc::update(float time)
{
	if (name == "Tyannus") {//для персонажа с таким именем логика будет такой
		if (int(CurrentFrame) == 0) CurrentFrame += 0.0002 * time;
		else if (int(CurrentFrame) == 1) CurrentFrame += 0.003 * time;
		if (CurrentFrame > 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, w, h));
		sprite.setPosition(x + w / 2, y + h / 2);
	}
	else if (name == "Piano") {
		sprite.setPosition(x + w / 2, y + h / 2);
	}
	else if (name == "Cross" && altarwasbroken == 0) {
		CurrentFrame += 0.002 * time;
		if (CurrentFrame > 4) CurrentFrame -= 4;
		sprite.setTextureRect(IntRect(200 * int(CurrentFrame), 0, w, h));
		sprite.setPosition(x + 25, y + 25);
	}
	else if (name == "Cross" && altarwasbroken == 1) {
		sprite.setColor(Color::Transparent);
	}
	else if (name == "Lira") {//для персонажа с таким именем логика будет такой
		if (int(CurrentFrame) == 0) CurrentFrame += 0.0002 * time;
		else if (int(CurrentFrame) == 1) CurrentFrame += 0.009 * time;
		if (CurrentFrame > 2) CurrentFrame -= 2;
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, w, h));
		sprite.setPosition(x + w / 2, y + h / 2);
	}
	else if (name == "Teodor" || name == "Teodor2") {//для персонажа с таким именем логика будет такой
		CurrentFrame += 0.004 * time;
		if (CurrentFrame > 6) CurrentFrame -= 6;
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, w, h));
		sprite.setPosition(x + w / 2, y + h / 2);
	}
}