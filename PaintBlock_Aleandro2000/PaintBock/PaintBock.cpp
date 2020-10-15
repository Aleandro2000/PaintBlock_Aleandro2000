//Realized by Aleandro2000
#include "pch.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
int main()
{
	struct
	{
		unsigned short x, y;
	}object;
	unsigned short map[41][41];
	unsigned long long score = 0;
	RenderWindow window(VideoMode(656, 656), "");
	Texture t1, t2, t3, t4;
	Font font;
	Music music;
	if (!t1.loadFromFile("Resources/white.png"))
		return EXIT_FAILURE;
	if (!t2.loadFromFile("Resources/red.png"))
		return EXIT_FAILURE;
	if (!t3.loadFromFile("Resources/green.png"))
		return EXIT_FAILURE;
	if (!t4.loadFromFile("Resources/blue.png"))
		return EXIT_FAILURE;
	if (!font.loadFromFile("Fonts/Calimbri.ttf"))
		return EXIT_FAILURE;
	if (!music.openFromFile("Sounds/soundtrack.ogg"))
		return EXIT_FAILURE;
	Sprite s1(t1), s2(t2), s3(t3), s4(t4);
	Vector2i point;
	Text text;
	text.setFont(font);
	text.setString("Game Over!\n\tPress ENTER to retry!");
	text.setPosition(0, 0);
	text.move(328.f, 328.f);
	text.setFillColor(Color::Black);
	bool open = true;
	srand(time(0));
	for (unsigned short j = 1; j < 41; ++j)
		map[0][j] = 0;
	for (unsigned short i = 1; i < 41; ++i)
		for (unsigned short j = 0; j < 41; ++j)
			map[i][j] = 0;
	do
	{
		score += 100;
		map[rand() % 41][rand() % 41] = 3;
	} while (map[0][0] == 3);
	map[0][0] = 1;
	object.x = object.y = 0;
	music.setLoop(true);
	music.play();
	while (window.isOpen())
	{
		Event event;
		window.setTitle("PaintBlock__________Score: "+std::to_string(score));
		while (window.pollEvent(event))
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				switch (event.key.code)
				{
				case Keyboard::Enter:
					if (!open)
					{
						for (unsigned short j = 1; j < 41; ++j)
							map[0][j] = 0;
						for (unsigned short i = 1; i < 41; ++i)
							for (unsigned short j = 0; j < 41; ++j)
								map[i][j] = 0;
						do
						{
							score += 100;
							map[rand() % 41][rand() % 41] = 3;
						} while (map[0][0] == 3);
						map[0][0] = 1;
						score = object.x = object.y = 0;
						open = true;
						music.play();
					}
					break;
				case Keyboard::Up:
					if (object.y && open)
					{
						map[object.x][object.y] = 0;
						--object.y;
						map[rand() % 41][rand() % 41] = 2;
						if (map[object.x][object.y] == 2)
							open = false;
						else if (map[object.x][object.y] == 3)
						{
							score += 100;
							map[object.x][object.y] = 1;
							map[rand() % 41][rand() % 41] = 3;
						}
						else
							map[object.x][object.y] = 1;
					}
					break;
				case Keyboard::Down:
					if (object.y < 40 && open)
					{
						map[object.x][object.y] = 0;
						++object.y;
						map[rand() % 41][rand() % 41] = 2;
						if (map[object.x][object.y] == 2)
							open = false;
						else if (map[object.x][object.y] == 3)
						{
							score += 100;
							map[object.x][object.y] = 1;
							map[rand() % 41][rand() % 41] = 3;
						}
						else
							map[object.x][object.y] = 1;
					}
					break;
				case Keyboard::Left:
					if (object.x && open)
					{
						map[object.x][object.y] = 0;
						--object.x;
						map[rand() % 41][rand() % 41] = 2;
						if (map[object.x][object.y] == 2)
							open = false;
						else if (map[object.x][object.y] == 3)
						{
							score += 100;
							map[object.x][object.y] = 1;
							map[rand() % 41][rand() % 41] = 3;
						}
						else
							map[object.x][object.y] = 1;
					}
					break;
				case Keyboard::Right:
					if (object.x < 40 && open)
					{
						map[object.x][object.y] = 0;
						++object.x;
						map[rand() % 41][rand() % 41] = 2;
						if (map[object.x][object.y] == 2)
							open = false;
						else if (map[object.x][object.y] == 3)
						{
							score += 100;
							map[object.x][object.y] = 1;
							map[rand() % 41][rand() % 41] = 3;
						}
						else
							map[object.x][object.y] = 1;
					}
					break;
				default:
					break;
				}
				break;
			default:
				break;
			}
		window.clear();
		for (unsigned short i = 0; i < 41; ++i)
			for (unsigned short j = 0; j < 41; ++j)
				switch (map[i][j])
				{
				case 0:
					s1.setPosition(i*16.f, j*16.f);
					s1.move(0.f, 0.f);
					window.draw(s1);
					break;
				case 1:
					s3.setPosition(i*16.f, j*16.f);
					s3.move(0.f, 0.f);
					window.draw(s3);
					break;
				case 2:
					s2.setPosition(i*16.f, j*16.f);
					s2.move(0.f, 0.f);
					window.draw(s2);
					break;
				case 3:
					s4.setPosition(i*16.f, j*16.f);
					s4.move(0.f, 0.f);
					window.draw(s4);
					break;
				default:
					break;
				}
		if (!open)
			window.draw(text);
		window.display();
	}
	return EXIT_SUCCESS;
}