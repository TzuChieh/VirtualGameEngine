#include "Engine.h"
#include "Game/TestGameProgram.h"

#include <iostream>

int main(int argc, char** argv) {

	xe::GameProgram* gameProgram = new xe::TestGameProgram;

	xe::Engine engine;
	engine.setGameProgram(gameProgram);

	if(!engine.init()) {
		std::cerr << "Engine initialization failed" << std::endl;
		exit(EXIT_FAILURE);
	}

	engine.start();
	
	delete gameProgram;

	return EXIT_SUCCESS;
}