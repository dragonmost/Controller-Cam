using namespace std;
using namespace sf;

class Config
{
	Controller* controller;
public:
	Config(Controller* _controller)
	{
		controller = _controller;
		Start();
	}

private:
	void Start()
	{
		RenderWindow window(VideoMode(300, 250), "Configuration");
		int Selected = -1;

		while (window.isOpen())
		{
			window.clear();
			window.draw(controller->getControllerSprite());

			for (int i = 0; i < controller->getNbButton(); i++)
			{
				CircleShape button = controller->getButton(i);
				if (i == Selected)
					button.setFillColor(Color::Cyan);
				window.draw(button);
			}
			
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.display();
		}
	}

};