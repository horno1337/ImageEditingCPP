#pragma once
#include "utilities.hpp"
class ViewingClass
{
public:
	void loop();
	string path;
	Image* image;
	ViewingClass(string, Image*);
};

