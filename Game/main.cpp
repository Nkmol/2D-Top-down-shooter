#include <iostream>
#include "RenderManager.h"
#include "InputManager.h"
#include "Player.h"
#include "AudioManager.h"

//#include "vld.h"
#include <memory>
#include <algorithm>
#include "Game.h"
#include "PlayingState.h"
#include "Menu.h"


#undef main
int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;

	//auto& renderManager = RenderManager::Instance();
//
//    AudioManager::Instance().InitMusicPlayer();
//    AudioManager::Instance().LoadBGM("pokemon");
//    AudioManager::Instance().PlayBGM();
	Menu menu;
	menu.DrawMenu();
	
    // TODO: END. this entire block is just for testing ////////////////////////////////////////////////////////////////


    return 0;

}
