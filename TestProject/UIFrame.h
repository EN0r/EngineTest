#pragma once
#include "UI.h"
#include "image.h"
class UIFrame : public UI
{
public:
	void start(SDL_Renderer* renderer);
	void update(SDL_Renderer* renderer);

	inline void setSize(SDL_Rect _size) { this->size = _size; }
	inline SDL_Rect getSize() { return this->size; }
private:
	SDL_Rect size = { 0,0,400,200 };
	image imgRenderer;
	const char* defaultFrameImage = "./resources/placeholder/uiComponents/default/defaultFrame.png";

};

