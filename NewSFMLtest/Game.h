#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <Windows.h>
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "Ammo.h"
#include "Menu.h"
#include "View.h"
#include "HealthBar.h"
#include "Level.h"
#include "HealthSphere.h";
#include "Npc.h"
#include "Save.h"
#include "Panel.h"

using namespace sf;
int lvlcounter = 0;
bool musicplay = 1;
bool refreshsteps = 1;
bool weMiss;
bool gameWasStarted = 0;
int menuButtonNumPaused = 0;
bool inPause = 0;
bool inDialog = 0;
float savedPlayerX;
float savedPlayerY;
int savedPlayerHealth;
int savedPlayerScore;
int savedPlayerNumberOfMap;
bool guideAllert;
bool saveFound;
bool newCord;
bool contDialog = 0;
int training_part = 0;
int trainingSpeach = 0;
std::string songName = "1";
bool goodending = 0;
bool badending = 0;

std::wstring passwordlvl0 = L"";
bool alive(RenderWindow& window)
{
	view.reset(FloatRect(0, 0, x, y));
	window.setView(view);
	view.zoom(0.65f);
	if (gameWasStarted == 0)
	{
		window.clear();
		menu(window);
		gameWasStarted = 1;

		//Проверка наличия сохранения
		if (fileExist() == true && MenuMode == 1)
		{
			load(&savedPlayerX, &savedPlayerY, &savedPlayerHealth, &savedPlayerScore, &savedPlayerNumberOfMap);
			saveFound = 1;
		}
		else if (MenuMode == 0)
		{
			savedPlayerNumberOfMap = 0;
			savedPlayerHealth = 100;
			saveFound = 0;
			guideAllert = 0;
		}
	}
	Vector2f centerPos = Vector2f(window.getSize().x / 2, window.getSize().y / 2);
	TileMap lvl;

	lvl.load("maps/map" + std::to_string(savedPlayerNumberOfMap) + ".tmx");

	SoundBuffer shootBuffer;//создаём буфер для звука выстрела
	shootBuffer.loadFromFile("sounds/shoot.ogg");//загружаем в него звук
	Sound shoot(shootBuffer);//создаем звук и загружаем в него звук выстрела из буфера

	SoundBuffer stepsBuffer;//создаём буфер для звука выстрела
	stepsBuffer.loadFromFile("sounds/steps.ogg");//загружаем в него звук
	Sound steps(stepsBuffer);//создаем звук и загружаем в него звук выстрела из буфера

	SoundBuffer defeatBuffer;//создаём буфер для звука проигрыша
	defeatBuffer.loadFromFile("sounds/defeat.ogg");//загружаем в него звук
	Sound defeat(defeatBuffer);//создаем звук и загружаем в него звук из буфера

	SoundBuffer swordSwingBuffer;//создаём буфер для звука удара мечом
	swordSwingBuffer.loadFromFile("sounds/SwordSwing.ogg");//загружаем в него звук
	Sound swordSwing(swordSwingBuffer);

	SoundBuffer swordHitBuffer;//создаём буфер для звука попадания мечом
	swordHitBuffer.loadFromFile("sounds/SwordHit.ogg");//загружаем в него звук
	Sound swordHit(swordHitBuffer);

	Music music;

	Texture attackZoneImage;
	attackZoneImage.loadFromFile("images/SwordSwing.png");
	Sprite attackZone(attackZoneImage);

	Image heroImage;
	heroImage.loadFromFile("images/Person.png");

	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/EasyEnemy(sphere).png");

	Image enemySkeleton;
	enemySkeleton.loadFromFile("images/Skelet.png");

	Image liraNpc;
	liraNpc.loadFromFile("images/npcGirl.png");

	Image teodorNpc;
	teodorNpc.loadFromFile("images/MageNpc.png");

	Image enemyBossSkeleton;
	enemyBossSkeleton.loadFromFile("images/SkeletBoss.png");

	Image GidNpcImage;
	GidNpcImage.loadFromFile("images/npcCommander.png");

	Image blik;
	blik.loadFromFile("images/blik.png");

	Image blik2;
	blik2.loadFromFile("images/blik2.png");

	Image healthSphereImage;
	healthSphereImage.loadFromFile("images/HealthRecovery.png");

	Texture GamePausedTexture, ContinueT, GoToMenuT;
	GamePausedTexture.loadFromFile("images/PauseScreen.png");
	ContinueT.loadFromFile("images/CONTINUEGAMETXT.png");
	GoToMenuT.loadFromFile("images/GOTOMENUTXT.png");
	Sprite GamePausedSprite(GamePausedTexture), ContinueS(ContinueT), GoToMenuS(GoToMenuT);
	Image BulletImage;
	BulletImage.loadFromFile("images/bullet.png");
	BulletImage.createMaskFromColor(Color(0, 0, 0));
	Font mainFont;
	mainFont.loadFromFile("fonts/Lugatype.otf");
	HealthBar playerHealthBar;
	Object player = lvl.getObject("player");
	Text textPassword("", mainFont, 200);
	Text training(L"", mainFont, 20);
	if (!saveFound || newCord)
	{
		savedPlayerX = player.rect.left;
		savedPlayerY = player.rect.top;
		save(savedPlayerX, savedPlayerY, savedPlayerHealth,savedPlayerScore, savedPlayerNumberOfMap);
		newCord = 0;
	}
	Player p(heroImage, "Player1", lvl, savedPlayerX, savedPlayerY, 100, 100);//объект класса игрока
	p.playerScore = savedPlayerScore;
	p.health = savedPlayerHealth;
	std::list<Enemy*> entities; // список для врагов
	std::list<Enemy*>::iterator it; //итератор для списка врагов
	std::list<Entity*> ammos;//второй итератор.для взаимодействия между объектами списка
	std::list<Entity*>::iterator itAmmo;//второй итератор.для взаимодействия между объектами списка
	std::list<Enemy*>::iterator it2;//второй итератор.для взаимодействия между объектами списка
	std::list<Entity*> HealthRec; //Список сфер лечения
	std::list<Entity*>::iterator itHR; //итератор сфер лечения
	std::vector<Object > HealthRecovery = lvl.getObjectsByName("healthRecovery");
	std::vector<Object> e = lvl.getObjectsByType("enemy"); // Вектор для всех врагов
	std::vector<Object> NPC = lvl.getObjectsByType("Npc");
	std::vector<Object> Teleport = lvl.getObjectsByType("Teleport");
	std::list<Npc*> NpcList; //Список npc
	std::list<Npc*>::iterator itNPC;

	for (int i = 0; i < e.size(); i++)
	{
		if (e[i].name == "enemy1")
			entities.push_back(new Enemy(easyEnemyImage, e[i].name, lvl, e[i].rect.left, e[i].rect.top, 50, 100));
		else if (e[i].name == "enemy2")
			entities.push_back(new Enemy(enemySkeleton, e[i].name, lvl, e[i].rect.left, e[i].rect.top, 110, 110));
		else if (e[i].name == "enemy3")
			entities.push_back(new Enemy(enemyBossSkeleton, e[i].name, lvl, e[i].rect.left, e[i].rect.top, 220, 220));
	}
	for (int i = 0; i < HealthRecovery.size(); i++)
		HealthRec.push_back(new HealthSphere(healthSphereImage, "HealthSphere", lvl, HealthRecovery[i].rect.left, HealthRecovery[i].rect.top, 32, 32));
	for (int i = 0; i < NPC.size(); i++)
	{
		if (NPC[i].name == "Tyannus")
			NpcList.push_back(new Npc(GidNpcImage, NPC[i].name, lvl, NPC[i].rect.left, NPC[i].rect.top, 100, 100));
		else if (NPC[i].name == "Piano")
			NpcList.push_back(new Npc(blik, NPC[i].name, lvl, NPC[i].rect.left, NPC[i].rect.top, 100, 100));
		else if (NPC[i].name == "Lira")
			NpcList.push_back(new Npc(liraNpc, NPC[i].name, lvl, NPC[i].rect.left, NPC[i].rect.top, 100, 100));
		else if (NPC[i].name == "Cross")
			NpcList.push_back(new Npc(blik2, NPC[i].name, lvl, NPC[i].rect.left, NPC[i].rect.top, 200, 200));
		else if (NPC[i].name == "Teodor")
			NpcList.push_back(new Npc(teodorNpc, NPC[i].name, lvl, NPC[i].rect.left, NPC[i].rect.top, 100, 100));
		else if (NPC[i].name == "Teodor2")
			NpcList.push_back(new Npc(teodorNpc, NPC[i].name, lvl, NPC[i].rect.left, NPC[i].rect.top, 100, 100));
	}
	float px = p.x;
	Clock clock;
	Texture dialogScreen;
	dialogScreen.loadFromFile("images/DialogFrame.png");
	Sprite dialogScreenSprite(dialogScreen);
	window.setMouseCursorVisible(false);
	while (window.isOpen() && inMenu == false)
	{
		if (savedPlayerNumberOfMap == 4 || savedPlayerNumberOfMap == 7 || savedPlayerNumberOfMap == 10 || savedPlayerNumberOfMap == 15)
			songName = std::to_string(savedPlayerNumberOfMap);
		if (musicplay)
		{
			lvlcounter = savedPlayerNumberOfMap;
			music.openFromFile("sounds/"+ songName +".ogg");
			music.setVolume(60);
			music.play();
			music.setLoop(true);
			musicplay = 0;
		}
		
		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		attackZone.setPosition(0, 0);
		p.sprite.setColor(Color::White);
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			musicplay = 1;
			Pause(window, p, time, GamePausedSprite, ContinueS, GoToMenuS, &clock, &gameWasStarted, &menuButtonNumPaused, &inDialog, &inPause, &savedPlayerNumberOfMap, view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2));
		}
		if (inPause == 1) 
			time = 0;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			//Удар мечом
			if (event.type == Event::MouseButtonPressed && inDialog == 0 && inPause == 0)
			{
				if (Mouse::isButtonPressed(Mouse::Left))
					p.attack(window, p, attackZone, weMiss);
				//Стрельба
				else if (Mouse::isButtonPressed(Mouse::Right))
				{
					ammos.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state));
					shoot.play();
				}
			}
		}
		//Проход во вектору телепортов на карте
		for (int i = 0; i < Teleport.size(); i++)
		{
			//Если игрок пересекается с одним из телепортов
			if (p.getRect().intersects(Teleport[i].rect))
			{
				//Если игрок находится на обуч. уровне и не ввел верный пароль
				if (savedPlayerNumberOfMap == 0 && passwordlvl0 != "2004")
					break;
				//Цикл переберающий числа от 0 до 20
				for (int j = 0; j < 20; j++)
				{
					//Если мы пересеклись с телепортом под номером j
					if (Teleport[i].name == "Tp" + std::to_string(j))
					{
						//Указание что на след уровне должна быть музыка
						musicplay = 1;
						//MenuMode = 1;
						//Сохранение в переменную номера карты на которую перешел игрок
						savedPlayerNumberOfMap = j;
						//Сохранение в переменную показателя здоровья игрока
						savedPlayerHealth = p.health;
						//Сохранение в переменную счета игрок
						savedPlayerScore = p.playerScore;
						//Указание на изменение координат игрока
						newCord = 1;
						//Перезапуск функции игры
						return true;
					}
				}
			}
		}
		for (itHR = HealthRec.begin(); itHR != HealthRec.end();)
		{
			Entity* x = *itHR;
			x->update(time);
			if ((*itHR)->getRect().intersects(p.getRect()))
			{
				if (p.health <= 60) { p.health += 40; }
				else if (p.health > 60) { p.health = 100; }
				itHR = HealthRec.erase(itHR);
				delete x;
			}
			else
				itHR++;
		}
		//Диалоги с npc
		bool nearToNPC;
		for (itNPC = NpcList.begin(); itNPC != NpcList.end();)
		{
			Entity* o = *itNPC;
			o->update(time);
			//Если имя НПС - Piano делаем следующее
			if ((*itNPC)->name == "Piano")
			{
				//Пока функция talking возвразает значение true делаем указанное
				while ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, passwordlvl0, mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
				{
					Event inpurpass; //создаем событие
					while (window.pollEvent(inpurpass)) //Пока событие выолняется делаем указанное
					{
						if (inpurpass.type == Event::Closed) //Если произошло событие закрытия приложения
							window.close(); //закрываем окно
						//Если произошло события ввода текста и кнопка Enter не нажата выполняем указанное
						if (inpurpass.type == Event::TextEntered && Keyboard::isKeyPressed(Keyboard::Enter) == false)
						{
							// отсекаем не ASCII символы
							if (inpurpass.text.unicode < 59 && inpurpass.text.unicode > 47)
							{
								//Записываем в переменную введенные данные
								passwordlvl0 += static_cast<char>(inpurpass.text.unicode);
								//Указание, что окно предется перезагрузить и заново открыть
								contDialog = true;
								//Если длина введенного пароля больше 4
								if (passwordlvl0.size() > 4)
									passwordlvl0.clear();
								break;
							}
						}
					}
					continue;
				}
				//Указание что диалог прекращается
				contDialog = 0;
			}
			else if ((*itNPC)->name == "Tyannus")
			{

				if (entities.empty() == false && passwordlvl0 != "2004")
				{
					if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/1Tyannus.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
					{
						trainingSpeach = 1;
						continue;
					}
				}
				else if ((*itNPC)->name == "Tyannus" && entities.empty() == true && passwordlvl0 != "2004")
				{
					if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/2Tyannus.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
					{
						trainingSpeach = 2;
						continue;
					}
				}
				else if ((*itNPC)->name == "Tyannus" && passwordlvl0 == "2004")
				{
					if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/3Tyannus.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
					{
						trainingSpeach = 3;
						continue;
					}
				}
			}
			else if ((*itNPC)->name == "Lira") {
				if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/1Lira.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
					continue;
			}
			else if ((*itNPC)->name == "Cross" && (*itNPC)->altarwasbroken == 0) {
				if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/1Cross.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
					continue;
			}
			else if ((*itNPC)->name == "Cross" && (*itNPC)->altarwasbroken == 1) {
				if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/2Cross.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
				{
					goodending = 1;
					continue;
				}
			}
			else if ((*itNPC)->name == "Teodor") {
				if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/1Teodor.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
					continue;
			}
			else if ((*itNPC)->name == "Teodor2") {
				if ((*itNPC)->talking(window, p.x, p.y, p.dx, p.dy, getDialog("texts/2Teodor.txt"), mainFont, dialogScreenSprite, &inDialog, &contDialog, &inPause) == true)
				{
					badending = 1;
					continue;
				}
			}
			itNPC++;
		}
		//Телепортация, если игрок вышел за стены
		if (p.x > lvl.widthOfmap || p.y > lvl.heightOfmap || p.y < 0 || p.x < 0)
		{
			if (p.x < 0)
				p.x = 50;
			else if (p.x > lvl.widthOfmap)
				p.x = lvl.widthOfmap - 50;
			else if (p.y > lvl.heightOfmap)
				p.y = lvl.heightOfmap - 50;
			else
				p.y = 50;
			
		}
		for (it = entities.begin(); it != entities.end();)
		{
			Enemy* b = *it;
			if (b->clockIrestart == 0)
				b->itime = b->clockIntel.getElapsedTime().asSeconds();
			else
			{
				b->clockIrestart = 0;
				b->clockIntel.restart();
				p.sprite.setColor(Color::Red);
			}
			b->update(time);
			b->Intelligence(&p.x, &p.y, p.w, p.h, &p.health, &p.speedBoost, lvl.widthOfmap, lvl.heightOfmap, time);
			if ((*it)->life == false)
			{
				p.speedBoost = 1;
				it = entities.erase(it);
				delete b;
			}
			else
				it++;
		}
		for (itAmmo = ammos.begin(); itAmmo != ammos.end();)
		{
			Entity* c = *itAmmo;
			c->update(time);
			if ((*itAmmo)->life == false) { itAmmo = ammos.erase(itAmmo); delete c; }
			else itAmmo++;
		}
		for (it = entities.begin(); it != entities.end(); it++)
		{
			if (((*it)->name == "enemy1" || (*it)->name == "enemy2" || (*it)->name == "enemy3") && ((*it)->getRect().intersects(FloatRect(attackZone.getPosition().x, attackZone.getPosition().y, 50, 50))))
			{
				swordHit.play();
				(*it)->health -= 50;
				weMiss = 0;
				attackZone.setPosition(0, 0);
				if (p.state == 0) { (*it)->x -= 30; }
				if (p.state == 1) { (*it)->x += 30; }
				if (p.state == 2) { (*it)->y -= 30; }
				if (p.state == 3 || p.state == 5) { (*it)->y += 30; }
			}
			if ((*it)->getRect().intersects(FloatRect(p.x, p.y, 100, 100)))
				p.speedBoost = 0.4;
			else
				p.speedBoost = 1;
			Entity* enemy = *it;
			for (itAmmo = ammos.begin(); itAmmo != ammos.end(); itAmmo++)
			{
				Entity* bullet = *itAmmo;
				if (bullet->name == "Bullet")
				{
					if (bullet->life == true)
					{
						if (bullet->getRect().intersects(enemy->getRect()))
						{
							bullet->life = false;
							enemy->health -= 20;
							if (enemy->health <= 0) enemy->life = false;
						}
					}
				}
			}
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())
				{
					if (((*it)->getRect().intersects((*it2)->getRect())))
					{
						if ((*it)->dx > 0) { (*it)->x = (*it2)->x - (*it)->w; }
						else if ((*it)->dx < 0) { (*it)->x = (*it2)->x + (*it2)->w; }
						else if ((*it)->dy > 0) { (*it)->y = (*it2)->y - (*it)->h; }
						else if ((*it)->dy < 0) { (*it)->y = (*it2)->y + (*it2)->h; }
					}
				}
			}
		}
		if (weMiss == 1)
		{
			swordSwing.play();
			weMiss = 0;
		}
			p.update(time);
		window.setView(view);
		window.clear();
		if (p.health <= 0)
		{
			music.stop();
			if (inPause == 0)
				defeat.play();
			if (alert(window, "images/GameOverPage.png", &inPause, view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)) != false)
				continue;
			musicplay = 1;
			return true;
		}
		window.draw(lvl);
		for (it = entities.begin(); it != entities.end(); it++)
			window.draw((*it)->sprite);
		for (itAmmo = ammos.begin(); itAmmo != ammos.end(); itAmmo++)
			window.draw((*itAmmo)->sprite);
		for (itHR = HealthRec.begin(); itHR != HealthRec.end(); itHR++)
			window.draw((*itHR)->sprite);
		for (itNPC = NpcList.begin(); itNPC != NpcList.end(); itNPC++)
			window.draw((*itNPC)->sprite);

		if (p.go == 1 && refreshsteps == 1)
		{
			steps.play();
			refreshsteps = 0;
			steps.setLoop(true);
		}
		if (p.go == 0)
		{
			refreshsteps = 1;
			steps.stop();
		}
		window.draw(p.sprite);
		playerHealthBar.update(p.health);
		playerHealthBar.draw(window);
		if (guideAllert == 0 && saveFound == 0) {
			if (alert(window, "images/missionbg.png", &inPause, view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)) != false)
				continue;
			else
				guideAllert = 1;
		}
		//Обучение для игрока 
		if (savedPlayerNumberOfMap == 0 && guideAllert && !inMenu)
		{
			if (Keyboard::isKeyPressed(Keyboard::A) == false && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::S) && training_part == 0)
				training.setString(L"Для перемещения нажмите любую из клавиш w,a,s,d. ");
			else if (training_part == 0)
				training_part = 1;

			if (training_part == 1 && !Mouse::isButtonPressed(Mouse::Left))
				training.setString(L"Для удара мечом нажмите на левую кнопку мыши ");
			else if (training_part == 1)
				training_part = 2;

			if (training_part == 2 && !Mouse::isButtonPressed(Mouse::Right))
				training.setString(L"Для выстрела из подручного мушкета нажмите правую кнопку мыши ");
			else if (training_part == 2)
				training_part = 3;

			if (training_part == 3 && trainingSpeach == 0)
				training.setString(L"Найдите и поговорите с кем-нибудь.Для разговора надо подойти\n к персонажу и нажать кнопку E ");
			else if (training_part == 3)
				training_part = 4;

			if (training_part == 4 && entities.size() != 0)
				training.setString(L"Отлично справляетесь! Давайте найдем и уничтожим врага");
			else if (training_part == 4)
				training_part = 5;

			if (training_part == 5 && HealthRec.size() != 0)
				training.setString(L"Великолепно! Давайте отыщем сферу здоровья и воспользуемся ей\n Для этого достаточно просто пройти через нее. ");
			else if (training_part == 5)
				training_part = 6;

			if (training_part == 6 && trainingSpeach != 2 && trainingSpeach != 3)
				training.setString(L"Думаю нам стоит вернуться к Тианнию и доложить о наших успехах.");
			else if (training_part == 6)
				training_part = 7;

			if (training_part == 7 && passwordlvl0 != L"2004")
				training.setString(L"Тианний доволен вашими успехами, и мы тоже. Он предложил вам \nпопробовать решить загадку с роялем. Возможно, стоит попробовать.");
			else if (training_part == 7)
				training_part = 8;
			if (training_part == 8 && trainingSpeach != 2 && trainingSpeach != 3)
				training.setString(L"Вам удалось решить загадку! Возможно следует обсудить это с Тианнием?");
			else if (training_part == 8)
				training_part = 9;

			if (training_part == 9)
				training.setString(L"Поздравляем вы прошли обучение!\n Если желаете можете отправится на встречу неизведанному!");
			training.setPosition(window.getView().getCenter().x - training.getLocalBounds().width / 2, window.getView().getCenter().y - training.getLocalBounds().height / 2 - 270);
			window.draw(training);
		}

		//Концовки игры 
		if (goodending || badending) //Если действия необходимые для этой концовки выполнены
		{
			//Если получена хорошая концовка
			if (goodending)
			{
				//Вызывана функция отображающая адаптивные картинки 
				if (alert(window, "images/END1.png", &inPause, view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)))
					continue;
				else
					goodending = 0;
				
			}
			//Если полученна плохая концовка
			else
			{
				//Вызывана функция отображающая адаптивные картинки
				if (alert(window, "images/END2.png", &inPause, view.getCenter().x - (view.getSize().x / 2), view.getCenter().y - (view.getSize().y / 2)))
					continue;
				else
					badending = 0;
			}
			window.clear(); //очистка экрана
			inMenu = 1; //указывает, что надо вернуться в меню
			gameWasStarted = 0; //указывает, что игра не начиналась
			return true; //возвращаем true, чтобы выйти в главное меню
		}
		window.display();
	}

}
void gameRun(RenderWindow& window)
{
	if (alive(window))
		gameRun(window);
}