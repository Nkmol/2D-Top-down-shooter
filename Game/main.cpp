#include <iostream>
#include "Engine.h"
//#include "AudioManager.h"

#undef main
int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	auto engine = new Engine::MainManager();
	//werkt nog niet vanwege link problemen
	//AudioManager::Instance()->LoadBGM("pokemon");
	//AudioManager::Instance()->PlayBGM();
	std::cout << engine->Message;


	std::cin.get();

	return 0;
}