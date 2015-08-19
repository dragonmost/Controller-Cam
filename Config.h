using namespace std;
using namespace sf;

class Config
{
public:
	Config()
	{
		Start();
	}

private:
	void Start()
	{
		RenderWindow window(VideoMode(300, 250), "Configuration");

		while (window.isOpen())
		{
			window.clear();
			window.display();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
		}
	}

};