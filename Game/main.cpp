#include <iostream>
#include "Engine.h"
//#include "AudioManager.h"
#include "TMXManager.h"
#include "RenderManager.h"

#undef main
int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	auto engine = new Engine::MainManager();
	
	/*AudioManager::Instance()->LoadBGM("pokemon");
	AudioManager::Instance()->PlayBGM(); */
	std::cout << engine->Message;

	TMXManager::Instance().Init("../content/map/tilemapje.tmx");
	TMXManager::Instance().Render();
	std::cin.get();

	return 0;
}