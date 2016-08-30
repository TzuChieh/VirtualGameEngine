#pragma once

#include "Common/type.h"
#include "Core/Platform.h"
#include "Common/logging.h"

#include <string>
#include <memory>

DECLARE_LOG_SENDER_EXTERN(GlfwPlatform);

struct GLFWwindow;

namespace ve
{

class Input;

class GlfwPlatform : public Platform
{
public:
	GlfwPlatform(const std::string& title, const uint32 widthPx, const uint32 heightPx);
	virtual ~GlfwPlatform() override;

	virtual void update() override;
	virtual void refresh() override;

	virtual bool shouldClose() override;

	virtual inline uint32 getWidthPx() const override
	{
		return m_widthPx;
	}

	virtual inline uint32 getHeightPx() const override
	{
		return m_heightPx;
	}

	virtual inline const Input* getInput() const override
	{
		return m_input.get();
	}

	virtual inline const Timer* getTimer() const override
	{
		return m_timer.get();
	}

private:
	std::string m_title;

	uint32 m_widthPx;// the width in pixels for the displayable area
	uint32 m_heightPx;// the height in pixels for the displayable area

	GLFWwindow* m_glfwWindow;
	std::unique_ptr<Input> m_input;
	std::unique_ptr<Timer> m_timer;

	bool init();
};

}