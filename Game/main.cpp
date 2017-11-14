#include <iostream>
#include "Engine.h"
#include "AudioManager.h"
//#include "vld.h"
//#include "AudioManager.h"
#include "TMXManager.h"
#include "RenderManager.h"

#undef main
int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	AudioManager::Instance().InitMusicPlayer();
	AudioManager::Instance().LoadBGM("pokemon");
	AudioManager::Instance().PlayBGM();

	TMXManager::Instance().Init("../content/map/tilemapje2.tmx");
	TMXManager::Instance().Render();
	std::cin.get();

	return 0;
}
