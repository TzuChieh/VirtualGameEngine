#include "GlfwInput.h"
#include "Input.h"
#include "glfw.h"
#include "Common/type.h"

#include <iostream>

using namespace xe;

GlfwInput::GlfwInput(GLFWwindow* glfwWindow)
: m_glfwWindow(glfwWindow)
{

}

GlfwInput::~GlfwInput()
{

}

bool GlfwInput::init()
{
	if(!m_glfwWindow)
	{
		std::cerr << "GlfwInput init error: glfw window pointer is null" << std::endl;
		return false;
	}

	glfwSetInputMode(m_glfwWindow, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(m_glfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	initKeyCodeMap();

	// init key states to false
	for(uint32 i = 0; i <= GLFW_KEY_LAST; i++)
	{
		m_currentKeyStates[i] = false;
		m_lastKeyStates[i] = false;
	}

	return true;
}

void GlfwInput::update()
{
	glfwPollEvents();

	uint32 engineKeyCode;
	for(uint32 i = 0; i <= GLFW_KEY_LAST; i++)
	{
		// test if i is a mapped glfw key
		if(m_keyCodeMap[i] != static_cast<engineKeyCodeType>(KeyCode::UNKNOWN))
		{
			engineKeyCode = m_keyCodeMap[i];
			m_lastKeyStates[engineKeyCode] = m_currentKeyStates[engineKeyCode];
			m_currentKeyStates[engineKeyCode] = (glfwGetKey(m_glfwWindow, i) == GLFW_PRESS);
		}
	}
}

void GlfwInput::decompose()
{

}

bool GlfwInput::isKeyDown(KeyCode keyCode) const
{
	return !m_lastKeyStates[static_cast<engineKeyCodeType>(keyCode)] && 
	       m_currentKeyStates[static_cast<engineKeyCodeType>(keyCode)];
}

bool GlfwInput::isKeyUp(KeyCode keyCode) const
{
	return m_lastKeyStates[static_cast<engineKeyCodeType>(keyCode)] &&
	       !m_currentKeyStates[static_cast<engineKeyCodeType>(keyCode)];
}

bool GlfwInput::isKeyHold(KeyCode keyCode) const
{
	return m_lastKeyStates[static_cast<engineKeyCodeType>(keyCode)] &&
	       m_currentKeyStates[static_cast<engineKeyCodeType>(keyCode)];
}

void GlfwInput::initKeyCodeMap()
{
	for(uint32 i = 0; i <= GLFW_KEY_LAST; i++)
	{
		m_keyCodeMap[i] = static_cast<engineKeyCodeType>(KeyCode::UNKNOWN);
	}

	m_keyCodeMap[GLFW_KEY_F1] = static_cast<engineKeyCodeType>(KeyCode::F1);
	m_keyCodeMap[GLFW_KEY_F2] = static_cast<engineKeyCodeType>(KeyCode::F2);
	m_keyCodeMap[GLFW_KEY_F3] = static_cast<engineKeyCodeType>(KeyCode::F3);
	m_keyCodeMap[GLFW_KEY_F4] = static_cast<engineKeyCodeType>(KeyCode::F4);
	m_keyCodeMap[GLFW_KEY_F5] = static_cast<engineKeyCodeType>(KeyCode::F5);
	m_keyCodeMap[GLFW_KEY_F6] = static_cast<engineKeyCodeType>(KeyCode::F6);
	m_keyCodeMap[GLFW_KEY_F7] = static_cast<engineKeyCodeType>(KeyCode::F7);
	m_keyCodeMap[GLFW_KEY_F8] = static_cast<engineKeyCodeType>(KeyCode::F8);
	m_keyCodeMap[GLFW_KEY_F9] = static_cast<engineKeyCodeType>(KeyCode::F9);
	m_keyCodeMap[GLFW_KEY_F10] = static_cast<engineKeyCodeType>(KeyCode::F10);
	m_keyCodeMap[GLFW_KEY_F11] = static_cast<engineKeyCodeType>(KeyCode::F11);
	m_keyCodeMap[GLFW_KEY_F12] = static_cast<engineKeyCodeType>(KeyCode::F12);

	m_keyCodeMap[GLFW_KEY_A] = static_cast<engineKeyCodeType>(KeyCode::A);
	m_keyCodeMap[GLFW_KEY_B] = static_cast<engineKeyCodeType>(KeyCode::B);
	m_keyCodeMap[GLFW_KEY_C] = static_cast<engineKeyCodeType>(KeyCode::C);
	m_keyCodeMap[GLFW_KEY_D] = static_cast<engineKeyCodeType>(KeyCode::D);
	m_keyCodeMap[GLFW_KEY_E] = static_cast<engineKeyCodeType>(KeyCode::E);
	m_keyCodeMap[GLFW_KEY_F] = static_cast<engineKeyCodeType>(KeyCode::F);
	m_keyCodeMap[GLFW_KEY_G] = static_cast<engineKeyCodeType>(KeyCode::G);
	m_keyCodeMap[GLFW_KEY_H] = static_cast<engineKeyCodeType>(KeyCode::H);
	m_keyCodeMap[GLFW_KEY_I] = static_cast<engineKeyCodeType>(KeyCode::I);
	m_keyCodeMap[GLFW_KEY_J] = static_cast<engineKeyCodeType>(KeyCode::J);
	m_keyCodeMap[GLFW_KEY_K] = static_cast<engineKeyCodeType>(KeyCode::K);
	m_keyCodeMap[GLFW_KEY_L] = static_cast<engineKeyCodeType>(KeyCode::L);
	m_keyCodeMap[GLFW_KEY_M] = static_cast<engineKeyCodeType>(KeyCode::M);
	m_keyCodeMap[GLFW_KEY_N] = static_cast<engineKeyCodeType>(KeyCode::N);
	m_keyCodeMap[GLFW_KEY_O] = static_cast<engineKeyCodeType>(KeyCode::O);
	m_keyCodeMap[GLFW_KEY_P] = static_cast<engineKeyCodeType>(KeyCode::P);
	m_keyCodeMap[GLFW_KEY_Q] = static_cast<engineKeyCodeType>(KeyCode::Q);
	m_keyCodeMap[GLFW_KEY_R] = static_cast<engineKeyCodeType>(KeyCode::R);
	m_keyCodeMap[GLFW_KEY_S] = static_cast<engineKeyCodeType>(KeyCode::S);
	m_keyCodeMap[GLFW_KEY_T] = static_cast<engineKeyCodeType>(KeyCode::T);
	m_keyCodeMap[GLFW_KEY_U] = static_cast<engineKeyCodeType>(KeyCode::U);
	m_keyCodeMap[GLFW_KEY_V] = static_cast<engineKeyCodeType>(KeyCode::V);
	m_keyCodeMap[GLFW_KEY_W] = static_cast<engineKeyCodeType>(KeyCode::W);
	m_keyCodeMap[GLFW_KEY_X] = static_cast<engineKeyCodeType>(KeyCode::X);
	m_keyCodeMap[GLFW_KEY_Y] = static_cast<engineKeyCodeType>(KeyCode::Y);
	m_keyCodeMap[GLFW_KEY_Z] = static_cast<engineKeyCodeType>(KeyCode::Z);
}