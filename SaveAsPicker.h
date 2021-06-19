#pragma once
#include "utilities.hpp"
class SaveAsPicker
{
public:
	SaveAsPicker(string, Font*);
	RenderWindow window;
	string path;
	string loop();
	Font* font;
};

