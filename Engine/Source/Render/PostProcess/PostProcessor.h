#pragma once

#include <vector>
#include <memory>

namespace ve
{

class PEffect;
class Texture2D;
class RenderCommand;

class PostProcessor
{
public:
	bool init();
	void decompose();

	void renderEffectToTexture(const PEffect& effect, const Texture2D& destination);
	void renderEffectToDisplay(const PEffect& effect);

private:
	std::vector<std::shared_ptr<RenderCommand>> m_renderCommands;

	void populateCommandBuffer(const PEffect& effect);
	void executeCommands();
};

}