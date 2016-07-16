#pragma once

#include "Common/type.h"
#include "Platform.h"

#include <string>

struct GLFWwindow;

namespace xe
{

class Input;

class GlfwPlatform : public Platform
{
public:
	GlfwPlatform(const std::string& title, const uint32 widthPx, const uint32 heightPx);

	virtual bool init() override;
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

private:
	std::string m_title;

	uint32 m_widthPx;// the width in pixels for the displayable area
	uint32 m_heightPx;// the height in pixels for the displayable area

	GLFWwindow* m_glfwWindow;
	Input* m_input;
};

}