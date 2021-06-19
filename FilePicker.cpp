#include "FilePicker.h"

FilePicker::FilePicker(string directory, Font* font)
{
	this->directory = directory;
	this->font = font;
	window.create(sf::VideoMode(640, 480), "", DefaultWindowMode);
}

void FilePicker::populateVector()
{
	current.clear();

	for (const auto& file : std::filesystem::directory_iterator(directory))
		current.push_back(file);
}

string FilePicker::loop()
{
	bool populateAgain = true;
	string result = "";
	vector<Text> files;
	int maxOnScreen = window.getSize().y/30 - 2;

	int firstOnScreen = 0;

	Text backText("[..]", *font);
	backText.setPosition(0, 0);
	backText.setFillColor(Color::Blue);

	while (true)
	{
		window.setTitle("Select a file: " + directory);
		if (populateAgain)
		{
			populateAgain = false;
			populateVector();
			firstOnScreen = 0;
		}
		files.clear();
		for (int i = firstOnScreen; i < std::min(firstOnScreen + maxOnScreen, (int)current.size()); i++)
		{
			vector<string> nameVector = split(current[i].path().string(), '/');
			string name = nameVector[nameVector.size() - 1];

			if (current[i].is_directory())
				name = name +"/";
			files.push_back(Text(name, *font));
			files[files.size()-1].setPosition(0, (i - firstOnScreen) * 34 +34);
		}
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::MouseWheelScrolled)
			{
				if (e.mouseWheelScroll.delta > 0)
				{
					if(firstOnScreen > 0)
						firstOnScreen--;
				}
				else
				{
					if(firstOnScreen+maxOnScreen < current.size())
						firstOnScreen++;
				}
			}
			else if (e.type == Event::MouseButtonReleased)
			{
				if (backText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
				{
					int count = std::count(directory.begin(), directory.end(), '/');
					if (count >= 2)
					{
						directory = directory.substr(0, strpos(directory, '/', count - 1));
						populateAgain = true;
						continue;
					}

				}
				for (auto& x : files)
				{
					if (x.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
					{
						string name = x.getString().toAnsiString();
						if (name[name.size() - 1] == '/')
						{
							directory += name;
							populateAgain = true;
							break;
						}
						else
						{
							window.close();
							return directory + name;
						}
					}
				}
			}
			else if (e.type == Event::Closed)
			{
				window.close();
				return "";
			}
		}
		for (auto& x: files)
		{
			if (x.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
			{
				x.setFillColor(Color::Red);
			}
			else
			{
				x.setFillColor(Color::White);
			}
			window.draw(x);
		}

		if (backText.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
		{
			backText.setFillColor(Color::Red);
		}
		else
		{
			backText.setFillColor(Color::Blue);
		}

		window.draw(backText);
		window.display();
		window.clear(Color(0x7b, 0x7b,0x8b));
	}
}