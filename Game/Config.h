#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <array>
namespace config 
{
	const int width = 1920;
	const int height = 1080;
	const int tileSize = 32;
	const std::string title = "Shooter Game";
	const bool fullscreen = true;

	const std::array<std::string, 3> levels{
		"../content/level1.json",
		"../content/level2.json",
		"../content/level3.json"
	};
}
#endif CONFIG_H