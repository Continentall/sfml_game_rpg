#include "HealthBar.h"

int wx = GetSystemMetrics(SM_CXSCREEN);
int wy = GetSystemMetrics(SM_CYSCREEN);
HealthBar::HealthBar()
{
	image.loadFromFile("images/HPbar.png");
	t.loadFromImage(image);
	s.setTexture(t);
	s.setTextureRect(IntRect(0, 0, 230, 70));
	bar.setFillColor(Color(255, 255, 255));//черный прямоугольник накладывается сверху и появляется эффект отсутствия здоровья
	max = 100;
	min = 0;
}
void HealthBar::update(int k)// k-текущее здоровье
{
	if (k >= 0)
		if (k <= max)
			bar.setSize(Vector2f(k * 218 / max, 49));//если не отрицательно и при этом меньше максимума
		else
			bar.setSize(Vector2f(0, 0));
}
void HealthBar::draw(RenderWindow& window)
{
	Vector2f center = window.getView().getCenter();
	Vector2f size = window.getView().getSize();
	s.setPosition((window.getView().getCenter().x - s.getLocalBounds().width / 2 - wx / 3.6 + 50), ((window.getView().getCenter().y - s.getLocalBounds().height / 2) - wy / 3.4));//позиция на экране
	bar.setPosition((window.getView().getCenter().x - s.getLocalBounds().width / 2 - wx / 3.6 + 56), ((window.getView().getCenter().y - s.getLocalBounds().height / 2) - wy / 3.4 + 11));
	window.draw(s);
	window.draw(bar);
}