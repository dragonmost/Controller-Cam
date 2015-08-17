using namespace sf;

class DPad
{
	RectangleShape shape;

public:
	DPad()
	{}

	void setButton(int _X, int _Y, int _XSize, int _YSize)
	{
		shape.setPosition(_X, _Y);
		shape.setSize(Vector2f(_XSize, _YSize));
		shape.setFillColor(Color::Red);
	}

	RectangleShape getShape()
	{ return shape; }
};