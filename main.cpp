#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>

#define STICKX 52
#define STICKY 67
#define CSTICKX 185
#define CSTICKY 132

using namespace std;
using namespace sf;

void LoadSettings(ifstream &file, int &JSID, int(&Button)[12]);
void DefaultSettings();

int main()
{
	FreeConsole();
	sf::RenderWindow window(sf::VideoMode(300, 250), "Controller Cam");
	
	Joystick JS;
	Texture controllerText;
	Sprite Controller;
	Texture stickText;
	Sprite Stick;
	Texture cstickText;
	Sprite CStick;
	CircleShape Button[6];		//A, B, X, Y, Z, Start;
	CircleShape Trigger[2];		//L, R;
	RectangleShape DPad[4];		//Up, Right, Down, Left;
	int JSID = 0;
	int ButtonID[12];	// A, B, X, Y, L, R, Z, Start, Up, Right, Left, Right;
	Font font;
	Text warning;

	ifstream SetupFile;
	SetupFile.open("setup.txt");
	if (!SetupFile.is_open())
	{
		DefaultSettings();
		SetupFile.open("setup.txt");
	}
	LoadSettings(SetupFile, JSID, ButtonID);
	SetupFile.close();

	if (!JS.isConnected(JSID))
	{
		if (!font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"))
		if (!font.loadFromFile("D:\\Windows\\Fonts\\Arial.ttf"));

		warning.setFont(font);
		warning.setString("Couldn't find the controller: " + to_string(JSID));
		warning.setCharacterSize(20);
		warning.setPosition(10, 220);
	}

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

		if (JS.isButtonPressed(JSID, ButtonID[2]))
		{
			Button[2].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[0]))
		{
			Button[0].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[1]))
		{
			Button[1].setFillColor(Color::Blue);
		}
		if (JS.isButtonPressed(JSID, ButtonID[3]))
		{
			Button[3].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[6]))
		{
			Trigger[0].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[7]))
		{
			Trigger[1].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[4]))
		{
			Button[4].setFillColor(Color::Blue);
		}
		if (JS.isButtonPressed(JSID, ButtonID[5]))
		{
			Button[5].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[8]))
		{
			DPad[0].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[9]))
		{
			DPad[1].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[10]))
		{
			DPad[2].setFillColor(Color::Red);
		}
		if (JS.isButtonPressed(JSID, ButtonID[11]))
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
		window.draw(warning);
		window.display();
	}

	return 0;
}

void LoadSettings(ifstream &file, int &JSID, int(&Button)[12])
{
	string line;
	int i = 0;
	while ((getline(file, line) || i < 10) && line != "Setting")
	{
		i++;
	}

	getline(file, line);	//Joystick ID
	JSID = stol(line.substr(13));
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
		"## Please enter the Id of the controller you want to monitor (usualy between 0-9)\n" <<
		"## Also the Id for each button on the controller (between 1-16).\n" <<
		"## You can find the button values in Control Panel/Hardware and Sound/Devices and Printers.\n" <<
		"## Right Click Game Controllers Parameters/Properties. You can then see wich number light up.\n" <<
		"## If the setup file is broken try deleting it and starting up the .exe again.\n" <<
		"################################################################################################\n\n" <<
		"Setting\n" <<
		"Joystrick ID: 2\n" <<
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