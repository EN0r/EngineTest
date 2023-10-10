#include "UI.h"

void UI::init(SDL_Renderer* renderer)
{
	for (auto& uiItem : this->uiComponents)
	{
		uiItem.start(renderer);
	}
}

void UI::render(SDL_Renderer* renderer)
{
	for (auto& uiItem : this->uiComponents)
	{
		uiItem.update(renderer);
	}
}

