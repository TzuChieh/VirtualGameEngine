#include "GlfwInput.h"
#include "Common/type.h"
#include "Common/ThirdPartyLib/glfw.h"
#include "Core/Input.h"

#include <iostream>

using namespace ve;

GlfwInput::GlfwInput(GLFWwindow* glfwWindow) : 
	m_glfwWindow(glfwWindow)
{

}

GlfwInput::~GlfwInput()
{

}

bool GlfwInput::init(const EngineProxy& engineProxy)
{
	if(!m_glfwWindow)
	{
		std::cerr << "GlfwInput init error: glfw window pointer is null" << std::endl;
		return false;
	}

	// TODO: this is probably bad since late initialization cause EngineProxy to have a default ctor (internal Engine pointer is null!)
	m_engineProxy = engineProxy;

	glfwSetInputMode(m_glfwWindow, GLFW_STICKY_KEYS, GLFW_TRUE);
	glfwSetInputMode(m_glfwWindow, GLFW_STICKY_MOUSE_BUTTONS, GLFW_TRUE);

	initKeyCodeMap();
	initMouseButtonCodeMap();

	// init key states to false
	for(uint32 i = 0; i <= static_cast<EngineKeyCodeType>(KeyCode::LAST); i++)
	{
		m_currentKeyStates[i] = false;
		m_lastKeyStates[i] = false;
	}

	// init mouse button states to false
	for(uint32 i = 0; i <= static_cast<EngineMouseButtonCodeType>(MouseButtonCode::LAST); i++)
	{
		m_currentMouseButtonStates[i] = false;
		m_lastMouseButtonStates[i] = false;
	}

	// set cursor initial position
	glfwGetCursorPos(m_glfwWindow, &m_currentCursorPosXpx, &m_currentCursorPosYpx);
	m_currentCursorPosYpx = static_cast<double>(m_engineProxy.getDisplayHeightPx()) - m_currentCursorPosYpx;
	m_lastCursorPosXpx = m_currentCursorPosXpx;
	m_lastCursorPosYpx = m_currentCursorPosYpx;

	// set cursor movement to zero pixel
	m_cursorMovementDeltaXpx = 0.0;
	m_cursorMovementDeltaYpx = 0.0;

	return true;
}

void GlfwInput::update()
{
	glfwPollEvents();

	// update keyboard keys
	EngineKeyCodeType engineKeyCode;
	for(uint32 i = 0; i <= GLFW_KEY_LAST; i++)
	{
		// test if i is a mapped GLFW key
		if(m_keyCodeMap[i] != static_cast<EngineKeyCodeType>(KeyCode::UNKNOWN))
		{
			engineKeyCode = m_keyCodeMap[i];
			m_lastKeyStates[engineKeyCode] = m_currentKeyStates[engineKeyCode];
			m_currentKeyStates[engineKeyCode] = (glfwGetKey(m_glfwWindow, i) == GLFW_PRESS);
		}
	}

	// update mouse buttons
	EngineMouseButtonCodeType engineMouseButtonCode;
	for(uint32 i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++)
	{
		// test if i is a mapped GLFW mouse button
		if(m_mouseButtonCodeMap[i] != static_cast<EngineMouseButtonCodeType>(MouseButtonCode::UNKNOWN))
		{
			engineMouseButtonCode = m_mouseButtonCodeMap[i];
			m_lastMouseButtonStates[engineMouseButtonCode] = m_currentMouseButtonStates[engineMouseButtonCode];
			m_currentMouseButtonStates[engineMouseButtonCode] = (glfwGetMouseButton(m_glfwWindow, i) == GLFW_PRESS);
		}
	}

	// update cursor measurements
	m_lastCursorPosXpx = m_currentCursorPosXpx;
	m_lastCursorPosYpx = m_currentCursorPosYpx;
	glfwGetCursorPos(m_glfwWindow, &m_currentCursorPosXpx, &m_currentCursorPosYpx);
	m_currentCursorPosYpx = static_cast<double>(m_engineProxy.getDisplayHeightPx()) - m_currentCursorPosYpx;

	m_cursorMovementDeltaXpx = static_cast<float64>(m_currentCursorPosXpx - m_lastCursorPosXpx);
	m_cursorMovementDeltaYpx = static_cast<float64>(m_currentCursorPosYpx - m_lastCursorPosYpx);
}

void GlfwInput::decompose()
{

}

void GlfwInput::virtualizeCursor() const
{
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void GlfwInput::unvirtualizeCursor() const
{
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool GlfwInput::isKeyDown(KeyCode keyCode) const
{
	return !m_lastKeyStates[static_cast<EngineKeyCodeType>(keyCode)] &&
	       m_currentKeyStates[static_cast<EngineKeyCodeType>(keyCode)];
}

bool GlfwInput::isKeyUp(KeyCode keyCode) const
{
	return m_lastKeyStates[static_cast<EngineKeyCodeType>(keyCode)] &&
	       !m_currentKeyStates[static_cast<EngineKeyCodeType>(keyCode)];
}

bool GlfwInput::isKeyHold(KeyCode keyCode) const
{
	return m_lastKeyStates[static_cast<EngineKeyCodeType>(keyCode)] &&
	       m_currentKeyStates[static_cast<EngineKeyCodeType>(keyCode)];
}

bool GlfwInput::isMouseButtonDown(MouseButtonCode mouseButtonCode) const
{
	return !m_lastMouseButtonStates[static_cast<EngineMouseButtonCodeType>(mouseButtonCode)] &&
	       m_currentMouseButtonStates[static_cast<EngineMouseButtonCodeType>(mouseButtonCode)];
}

bool GlfwInput::isMouseButtonUp(MouseButtonCode mouseButtonCode) const
{
	return m_lastMouseButtonStates[static_cast<EngineMouseButtonCodeType>(mouseButtonCode)] &&
	       !m_currentMouseButtonStates[static_cast<EngineMouseButtonCodeType>(mouseButtonCode)];
}

bool GlfwInput::isMouseButtonHold(MouseButtonCode mouseButtonCode) const
{
	return m_lastMouseButtonStates[static_cast<EngineMouseButtonCodeType>(mouseButtonCode)] &&
	       m_currentMouseButtonStates[static_cast<EngineMouseButtonCodeType>(mouseButtonCode)];
}

void GlfwInput::getCursorPositionPx(float64* out_x, float64* out_y) const
{
	*out_x = static_cast<float64>(m_currentCursorPosXpx);
	*out_y = static_cast<float64>(m_currentCursorPosYpx);
}

void GlfwInput::getCursorMovementDeltaPx(float64* out_dx, float64* out_dy) const
{
	*out_dx = m_cursorMovementDeltaXpx;
	*out_dy = m_cursorMovementDeltaYpx;
}

void GlfwInput::initKeyCodeMap()
{
	for(uint32 i = 0; i <= GLFW_KEY_LAST; i++)
	{
		m_keyCodeMap[i] = static_cast<EngineKeyCodeType>(KeyCode::UNKNOWN);
	}

	m_keyCodeMap[GLFW_KEY_F1] = static_cast<EngineKeyCodeType>(KeyCode::F1);
	m_keyCodeMap[GLFW_KEY_F2] = static_cast<EngineKeyCodeType>(KeyCode::F2);
	m_keyCodeMap[GLFW_KEY_F3] = static_cast<EngineKeyCodeType>(KeyCode::F3);
	m_keyCodeMap[GLFW_KEY_F4] = static_cast<EngineKeyCodeType>(KeyCode::F4);
	m_keyCodeMap[GLFW_KEY_F5] = static_cast<EngineKeyCodeType>(KeyCode::F5);
	m_keyCodeMap[GLFW_KEY_F6] = static_cast<EngineKeyCodeType>(KeyCode::F6);
	m_keyCodeMap[GLFW_KEY_F7] = static_cast<EngineKeyCodeType>(KeyCode::F7);
	m_keyCodeMap[GLFW_KEY_F8] = static_cast<EngineKeyCodeType>(KeyCode::F8);
	m_keyCodeMap[GLFW_KEY_F9] = static_cast<EngineKeyCodeType>(KeyCode::F9);
	m_keyCodeMap[GLFW_KEY_F10] = static_cast<EngineKeyCodeType>(KeyCode::F10);
	m_keyCodeMap[GLFW_KEY_F11] = static_cast<EngineKeyCodeType>(KeyCode::F11);
	m_keyCodeMap[GLFW_KEY_F12] = static_cast<EngineKeyCodeType>(KeyCode::F12);

	m_keyCodeMap[GLFW_KEY_A] = static_cast<EngineKeyCodeType>(KeyCode::A);
	m_keyCodeMap[GLFW_KEY_B] = static_cast<EngineKeyCodeType>(KeyCode::B);
	m_keyCodeMap[GLFW_KEY_C] = static_cast<EngineKeyCodeType>(KeyCode::C);
	m_keyCodeMap[GLFW_KEY_D] = static_cast<EngineKeyCodeType>(KeyCode::D);
	m_keyCodeMap[GLFW_KEY_E] = static_cast<EngineKeyCodeType>(KeyCode::E);
	m_keyCodeMap[GLFW_KEY_F] = static_cast<EngineKeyCodeType>(KeyCode::F);
	m_keyCodeMap[GLFW_KEY_G] = static_cast<EngineKeyCodeType>(KeyCode::G);
	m_keyCodeMap[GLFW_KEY_H] = static_cast<EngineKeyCodeType>(KeyCode::H);
	m_keyCodeMap[GLFW_KEY_I] = static_cast<EngineKeyCodeType>(KeyCode::I);
	m_keyCodeMap[GLFW_KEY_J] = static_cast<EngineKeyCodeType>(KeyCode::J);
	m_keyCodeMap[GLFW_KEY_K] = static_cast<EngineKeyCodeType>(KeyCode::K);
	m_keyCodeMap[GLFW_KEY_L] = static_cast<EngineKeyCodeType>(KeyCode::L);
	m_keyCodeMap[GLFW_KEY_M] = static_cast<EngineKeyCodeType>(KeyCode::M);
	m_keyCodeMap[GLFW_KEY_N] = static_cast<EngineKeyCodeType>(KeyCode::N);
	m_keyCodeMap[GLFW_KEY_O] = static_cast<EngineKeyCodeType>(KeyCode::O);
	m_keyCodeMap[GLFW_KEY_P] = static_cast<EngineKeyCodeType>(KeyCode::P);
	m_keyCodeMap[GLFW_KEY_Q] = static_cast<EngineKeyCodeType>(KeyCode::Q);
	m_keyCodeMap[GLFW_KEY_R] = static_cast<EngineKeyCodeType>(KeyCode::R);
	m_keyCodeMap[GLFW_KEY_S] = static_cast<EngineKeyCodeType>(KeyCode::S);
	m_keyCodeMap[GLFW_KEY_T] = static_cast<EngineKeyCodeType>(KeyCode::T);
	m_keyCodeMap[GLFW_KEY_U] = static_cast<EngineKeyCodeType>(KeyCode::U);
	m_keyCodeMap[GLFW_KEY_V] = static_cast<EngineKeyCodeType>(KeyCode::V);
	m_keyCodeMap[GLFW_KEY_W] = static_cast<EngineKeyCodeType>(KeyCode::W);
	m_keyCodeMap[GLFW_KEY_X] = static_cast<EngineKeyCodeType>(KeyCode::X);
	m_keyCodeMap[GLFW_KEY_Y] = static_cast<EngineKeyCodeType>(KeyCode::Y);
	m_keyCodeMap[GLFW_KEY_Z] = static_cast<EngineKeyCodeType>(KeyCode::Z);
}

void GlfwInput::initMouseButtonCodeMap()
{
	for(uint32 i = 0; i <= GLFW_MOUSE_BUTTON_LAST; i++)
	{
		m_mouseButtonCodeMap[i] = static_cast<EngineMouseButtonCodeType>(MouseButtonCode::UNKNOWN);
	}

	m_mouseButtonCodeMap[GLFW_MOUSE_BUTTON_1] = static_cast<EngineMouseButtonCodeType>(MouseButtonCode::LEFT);
	m_mouseButtonCodeMap[GLFW_MOUSE_BUTTON_2] = static_cast<EngineMouseButtonCodeType>(MouseButtonCode::RIGHT);
}