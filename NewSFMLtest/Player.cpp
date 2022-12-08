#include "Player.h"

Player::Player(Image& image, String Name, TileMap& lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
{
	//������ �������� ����� ������
	playerScore = 0;
	//������� �������� ����������, ��� ����� �� ��������
	isShoot = false;
	//������� ���������� ��������� ������
	state = down;
	//���������� � ������ ���� �������� ������ 
	obj = lev.getAllObjects();
}

void Player::control(float time)
{
	//���� ������ ����� �������
	if (Keyboard::isKeyPressed) {
		//���� ������ ������� A
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			//��� ��� �������� �������� ���������� ������ �������� 1
			go = 1;
			//����������� ��������� ���������
			state = left;
			//������� �������� ��������
			speed = 0.5 * speedBoost;
			//������ ����� ��� ��������
			CurrentFrame += 0.005 * time;
			//���� ������� ���� ����� �� 2�� �� �� ����������
			if (CurrentFrame > 2) CurrentFrame -= 2;
			//������������ ������� ������-����� � �������� ������� ������
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + w, 600, -w, h));
		}
		//���� ������ ������� D
		else if (Keyboard::isKeyPressed(Keyboard::D)) {
			//��� ��� �������� �������� ���������� ������ �������� 1
			go = 1;
			//����������� ��������� ���������
			state = right;
			//������� �������� ��������
			speed = 0.5 * speedBoost;
			//������ ����� ��� ��������
			CurrentFrame += 0.005 * time;
			//���� ������� ���� ����� �� 2�� �� �� ����������
			if (CurrentFrame > 2) CurrentFrame -= 2;
			//������������ ������� ������-����� � �������� ������� ������
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 600, w, h));
		}
		//���� ������ ������� W
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			//��� ��� �������� �������� ���������� ������ �������� 1
			go = 1;
			//����������� ��������� ���������
			state = up;
			//������� �������� ��������
			speed = 0.5 * speedBoost;
			//������ ����� ��� ��������
			CurrentFrame += 0.005 * time;
			//���� ������� ���� ����� �� 3�� �� �� ����������
			if (CurrentFrame > 3) CurrentFrame -= 3;
			//������������ ������� ������-����� � �������� ������� ������
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 100, w, h));
		}
		//���� ������ ������� S
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			//��� ��� �������� �������� ���������� ������ �������� 1
			go = 1;
			//����������� ��������� ���������
			state = down;
			//������� �������� ��������
			speed = 0.5 * speedBoost;
			//������ ����� ��� ��������
			CurrentFrame += 0.005 * time;
			//���� ������� ���� ����� �� 2�� �� �� ����������
			if (CurrentFrame > 2) CurrentFrame -= 2;
			//������������ ������� ������-����� � �������� ������� ������
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 700, w, h));
		}
		//���� ������ ������ ������ ����
		else if (Mouse::isButtonPressed(Mouse::Right)) {
			isShoot = true;
		}
	}
}
void Player::checkCollisionWithMap(float Dx, float Dy) //�������� �������
{
	for (int i = 0; i < obj.size(); i++)
		if (getRect().intersects(obj[i].rect))
			if (obj[i].type == "solid")
			{
				if (Dy > 0) { y = obj[i].rect.top - h;  dy = 0; }
				if (Dy < 0) { y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (Dx > 0) { x = obj[i].rect.left - w; }
				if (Dx < 0) { x = obj[i].rect.left + obj[i].rect.width; }
			}
}
bool Player::attackAnimation(int position, float time) //�������� �����
{
	if (position == 0) {
		CurrentFrame += 0.006 * time;
		if (CurrentFrame > 3)  return true; // ���� ������ � �������� ����� - ����������� �����.
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + w, 500, -w, h));
	}
	else if (position == 1) {
		CurrentFrame += 0.006 * time;
		if (CurrentFrame > 3)  return true; // ���� ������ � �������� ����� - ����������� �����.
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 500, w, h));
	}
	else if (position == 2) {
		CurrentFrame += 0.006 * time;
		if (CurrentFrame > 3)  return true; // ���� ������ � �������� ����� - ����������� �����.
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 300, w, h));
	}
	else if (position == 3) {
		CurrentFrame += 0.006 * time;
		if (CurrentFrame > 3)  return true; // ���� ������ � �������� ����� - ����������� �����.
		sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 200, w, h));
	}
}
void Player::update(float time) //���������� ������
{
	if (Mouse::isButtonPressed(Mouse::Left) && lbm_pressed == 0 && animend == 1) { //  ����� ���� �������� ��������� ��� �� ����������
		fight = 1;
	}
	else if (animend == 0) { //����������� ����� ���� �������� �� �����������
		fight = 1;
	}
	else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::E)) {
		fight = 0;

		control(time);//������� ���������� ����������
		switch (state)
		{
		case right:dx = speed; dy = 0; break;
		case left:dx = -speed; dy = 0; break;
		case up: dx = 0; dy = -speed; break;
		case down: dx = 0; dy = speed; break;
		}
		x += dx * time;
		y += dy * time;
	}
	else
	{
		go = 0;
		if (state == right && Keyboard::isKeyPressed(Keyboard::D) == false) {
			if (int(CurrentFrame) == 0) CurrentFrame += 0.0006 * time;
			else if (int(CurrentFrame) == 1) CurrentFrame += 0.003 * time;
			if (CurrentFrame > 2) CurrentFrame -= 2; // ���� ������ � 2 ����� - ����������� �����.
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 400, w, h));
		}
		else if (state == left && Keyboard::isKeyPressed(Keyboard::A) == false) {
			if (int(CurrentFrame) == 0) CurrentFrame += 0.0006 * time;
			else if (int(CurrentFrame) == 1) CurrentFrame += 0.003 * time;
			if (CurrentFrame > 2) CurrentFrame -= 2; // ���� ������ � 2 ����� - ����������� �����.
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame) + w, 400, -w, h));
		}
		else if (state == down && Keyboard::isKeyPressed(Keyboard::S) == false) {
			if (int(CurrentFrame) == 0) CurrentFrame += 0.0006 * time;
			else if (int(CurrentFrame) == 1) CurrentFrame += 0.003 * time;
			if (CurrentFrame > 2) CurrentFrame -= 2; // ���� ������ � 2 ����� - ����������� �����.
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, w, h));
		}
		else if (state == up && Keyboard::isKeyPressed(Keyboard::W) == false)
		{
			if (int(CurrentFrame) == 0) CurrentFrame += 0.0006 * time;
			else if (int(CurrentFrame) == 1) CurrentFrame += 0.0003 * time;
			if (CurrentFrame > 2) CurrentFrame -= 2; // ���� ������ � 2 ����� - ����������� �����.
			sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 800, w, h));
		}
	}
	if (fight == 1)
	{
		if (attackAnimation(state, time) == 1)
		{
			fight = 0;
			animend = 1;
		}
		else if (attackAnimation(state, time) != 1)
		{
			animend = 0;
			lbm_pressed = 1;
		}
	}
	if (!Mouse::isButtonPressed(Mouse::Left))
	{
		lbm_pressed = 0;
	}
	checkCollisionWithMap(dx, 0);//��������� ������������ �� �
	checkCollisionWithMap(0, dy);//��������� ������������ �� Y
	sprite.setPosition(x + w / 2, y + h / 2);
	if (health <= 0)
	{
		life = false;
	}
	if (!isMove)
	{
		speed = 0;
	}
	if (life)
	{
		getplayercoordinateforview(x, y);
	}
}

void Player::attack(sf::RenderWindow& window, Player& p, Sprite& attackZone, bool& weMiss)//������� ����� �����
{
	weMiss = 1;
	if (p.state == 0)
	{
		attackZone.setTextureRect(IntRect(0, 100, 70, 100)); attackZone.setPosition(p.x - 90, p.y); window.draw(attackZone);
	}
	else if (p.state == 1)
	{
		attackZone.setTextureRect(IntRect(0, 0, 70, 100)); attackZone.setPosition(p.x + 110, p.y); window.draw(attackZone);
	}
	else if (p.state == 2)
	{
		attackZone.setTextureRect(IntRect(0, 200, 100, 70)); attackZone.setPosition(p.x, p.y - 90); window.draw(attackZone);
	}
	else if (p.state == 3)
	{
		attackZone.setTextureRect(IntRect(0, 270, 100, 70)); attackZone.setPosition(p.x, p.y + 110); window.draw(attackZone);
	}
	window.display();
}
