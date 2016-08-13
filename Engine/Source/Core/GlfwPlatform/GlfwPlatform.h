#pragma once

#include "Common/type.h"
#include "Core/Platform.h"

#include <string>

struct GLFWwindow;

namespace xe
{

class Input;

class GlfwPlatform : public Platform
{
public:
	GlfwPlatform(const std::string& title, const uint32 widthPx, const uint32 heightPx);
	virtual ~GlfwPlatform() override;

	virtual bool init(const EngineProxy& engineProxy) override;
	virtual void update() override;
	virtual void refresh() override;
	virtual void decompose() override;

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
		return m_input;
	}

	virtual inline const Timer* getTimer() const override
	{
		return m_timer;
	}

private:
	std::string m_title;

	uint32 m_widthPx;// the width in pixels for the displayable area
	uint32 m_heightPx;// the height in pixels for the displayable area

	GLFWwindow* m_glfwWindow;
	Input* m_input;
	Timer* m_timer;
};

}