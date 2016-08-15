#pragma once

#include "Core/Input.h"
#include "Common/type.h"
#include "Common/ThirdPartyLib/glfw.h"
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

	virtual bool isMouseButtonDown(MouseButtonCode mouseButtonCode) const override;
	virtual bool isMouseButtonUp(MouseButtonCode mouseButtonCode) const override;
	virtual bool isMouseButtonHold(MouseButtonCode mouseButtonCode) const override;

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

	// mapping glfw key/button codes to engine codes
	typedef std::underlying_type<KeyCode>::type         EngineKeyCodeType;
	typedef std::underlying_type<MouseButtonCode>::type EngineMouseButtonCodeType;
	EngineKeyCodeType         m_keyCodeMap[GLFW_KEY_LAST + 1];
	EngineMouseButtonCodeType m_mouseButtonCodeMap[GLFW_MOUSE_BUTTON_LAST + 1];

	// whether the key/button is down after current update
	bool m_currentKeyStates[static_cast<EngineKeyCodeType>(KeyCode::LAST) + 1];
	bool m_currentMouseButtonStates[static_cast<EngineMouseButtonCodeType>(MouseButtonCode::LAST) + 1];
	// whether the key/button is down after last update
	bool m_lastKeyStates[static_cast<EngineKeyCodeType>(KeyCode::LAST) + 1];
	bool m_lastMouseButtonStates[static_cast<EngineMouseButtonCodeType>(MouseButtonCode::LAST) + 1];

	void initKeyCodeMap();
	void initMouseButtonCodeMap();
};

}