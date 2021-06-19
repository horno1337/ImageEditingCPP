#include "ViewingClass.h"

ViewingClass::ViewingClass(string path, Image* image)
{
	this->path = path;
	this->image = image;
}

void ViewingClass::loop()
{
	RenderWindow window;
	window.create(
		VideoMode(image->getSize().x, image->getSize().y), "Preview: " + path, DefaultWindowMode
	);

	Texture texture;
	texture.loadFromImage(*image);
	Sprite sprite(texture);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window.close();
			}
		}
		window.draw(sprite);
		window.display();
		window.clear();
	}
}