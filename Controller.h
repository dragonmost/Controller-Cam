using namespace sf;
using namespace std;

class Controller
{
	string Name;
	int nbButton;
	DPad dPad[4];
	vector<Button> button;
	Texture controllerText;
	Sprite controller;

public:
	Controller()
	{}
	Controller(string ControllerName)
	{
		Name = ControllerName;
		setController(Name);
	}

	void setController(string ControllerName)
	{
		Name = ControllerName;

		controllerText.loadFromFile("Texture\\" + ControllerName + ".png");
		controller.setTexture(controllerText);
		controller.setScale(0.3, 0.3);
		controller.setPosition(0, -30);

		if (ControllerName == "SNES")
		{
			nbButton = 12;
			button.resize(nbButton);

			button[0].setButton(252, 128, 11, Color::Red);	//A
			button[1].setButton(224, 150, 11, Color::Red);	//B
			button[2].setButton(224, 107, 11, Color::Red);	//X
			button[3].setButton(196, 129, 11, Color::Red);	//Y

			button[4].setButton(115, 150, 3.5, Color::Red);	//Select
			button[4].elipse(4, 1.5, -34);
			button[5].setButton(146, 150, 3.5, Color::Red);	//Start
			button[5].elipse(4, 1.5, -34);

			button[6].setButton(45, 75, 7, Color::Red);		//L
			button[6].elipse(4, 1, -5);
			button[7].setButton(207, 73, 7, Color::Red);	//R
			button[7].elipse(4, 1, 5);
		}
		else if (ControllerName == "N64")
		{
			nbButton = 14;
			button.resize(nbButton);
		}
		else if (ControllerName == "GAMECUBE")
		{
			nbButton = 12;
			button.resize(nbButton);
			/*
			dPad[0].setButton(102, 125, 11, 15);			//Up
			dPad[1].setButton(111, 139, 15, 11);			//Right
			dPad[2].setButton(102, 148, 11, 15);			//Down
			dPad[3].setButton(90, 139, 15, 11);				//Left
			*/

			button[0].setButton(221, 67, 17, Color::Red);	//A
			button[1].setButton(195, 88, 11, Color::Red);	//B
			button[2].setButton(260, 70, 10, Color::Red);	//X
			button[3].setButton(220, 43, 10, Color::Red);	//Y
			button[4].setButton(240, 20, 10, Color::Red);	//Z
			button[5].setButton(146, 78, 7, Color::Red);	//Start

			button[6].setButton(38, 30, 7, Color::Red);		//L
			button[6].elipse(3, 1, -20);
			button[7].setButton(230, 18, 7, Color::Red);	//R
			button[7].elipse(3, 1, 20);

			button[8].setButton(102, 125, 11, Color::Red);	//Up
			button[9].setButton(111, 139, 15, Color::Red);	//Right
			button[10].setButton(102, 148, 11, Color::Red);	//Down
			button[11].setButton(90, 139, 15, Color::Red);	//Left
		}
		else if (ControllerName == "PLAYSTATION")
		{
			nbButton = 16;
			button.resize(nbButton);
		}
		else if (ControllerName == "WIIUPRO")
		{
			nbButton = 14;
			button.resize(nbButton);
		}
		else
		{
		}
	}

	Sprite getControllerSprite()
	{
		return controller;
	}

	CircleShape getButton(int buttonID)
	{
		return button[buttonID].getShape();
	}

	int getNbButton()
	{
		return nbButton;
	}
};