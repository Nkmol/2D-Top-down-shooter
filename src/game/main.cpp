#include <iostream>
#include "Engine.h"

int main(int argc, char *argv[]){
    std::cout << "Hello, World!" << std::endl;

	auto engine = new Engine::MainManager();

	std::cout << engine->Message;


	std::cin.get();

    return 0;
}