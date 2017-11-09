#include <iostream>
#include "Engine.h"
#include "AudioManager.h"
#include "vld.h"

#undef main
int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	AudioManager::Instance().InitMusicPlayer();
	AudioManager::Instance().LoadBGM("pokemon");
	AudioManager::Instance().PlayBGM();


	std::cin.get();

	return 0;
}