#pragma once
#include "Entity.h"
#include "View.h"

class Npc :public Entity {
public:
	bool nearToNPC = 0;
	float CurrentFrame = 0;
	bool e_pressed = false;
	std::wstring npcname;
	bool altarwasbroken = 0;
	
	Npc(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H);
	
	bool talking(RenderWindow& window, float px, float py, float pdx, float pdy, std::wstring text, Font mainFont, Sprite dialogScreenSprite, bool* inDialog, bool* contDialog, bool* inPause);

	void update(float time);
};
