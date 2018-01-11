#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <array>
#include "Point.h"

namespace config 
{
	const int width = 1280;
	const int height = 960;
	const int tileSize = 32;
	const std::string title = "Shooter Game";
	const bool fullscreen = false;

	const std::array<std::string, 3> levels{
		"../content/level1.json",
		"../content/level2.json",
		"../content/level3.json"
	};

	const Point WINDOW_CENTER { height / 2, width / 2 };
}
#endif CONFIG_H