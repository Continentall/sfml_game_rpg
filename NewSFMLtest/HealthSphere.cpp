#include "HealthSphere.h"

HealthSphere::HealthSphere(Image& image, String Name, TileMap& lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H) {
	obj = lvl.getAllObjects();
	sprite.setTextureRect(IntRect(0, 0, w, h));
}
void HealthSphere::update(float time)
{
	CurrentFrame += 0.005 * time;
	if (CurrentFrame > 3) CurrentFrame -= 3; // если пришли к третьему кадру - откидываемся назад.
	sprite.setTextureRect(IntRect(32 * int(CurrentFrame), 0, w, h));
	sprite.setPosition(x + w / 2, y + h / 2);
}