#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_sdlrenderer.h"
#include "entity.h"

class imguiMenuUI
{
public:
	static void init(SDL_Renderer* renderer, SDL_Window* window);
	static void update(std::vector<const char*> information);
	static std::map<int, component*> getComponents(entity* entity, int& entID);
private:
	static const bool visible = true;
};

