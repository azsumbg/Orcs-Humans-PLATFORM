#pragma once

#ifdef PLATFORM_EXPORTS
#define PLATFORM_API __declspec(dllexport)
#else 
#define PLATFORM_API __declspec(dllimport)
#endif

#include <random>
#include <type_traits>

constexpr float scr_width{ 1000.0f };
constexpr float scr_height{ 800.0f };

constexpr float sky{ 50.0f };
constexpr float ground { 750.0f };

enum class dirs { left = 0, right = 1, up = 2, down = 3, stop = 4 };
enum class actions { stop = 0, move = 1, flee = 2, harvest = 3, shoot = 4, melee = 5 };
enum class unit_type { peon = 0, warrior = 1, archer = 2, knight = 3, artillery = 4 };
enum class obstacle { rock = 0, small_tree = 1, mid_tree = 2, big_tree = 3 };

struct FPOINT
{
	float x{ 0 };
	float y{ 0 };
};
struct FRECT
{
	FPOINT up_left{ 0 };
	FPOINT up_right{ 0 };
	FPOINT down_left{ 0 };
	FPOINT down_right{ 0 };
};

namespace dll
{
	class PLATFORM_API PROTON
	{
	protected:
		float _width{ 0 };
		float _height{ 0 };

	public:
		FPOINT start{};
		FPOINT end{};
		FPOINT center{};

		float radiusX{ 0 };
		float radiusY{ 0 };

		PROTON();
		PROTON(float _sx, float _sy);
		PROTON(float _sx, float _sy, float _swidth, float _sheight);

		virtual ~PROTON() {};

		void SetEdges();
		void NewWidth(float _new_width);
		void NewHeight(float _new_height);
		void NewDims(float _new_width, float _new_height);

		float GetWidth() const;
		float GetHeight() const;
	};









	// FUNCTIONS *******************************************

	bool PLATFORM_API Intersect(FRECT first, FRECT second);

}