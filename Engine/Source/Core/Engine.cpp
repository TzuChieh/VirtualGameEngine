#include "Common/type.h"
#include "Engine.h"
#include "GlfwWindow.h"
#include "GraphicsApi.h"
#include "Game/GameProgram.h"
#include "Renderer/Renderer.h"

#include <iostream>

using namespace xe;

Engine::Engine()
: m_window(nullptr), m_gameProgram(nullptr) {

}

bool Engine::init() {
	m_window = new GlfwWindow("Xeno Game Engine ver. 0.0", 1366, 768);

	// OpenGL context should be constructed after Window initialized
	if(!m_window->init()) {
		std::cerr << "Window initialization failed" << std::endl;
		return false;
	}

	// OpenGL core-profile & extension functions should be loaded after GLEW initialized
	glewExperimental = GL_TRUE;
	if(glewInit() != GLEW_OK) {  
		std::cerr << "GLEW initialization failed" << std::endl;
		return false;
	}

	if(!m_gameProgram) {
		std::cerr << "GameProgram not specified" << std::endl;
		return false;
	}

	if(!m_gameProgram->init()) {
		std::cerr << "GameProgram initialization failed" << std::endl;
		return false;
	}

	std::cout << "Engine initialized" << std::endl;

	return true;
}

void Engine::start() {
	std::cout << "Engine started" << std::endl;

	run();
}

void Engine::stop() {
	std::cout << "Engine stopped" << std::endl;

	dispose();
}

void Engine::run() {
	while(!m_window->shouldClose()) {
		update();
		render();
	}

	stop();
}

void Engine::update() {
	m_window->update();
	m_gameProgram->update();
}

void Engine::render() {
	// TODO: render stuff

	m_window->refresh();
}

void Engine::dispose() {
	if(m_window) {
		m_window->dispose();
		delete m_window;
	}

	std::cout << "Engine disposed" << std::endl;
}

void Engine::setGameProgram(GameProgram* gameProgram) {
	m_gameProgram = gameProgram;
}

void Engine::setGameProgram(Renderer* renderer) {
	m_renderer = renderer;
}