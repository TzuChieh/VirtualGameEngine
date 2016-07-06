#include "Engine.h"

#include <iostream>

int main(int argc, char** argv) {
	//std::cout << sizeof(unsigned int) << std::endl;

	xe::Engine engine;
	if(!engine.init()) {
		std::cerr << "Engine initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	engine.start();

	return EXIT_SUCCESS;
}