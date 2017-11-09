#include <iostream>
#include "../Engine/Engine.h"
#include "../Engine/RenderManager.h"
#include "../Engine/moveableobject.h"
//#include "AudioManager.h"

#undef main
int main(int argc, char* argv[]) {
	std::cout << "Hello, World!" << std::endl;

	auto engine = new Engine::MainManager();
	
	/*AudioManager::Instance()->LoadBGM("pokemon");
	AudioManager::Instance()->PlayBGM(); */

    RenderManager::GetRenderManager();

    while(true) {
        SDL_PumpEvents();
        MoveableObject moveableObject = MoveableObject("content/soldier.png", 50, 50, 1);
        RenderManager::GetRenderManager()->Clear();
        moveableObject.draw(50,50,100);
        RenderManager::GetRenderManager()->Flip();
    }
	std::cout << engine->Message;

	std::cin.get();

	return 0;
}