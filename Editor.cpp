#include "Editor.h"

Editor::Editor(RenderWindow* renderWindow, Font* font, string path)
{
	this->window = renderWindow;
	this->path = path;
	this->font = font;
	if(!image.loadFromFile(this->path))
	{
		throw std::runtime_error("File not found");
	}
	window->setTitle("Editing: " + path);
}

void Editor::loop()
{
	const int btncnt = 5;
	string txt[btncnt] = { "shear", "blend", "view", "save", "save as" };

	Text buttons[btncnt];
	for (int i = 0; i < btncnt; i++)
	{
		buttons[i].setString(txt[i]);
		buttons[i].setCharacterSize(12);
		buttons[i].setFont(*font);
		buttons[i].setPosition(i * 40+1, 1);
		buttons[i].setFillColor(Color::White);
	}

	bool isPicking = false;
	Vector2f first;
	Vector2f second;

	Sprite sprite;

	Texture texture;
	texture.loadFromImage(image);
	while (window->isOpen())
	{
		Event e;
		while (window->pollEvent(e))
		{
			if (e.type == Event::Closed)
			{
				window->close();
			}
			else if (e.type == Event::MouseButtonPressed)
			{
				if (e.mouseButton.button == Mouse::Button::Right)
				{
					isPicking = false;
				}
				else if (e.mouseButton.button == Mouse::Button::Left)
				{
					first = Vector2f(Mouse::getPosition(*window));
				}
			}
			else if (e.type == Event::MouseButtonReleased)
			{
				if (isPicking)
				{
					second = Vector2f(Mouse::getPosition(*window));

					if (sprite.getGlobalBounds().contains(first) && sprite.getGlobalBounds().contains(second))
					{
						if (first.x > second.x) std::swap(first.x, second.x);
						if (first.y > second.y) std::swap(first.y, second.y);

						first -= sprite.getPosition();
						second -= sprite.getPosition();
						Vector2f size = second - first;
						size.x = abs(size.x);
						size.y = abs(size.y);
						Image sImage;
						sImage.create(size.x, size.y);
						sImage.copy(image, 0, 0, IntRect(Vector2i(first), Vector2i(size)));
						if(texture.loadFromImage(sImage))
							image = sImage;
					}
					isPicking = false;
				}
				else
				{
					for (int i = 0; i < btncnt; i++)
					{
						if (buttons[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window))))
						{
							switch (i)
							{
							case 0:
							{
								isPicking = true;
							}
							break;
							case 1:
							{
								FilePicker filePicker("C:/", font);
								filePicker.window.setTitle("Select file to blend with");
								string pathToBlend = filePicker.loop();
								if (pathToBlend != "")
								{
									blend(pathToBlend);
									texture.loadFromImage(image);
								}
							}
							break;
							case 2:
							{
								ViewingClass viewingClass(path, &image);
								viewingClass.loop();
							}
							break;
							case 3:
							{
								image.saveToFile(path);
							}
							break;
							case 4:
							{
								SaveAsPicker savepicker(path, font);
								string newpath = savepicker.loop();
								if (newpath != "")
									image.saveToFile(newpath);
							}
							break;
							}
						}
					}
			}
			}
		}

		sprite.setTexture(texture, true);
		sprite.setPosition(window->getSize().x/2-image.getSize().x/2,
			window->getSize().y/2-image.getSize().y/2);
		window->draw(sprite);
		for (int i = 0; i < btncnt; i++)
		{
			if (buttons[i].getGlobalBounds().contains(Vector2f(Mouse::getPosition(*window))))
			{
				buttons[i].setFillColor(Color::Cyan);
			}
			else
			{
				buttons[i].setFillColor(Color::White);
			}
			window->draw(buttons[i]);
		}
		window->display();
		window->clear(Color(30,30,30));
		
	}
}

void Editor::blend(string pathToBlend)
{
	Image toBlend;
	if (!toBlend.loadFromFile(pathToBlend))
	{
		throw std::runtime_error("File not found");
	}
	
	int horizontal = std::min(toBlend.getSize().x, image.getSize().x);
	int vertical = std::min(toBlend.getSize().y, image.getSize().y);
	for (int i = 0; i < horizontal; i++)
	{
		for (int j = 0; j < vertical; j++)
		{
			image.setPixel(i, j,
				image.getPixel(i, j) * toBlend.getPixel(i, j)
			);
		}
	}
}