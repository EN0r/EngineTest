#include "imguiMenuUI.h"

void imguiMenuUI::init(SDL_Renderer* renderer, SDL_Window* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
}

void imguiMenuUI::update(std::vector<const char*> information)
{
	if (visible == true)
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		{
			ImGui::Begin("Info");
			ImGui::SetWindowSize({400,150});
			if (information.size() <= 0)
			{
				for (auto info : information)
				{
					ImGui::Text(info);
				}
			}
			ImGui::End();
		}
		ImGui::EndFrame();
		ImGui::Render();
	}
	ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

std::map<int, component*> imguiMenuUI::getComponents(entity* _ent, int& entID)
{
	entID = _ent->getEID();
	return _ent->getComponentList();
}
