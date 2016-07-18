#pragma once

#include "Input.h"
#include "Common/type.h"
#include "glfw.h"
#include <type_traits>

struct GLFWwindow;

namespace xe
{

class GlfwInput : public Input
{
public:
	GlfwInput(GLFWwindow* glfwWindow);
	virtual ~GlfwInput() override;

	virtual bool init() override;
	virtual void update() override;
	virtual void decompose() override;

	virtual bool isKeyDown(KeyCode keyCode) const override;
	virtual bool isKeyUp(KeyCode keyCode) const override;
	virtual bool isKeyHold(KeyCode keyCode) const override;

private:
	GLFWwindow* m_glfwWindow;

	// mapping glfw key codes to engine key codes
	typedef std::underlying_type<KeyCode>::type engineKeyCodeType;
	engineKeyCodeType m_keyCodeMap[GLFW_KEY_LAST + 1];

	// TODO: add a constant like engine_key_last, don't use glfw's
	// whether the key is down after current update
	bool m_currentKeyStates[GLFW_KEY_LAST + 1];
	// whether the key is down after last update
	bool m_lastKeyStates[GLFW_KEY_LAST + 1];

	void initKeyCodeMap();
};

}