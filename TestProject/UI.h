#pragma once
#include "world.h"
#include <vector>
enum UIITEMS
{
	UI_FRAME = 0,
	UI_BUTTON = 1
};
class UI
{
public:
	virtual void start(SDL_Renderer* renderer) = 0;
	virtual void update(SDL_Renderer* renderer) = 0;

	void render(SDL_Renderer* renderer);
	void init(SDL_Renderer* renderer);



	template<typename T>
	T getUIElement() // get component via class
	{
		for (auto component : this->uiComponents)
		{

			std::string n1 = typeid(T).name();
			n1.erase(n1.end() - 10, n1.end());
			std::string n2 = typeid(*component.second).name();
			if (n1 == n2) {
				return dynamic_cast<T>(component.second);
				break;
			}
		}

		//std::cout << "WARNING //" << " component does not exist: " << typeid(T).name() << std::endl;
		return nullptr;
	}


private:
	std::vector<UI> uiComponents;

};