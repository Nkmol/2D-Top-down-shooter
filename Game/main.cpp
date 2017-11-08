#include <iostream>
#include "Engine.h"
//#include "AudioManager.h"

int main(int argc, char *argv[]) {
	std::cout << "Hello, World!" << std::endl;

	auto engine = new Engine::MainManager();
	//werkt nog niet vanwege link problemen
	//AudioManager::instance()->loadBGM("pokemon");
	//AudioManager::instance()->playBGM();
	std::cout << engine->Message;


	std::cin.get();

	return 0;
}