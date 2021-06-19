#pragma once
#include "utilities.hpp"
#include "ViewingClass.h"
#include "FilePicker.h"
#include "SaveAsPicker.h"
class Editor
{
public:
	Editor(RenderWindow*,Font*,string);
	RenderWindow* window;
	string path;
	Font* font;

	void loop();

	Image image;

	void blend(string);
};

