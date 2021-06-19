#pragma once
#include"utilities.hpp"
class FilePicker
{
public:
	FilePicker(string, Font*);
	string directory;
	RenderWindow window;

	void populateVector();
	vector<std::filesystem::directory_entry> current;
	Font* font;

	string loop();
};

