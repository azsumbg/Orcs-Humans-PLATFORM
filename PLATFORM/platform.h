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
	template<typename T> class BAG
	{
	private:
		T* m_ptr{ nullptr };
		size_t max_size{ 0 };
		size_t next_pos{ 0 };

	public:
		BAG() :max_size{ 1 }, m_ptr{ reinterpret_cast<T*>(calloc(max_size,sizeof(T))) } {};
		BAG(size_t lenght) :max_size{ lenght }, m_ptr{ reinterpret_cast<T*>(calloc(lenght,sizeof(T))) } {};
		BAG(const BAG<T>& other)
		{
			if (other.m_ptr == this->m_ptr || other.next_pos < 1)return;

			m_ptr = reinterpret_cast<T*>(calloc(other.max_size, sizeof(T)));
			max_size = other.max_size;
			next_pos = other.next_pos;

			for (size_t count = 0; count < next_pos; count++)m_ptr[count] = other.m_ptr[count];
		}

		~BAG()
		{
			if (m_ptr)free(m_ptr);
		}

		bool empty() const
		{
			if (next_pos == 0)return true;
			return false;
		}
		size_t size() const
		{
			return next_pos;
		}
		size_t capacity() const
		{
			return max_size;
		}

		bool push_back(T element)
		{
			if (m_ptr)
			{
				if (next_pos + 1 < max_size)
				{
					m_ptr[next_pos] = element;
					++next_pos;
					return true;
				}
				else
				{
					++max_size;
					m_ptr = reinterpret_cast<T*>(realloc(m_ptr, max_size * sizeof(T));
					if (m_ptr)
					{
						m_ptr[next_pos] = element;
						++next_pos;
						return true;
					}
				}
			}
			return false;
		}
		bool push_back(T* element)
		{
			if (m_ptr)
			{
				if (next_pos + 1 < max_size)
				{
					m_ptr[next_pos] = (*element);
					++next_pos;
					return true;
				}
				else
				{
					++max_size;
					m_ptr = reinterpret_cast<T*>(realloc(m_ptr, max_size * sizeof(T));
					if (m_ptr)
					{
						m_ptr[next_pos] = (*element);
						++next_pos;
						return true;
					}
				}
			}
			return false;
		}

		void push_front(T element)
		{
			(*m_ptr) = element;
		}
		void push_front(T* element)
		{
			(*m_ptr) = (*element);
		}

		void erase(size_t index)
		{
			if (index >= next_pos)return;

			if (m_ptr)
			{
				for (size_t count = index; count < next_pos - 1; ++count)m_ptr[count] = m_ptr[count + 1];
				
			}
		}

		BAG& operator [] (size_t index)
		{
			if (index >= next_pos) throw std::runtime_error("Wrong index !");
			if (!m_ptr) throw std::runtime_error("Invalid data pointer !");

			return m_ptr[index];
		}
	};
	
	
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

	template<typename T>concept primes = std::is_same<T, int>::value || std::is_same<T, float>::value
		|| std::is_same<T, double>::value || std::is_same<T, long>::value || std::is_same<T, char>::value;

	bool PLATFORM_API Intersect(FRECT first, FRECT second);

}