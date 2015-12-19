#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include "DPad.h"
#include "Button.h"
#include "Controller.h"
#include "Config.h"

#define STICKX 52
#define STICKY 67
#define CSTICKX 185
#define CSTICKY 132

using namespace std;
using namespace sf;

void LoadSettings(ifstream &file, int &JSID, string& ControllerName, int(&Button)[12]);
void DefaultSettings();

int main()
{
	FreeConsole();
	sf::RenderWindow window(sf::VideoMode(300, 250), "Controller Cam");

	Controller* controller;
	Joystick JS;
	string ControllerName;
	Texture LStickText;
	Sprite LStick;
	Texture RStickText;
	Sprite RStick;
	//CircleShape Button[6];		//A, B, X, Y, Z, Start;
	//CircleShape Trigger[2];		//L, R;
	RectangleShape DPad[4];		//Up, Right, Down, Left;
	int JSID = 0;
	int ButtonID[12];	// A, B, X, Y, L, R, Z, Start, Up, Right, Left, Right;
	Font font;
	Text warning;

	Config* config;

	ifstream SetupFile;
	SetupFile.open("setup.txt");
	if (!SetupFile.is_open())
	{
		DefaultSettings();
		SetupFile.open("setup.txt");
	}
	LoadSettings(SetupFile, JSID, ControllerName, ButtonID);
	SetupFile.close();

	controller = new Controller(ControllerName);

	if (!JS.isConnected(JSID))
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
		if (!font.loadFromFile("D:\\Windows\\Fonts\\Arial.ttf"));

		warning.setFont(font);
		warning.setString("Couldn't find the controller: " + to_string(JSID));
		warning.setCharacterSize(20);
		warning.setPosition(10, 220);
	}

	if (ControllerName == "GAMECUBE")
	{
		LStickText.loadFromFile("Texture\\STICK.png");
		LStick.setTexture(LStickText);
		LStick.setScale(0.3, 0.3);
		LStick.setPosition(STICKX, STICKY);

		RStickText.loadFromFile("Texture\\C-STICK.png");
		RStick.setTexture(RStickText);
		RStick.setScale(0.3, 0.3);
		RStick.setPosition(CSTICKX, CSTICKY);
	}
	else if (ControllerName == "N64")
	{
		LStickText.loadFromFile("Texture\\N64_STICK.png");
		LStick.setTexture(LStickText);
		LStick.setScale(0.3, 0.3);
		LStick.setPosition(STICKX, STICKY);
	}
	else if (ControllerName == "Playstation")
	{
	}

	while (window.isOpen())
	{
		window.clear();
		window.draw(controller->getControllerSprite());

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				delete config;
				delete controller;
				window.close();
			}

			if (event.type == Event::MouseButtonPressed && Mouse::isButtonPressed(Mouse::Right))
			{
				config = new Config(controller);
			}
		}

		

		for (int i = 0; i < controller->getNbButton() -1; i++)
		{
			if (JS.isButtonPressed(JSID, ButtonID[i]))
				window.draw(controller->getButton(i));
		}

		LStick.setPosition(STICKX + JS.getAxisPosition(2, JS.X) / 10, STICKY + JS.getAxisPosition(2, JS.Y)/ 10);
		RStick.setPosition(CSTICKX + JS.getAxisPosition(2, JS.R) / 10, CSTICKY + JS.getAxisPosition(2, JS.Z) / 10);


		window.draw(LStick);
		window.draw(RStick);

		window.draw(warning);
		window.display();
	}

	return 0;
}

void LoadSettings(ifstream &file, int &JSID, string& ControllerName, int(&Button)[12])
{
	string line;
	int i = 0;
	while ((getline(file, line) || i < 10) && line != "Setting")
	{
		i++;
	}

	getline(file, line);	//Joystick ID
	JSID = stol(line.substr(13));
	getline(file, line);
	ControllerName = line.substr(16);
	getline(file, line);	//A
	Button[0] = stol(line.substr(2)) - 1;
	getline(file, line);	//B
	Button[1] = stol(line.substr(2)) - 1;
	getline(file, line);	//X
	Button[2] = stol(line.substr(2)) - 1;
	getline(file, line);	//Y
	Button[3] = stol(line.substr(2)) - 1;
	getline(file, line);	//Z
	Button[4] = stol(line.substr(2)) - 1;
	getline(file, line);	//Start
	Button[5] = stol(line.substr(6)) - 1;
	getline(file, line);	//L
	Button[6] = stol(line.substr(2)) - 1;
	getline(file, line);	//R
	Button[7] = stol(line.substr(2)) - 1;
	getline(file, line);	//Up
	Button[8] = stol(line.substr(3)) - 1;
	getline(file, line);	//Right
	Button[9] = stol(line.substr(6)) - 1;
	getline(file, line);	//Down
	Button[10] = stol(line.substr(5)) - 1;
	getline(file, line);	//Left
	Button[11] = stol(line.substr(5)) - 1;
}

void DefaultSettings()
{
	//Default text
	ofstream file;
	file.open("setup.txt");

	file <<
		"################################################################################################\n" <<
		"## Please enter the Id of the controller you want to monitor (usualy between 0-9),\n" <<
		"## the controller name (supports SNES and GAMECUBE),\n" <<
		"## Also the Id for each button on the controller (between 1-16).\n" <<
		"## You can find the button values in Control Panel/Hardware and Sound/Devices and Printers.\n" <<
		"## Right Click Game Controllers Parameters/Properties. You can then see wich number light up.\n" <<
		"## If the setup file is broken try deleting it and starting up the .exe again.\n" <<
		"################################################################################################\n\n" <<
		"Setting\n" <<
		"Joystrick ID: 2\n" <<
		"ControllerName: GAMECUBE\n"
		"A: 2\n" <<
		"B: 3\n" <<
		"X: 1\n" <<
		"Y: 4\n" <<
		"Z: 8\n" <<
		"Start: 10\n" <<
		"L: 5\n" <<
		"R: 6\n" <<
		"Up: 13\n" <<
		"Right: 14\n" <<
		"Down: 15\n" <<
		"Left: 16\n";

	file.close();
}