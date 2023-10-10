#pragma once
#include "UI.h"
#include "image.h"
class UIFrame : public UI
{
public:
	void start(SDL_Renderer* renderer);
	void update(SDL_Renderer* renderer);

	UIFrame()
	{

	}

	inline void setBackground(const char* path) { path = this->defaultFrameImage; }
	inline void setPosition(int x, int y) { this->size.x = x; this->size.y = y; }
	inline void setSize(SDL_Rect _size) { this->size = _size; } // default size 400,200
	inline SDL_Rect getSize() { return this->size; }
	inline void addChild(UI* childItem)
	{
		this->children.push_back(childItem);
	}
	inline std::vector<UI*> getChildren() { return this->children; } // returns array of children

	/*
		template<typename child>
		inline child getChildEX() // returns specific child based on typeID
		{
			for (auto child : this->children)
			{

				std::string n1 = typeid(child).name();
				n1.erase(n1.end() - 10, n1.end());
				std::string n2 = typeid(child.second).name();
				if (n1 == n2) {
					return dynamic_cast<child>(child.second);
					break;
				}
			}
			return nullptr;
		}
	*/

private:
	bool init = false;
	SDL_Rect size = { 0,0,400,200 };
	image imgRenderer;
	const char* defaultFrameImage = "./resources/placeholder/uiComponents/default/defaultFrame.png";
	std::vector<UI*> children;
};

