#include "UIFrame.h"

void UIFrame::start(SDL_Renderer* renderer)
{
	imgRenderer.initImage(renderer);
	this->init = true;
}

void UIFrame::update(SDL_Renderer* renderer)
{
	if (this->init)
		imgRenderer.createImage(renderer, size);

}
