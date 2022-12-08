#include "Menu.h"

int x = GetSystemMetrics(SM_CXSCREEN); //Разрешение экрана по X
int y = GetSystemMetrics(SM_CYSCREEN); //Разрешение экрана по Y
int MenuMode;
bool inMenu = true;

void adaptPicture(Sprite* sprite, RenderWindow& window)
{
    float xsize = ((float)window.getView().getSize().x / (float)sprite->getTexture()->getSize().x);
    float ysize = ((float)window.getView().getSize().y / (float)sprite->getTexture()->getSize().y);
    (*sprite).setScale(xsize, ysize);
    FloatRect fRect = (*sprite).getGlobalBounds();
    float px = (window.getView().getSize().x - sprite->getGlobalBounds().width) / 2;
    float py = (window.getView().getSize().y - sprite->getGlobalBounds().height) / 2;
    (*sprite).setPosition(px, py);
}
void menu(RenderWindow& window)
{
    Music menuMusic;
    menuMusic.openFromFile("sounds/mainmenu.ogg");
    menuMusic.setVolume(1);
    menuMusic.play();
    menuMusic.setLoop(true);
    bool inAbout = 0;
    bool isClick = 0;
    float camx = view.getCenter().x - (view.getSize().x / 2);
    float camy = view.getCenter().y - (view.getSize().y / 2);
    Vector2f centerPos = Vector2f(window.getSize().x / 2, window.getSize().y / 2);
    Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuBackground, aboutPage, okey, logo;
    logo.loadFromFile("images/Logo.png");
    menuBackground.loadFromFile("images/Background1.png");
    menuTexture1.loadFromFile("images/NEWGAMETXT.png");
    menuTexture2.loadFromFile("images/CONTINUEGAMETXT.png");
    menuTexture3.loadFromFile("images/EXITGAMETXT.png");
    menuTexture4.loadFromFile("images/ABOUTGAMETXT.png");
    aboutPage.loadFromFile("images/AboutScreen.png");
    okey.loadFromFile("images/OKEYTEXT.png");
    Sprite menu(menuBackground), menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), aboutPageS(aboutPage), okeyS(okey), logos(logo);
    adaptPicture(&menu, window);
    int menuButtonNum = 0;
    menu1.setPosition(window.getView().getCenter().x - menu1.getLocalBounds().width / 2, window.getView().getCenter().y - menu1.getLocalBounds().height / 2 - 150);
    menu2.setPosition(window.getView().getCenter().x - menu2.getLocalBounds().width / 2, window.getView().getCenter().y - menu2.getLocalBounds().height / 2);
    menu4.setPosition(window.getView().getCenter().x - menu4.getLocalBounds().width / 2, window.getView().getCenter().y - menu4.getLocalBounds().height / 2 + 150);
    menu3.setPosition(window.getView().getCenter().x - menu3.getLocalBounds().width / 2, window.getView().getCenter().y - menu3.getLocalBounds().height / 2 + 300);
    logos.setPosition(window.getView().getCenter().x - logos.getLocalBounds().width / 2, window.getView().getCenter().y - logos.getLocalBounds().height / 2 - 350);


    while (inMenu) {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menu3.setColor(Color::White);
        menu4.setColor(Color::White);
        okeyS.setColor(Color::White);
        if (!Mouse::isButtonPressed(Mouse::Left))
        {
            isClick = 0;
        }

        if (isClick == 0) {
            if (IntRect(centerPos.x - menu1.getGlobalBounds().width / 2, centerPos.y - menu1.getGlobalBounds().height / 2 - 150, 600, 100).contains(Mouse::getPosition(window))) { menu1.setColor(Color(128, 128, 128)); menuButtonNum = 1; }
            if (IntRect(centerPos.x - menu2.getGlobalBounds().width / 2, centerPos.y - menu2.getGlobalBounds().height / 2, 600, 100).contains(Mouse::getPosition(window))) { menu2.setColor(Color(128, 128, 128)); menuButtonNum = 2; }
            if (IntRect(centerPos.x - menu3.getGlobalBounds().width / 2, centerPos.y - menu3.getGlobalBounds().height / 2 + 300, 600, 100).contains(Mouse::getPosition(window))) { menu3.setColor(Color(128, 128, 128)); menuButtonNum = 3; }
            if (IntRect(centerPos.x - menu4.getGlobalBounds().width / 2, centerPos.y - menu4.getGlobalBounds().height / 2 + 150, 600, 100).contains(Mouse::getPosition(window))) { menu4.setColor(Color(128, 128, 128)); menuButtonNum = 4; }
        }
        if (Mouse::isButtonPressed(Mouse::Left) || inAbout == 1)
        {
            if (menuButtonNum == 4 || inAbout == 1)
            {
                aboutPageS.setPosition(window.getView().getCenter().x - aboutPageS.getLocalBounds().width / 2, window.getView().getCenter().y - aboutPageS.getLocalBounds().height / 2);
                okeyS.setPosition(window.getView().getCenter().x - okeyS.getLocalBounds().width / 2, window.getView().getCenter().y - okeyS.getLocalBounds().height + 700 / 2);
                if (IntRect(centerPos.x - okeyS.getGlobalBounds().width / 2, centerPos.y - okeyS.getGlobalBounds().height + 700 / 2, 300, 150).contains(Mouse::getPosition(window))) {
                    okeyS.setColor(Color(128, 128, 128));
                    if (Mouse::isButtonPressed(Mouse::Left))
                    {
                        isClick = 1;
                        inAbout = 0;
                        continue;
                    }
                }
                window.draw(aboutPageS);
                window.draw(okeyS);
                window.display();
                inAbout = 1;
                continue;
            }
        }

        if (Mouse::isButtonPressed(Mouse::Left) && isClick == 0)
        {
            if (menuButtonNum == 1) {
                inMenu = false; MenuMode = 0;
            }
            if (menuButtonNum == 2)
            {
                inMenu = false;
                MenuMode = 1;
            }
            if (menuButtonNum == 3)
            {
                window.close();
                inMenu = false;
                MenuMode = 2;
            }
        }
        window.draw(menu);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);
        window.draw(menu4);
        window.draw(logos);
        window.display();
    }

}


