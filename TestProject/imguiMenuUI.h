#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"

class imguiMenuUI
{
public:
	void init(SDL_Renderer* renderer);
	void update();
private:
	bool visible = true;
};

