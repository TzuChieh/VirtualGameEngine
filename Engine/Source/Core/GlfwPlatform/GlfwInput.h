#pragma once

#include "Core/Input.h"
#include "Common/type.h"
#include "Core/glfw.h"
#include "Core/EngineProxy.h"

#include <type_traits>

struct GLFWwindow;

namespace xe
{

class GlfwInput : public Input
{
public:
	GlfwInput(GLFWwindow* glfwWindow);
	virtual ~GlfwInput() override;

	virtual bool init(const EngineProxy& engineProxy) override;
	virtual void update() override;
	virtual void decompose() override;

	virtual void virtualizeCursor() const override;
	virtual void unvirtualizeCursor() const override;

	virtual bool isKeyDown(KeyCode keyCode) const override;
	virtual bool isKeyUp(KeyCode keyCode) const override;
	virtual bool isKeyHold(KeyCode keyCode) const override;

	virtual void getCursorPositionPx(float64* out_x, float64* out_y) const override;
	virtual void getCursorMovementDeltaPx(float64* out_dx, float64* out_dy) const override;

private:
	GLFWwindow* m_glfwWindow;
	EngineProxy m_engineProxy;

	// GLFW uses double to represent cursor position
	double m_lastCursorPosXpx;
	double m_lastCursorPosYpx;
	double m_currentCursorPosXpx;
	double m_currentCursorPosYpx;

	float64 m_cursorMovementDeltaXpx;
	float64 m_cursorMovementDeltaYpx;

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