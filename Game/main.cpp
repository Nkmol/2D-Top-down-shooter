#include <iostream>
#include "../Engine/Engine.h"
#include "../Engine/RenderManager.h"
//#include "AudioManager.h"

#undef main
int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	auto engine = new Engine::MainManager();
	
	/*AudioManager::Instance()->LoadBGM("pokemon");
	AudioManager::Instance()->PlayBGM(); */

//    RenderManager::GetRenderManager();
//
//        RenderManager::GetRenderManager()->Clear();
//        RenderManager::GetRenderManager()->Flip();

	std::cout << engine->Message;

	std::cin.get();

	return 0;
}