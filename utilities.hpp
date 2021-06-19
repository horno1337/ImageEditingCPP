#pragma once
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <conio.h>
#include <filesystem>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using std::string, std::vector;
using namespace sf;

unsigned const int DefaultWindowMode = sf::Style::Default ^ sf::Style::Resize;

inline vector<string> split(const string& s, char delim)
{
    vector<string> result;
    std::stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

inline int strpos(string toSearch, char character, int which)
{
    string read;  
    for (int i = 1; i < which + 1; i++)
    {
        std::size_t found = toSearch.find(character);
        read += toSearch.substr(0, found + 1);
        toSearch.erase(0, found + 1);
        if (i == which)
        {
            return read.size();
        }
    }
    return -1;
}