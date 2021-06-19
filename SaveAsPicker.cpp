#include "SaveAsPicker.h"

SaveAsPicker::SaveAsPicker(string path, Font* font)
{
	this->path = path;
	this->font = font;
}

string SaveAsPicker::loop()
{
	window.create(VideoMode(640, 50), "Enter a full file path", DefaultWindowMode);
	Text enteredText;
	string enteredString = path;

	enteredText.setPosition(0, 0);
	enteredText.setString(path);
	enteredText.setFont(*font);
	enteredText.setCharacterSize(15);

	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::TextEntered)
			{
				if (e.text.unicode >= 32 && e.text.unicode <= 126)
				{
					enteredString += static_cast<char>(e.text.unicode);
					String sfstring(enteredString);
					enteredText.setString(sfstring);
				}
				else if (e.text.unicode == 8)
				{
					enteredString = enteredString.substr(0, enteredString.size()-1);
					String sfstring(enteredString);
					enteredText.setString(sfstring);
				}
				else if (e.text.unicode == 13)
				{
					return enteredString;
				}
			}
		}
		window.draw(enteredText);
		window.display();
		window.clear();
	}
	return "";

}