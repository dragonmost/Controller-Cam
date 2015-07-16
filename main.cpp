#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#define STICKX 52
#define STICKY 67
#define CSTICKX 185
#define CSTICKY 132

using namespace std;
using namespace sf;

int main()
{
	FreeConsole();
	sf::RenderWindow window(sf::VideoMode(300, 250), "Controller Cam");
	
	Texture controllerText;
	Sprite Controller;
	Texture stickText;
	Sprite Stick;
	Texture cstickText;
	Sprite CStick;
	CircleShape Button[6];		//A, B, X, Y, Z, Start;
	CircleShape Trigger[2];	//L, R;
	RectangleShape DPad[4];		//Up, Right, Down, Left;

	controllerText.loadFromFile("Texture\\CONTROLLER.png");
	Controller.setTexture(controllerText);
	Controller.setScale(0.3, 0.3);
	Controller.setPosition(0, -30);

	stickText.loadFromFile("Texture\\STICK.png");
	Stick.setTexture(stickText);
	Stick.setScale(0.3, 0.3);
	Stick.setPosition(STICKX, STICKY);

	cstickText.loadFromFile("Texture\\C-STICK.png");
	CStick.setTexture(cstickText);
	CStick.setScale(0.3, 0.3);
	CStick.setPosition(CSTICKX, CSTICKY);


	Button[0].setRadius(17);
	Button[0].setPosition(221, 67);
	Button[1].setRadius(11);
	Button[1].setPosition(195, 88);
	Button[2].setRadius(10);
	Button[2].setPosition(260, 70);
	Button[3].setRadius(10);
	Button[3].setPosition(220, 43);
	Button[4].setRadius(10);
	Button[4].setPosition(240, 20);
	Button[5].setRadius(7);
	Button[5].setPosition(146, 78);
	
	Trigger[0].setRadius(7);
	Trigger[0].setScale(3, 1);
	Trigger[0].setRotation(-20);
	Trigger[0].setPosition(38, 30);
	Trigger[1].setRadius(7);
	Trigger[1].setScale(3, 1);
	Trigger[1].setRotation(20);
	Trigger[1].setPosition(230, 18);

	DPad[0].setSize(Vector2f(11, 15));
	DPad[0].setPosition(102, 125);
	DPad[1].setSize(Vector2f(15, 11));
	DPad[1].setPosition(111, 139);
	DPad[2].setSize(Vector2f(11, 15));
	DPad[2].setPosition(102, 148);
	DPad[3].setSize(Vector2f(15, 11));
	DPad[3].setPosition(90, 139);

	while (window.isOpen())
	{
		Trigger[0].setFillColor(Color::Transparent);
		Trigger[1].setFillColor(Color::Transparent);

		for (int i = 0; i < 6; i++)
			Button[i].setFillColor(Color::Transparent);

		for (int i = 0; i < 4; i++)
			DPad[i].setFillColor(Color::Transparent);


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Joystick JS;
		if (JS.isButtonPressed(2, 0))
		{
			Button[2].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 1))
		{
			Button[0].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 2))
		{
			Button[1].setFillColor(Color::Blue);
		}
		if (JS.isButtonPressed(2, 3))
		{
			Button[3].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 4))
		{
			Trigger[0].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 5))
		{
			Trigger[1].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 7))
		{
			Button[4].setFillColor(Color::Blue);
		}
		if (JS.isButtonPressed(2, 9))
		{
			Button[5].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 12))
		{
			DPad[0].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 13))
		{
			DPad[1].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 14))
		{
			DPad[2].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(2, 15))
		{
			DPad[3].setFillColor(Color::Red);
		}

		Stick.setPosition(STICKX + JS.getAxisPosition(2, JS.X) / 10, STICKY + JS.getAxisPosition(2, JS.Y)/ 10);
		CStick.setPosition(CSTICKX + JS.getAxisPosition(2, JS.R) / 10, CSTICKY + JS.getAxisPosition(2, JS.Z) / 10);


		window.clear();
		window.draw(Controller);
		window.draw(Stick);
		window.draw(CStick);

		window.draw(Trigger[0]);
		window.draw(Trigger[1]);

		for (int i = 0; i < 6; i++)
			window.draw(Button[i]);

		for (int i = 0; i < 4; i++)
			window.draw(DPad[i]);

		window.display();
	}

	return 0;
}