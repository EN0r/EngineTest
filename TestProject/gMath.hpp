#pragma once
#include "SDL.h"
namespace tools
{
	//int frameTime;
	//int mousePosX, mousePosy;
	//Uint32 mouseState;
	struct _2DSize
	{
		float w, h;
		inline _2DSize operator+(_2DSize a) {
			return { a.w + w,a.h + h };
		}
		inline _2DSize operator-(_2DSize a) {
			return { a.w - w,a.h - h };
		}
		inline _2DSize operator/(_2DSize a) {
			return { a.w / w,a.h / h };
		}
	};
	struct vec2 // not the game component
	{
		float x, y;
		inline vec2 operator+(vec2 a) {
			return { a.x + x,a.y + y };
		}
		inline vec2 operator-(vec2 a) {
			return { a.x - x,a.y - y };
		}
		inline vec2 operator/(vec2 a) {
			return { a.x / x,a.y / y };
		}
	};

	inline bool AABB(SDL_Rect obj, SDL_Rect r1) // bounding box collision use for gui ect
	{
		if (obj.x < r1.x + r1.w &&
			obj.x + obj.w > r1.x &&
			obj.y < r1.y + r1.h &&
			obj.y + obj.h> r1.y)
		{
			return true;
		}
		return false;
	}
}
