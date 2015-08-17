class Button
{
	sf::CircleShape shape;

public:
	void setButton(int _X, int _Y, int _Rad, Color _Color)
	{
		shape.setPosition(_X, _Y);
		shape.setRadius(_Rad);
		shape.setFillColor(_Color);
	}

	void elipse(float _ScaleX, float _ScaleY, float _Rot)
	{
		shape.setScale(_ScaleX, _ScaleY);
		shape.setRotation(_Rot);
	}

	sf::CircleShape getShape()
	{
		return shape;
	}

};