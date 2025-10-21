#include "pch.h"
#include "platform.h"

// RANDIT ************************

dll::RANDIT::RANDIT()
{
	std::random_device rd{};
	std::seed_seq sq{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937(sq);
}
dll::RANDIT::RANDIT(RANDIT& other)
{
	std::random_device rd{};
	std::seed_seq sq{ rd(),rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937(sq);
}
dll::RANDIT::~RANDIT()
{
	if (twister)delete twister;
}

int dll::RANDIT::operator()(int min, int max)
{
	std::uniform_int_distribution distrib(min, max);

	return distrib((*twister));
}

//////////////////////////////////

// PROTON ***********************

dll::PROTON::PROTON()
{
	_width = 1.0f;
	_height = 1.0f;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}
dll::PROTON::PROTON(float _sx, float _sy)
{
	start.x = _sx;
	start.y = _sy;

	_width = 1.0f;
	_height = 1.0f;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}
dll::PROTON::PROTON(float _sx, float _sy, float _swidth, float _sheight)
{
	start.x = _sx;
	start.y = _sy;

	_width = _swidth;
	_height = _sheight;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}

void dll::PROTON::SetEdges()
{
	end.x = start.x + _width;
	end.y = start.y + _height;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}
void dll::PROTON::NewWidth(float _new_width)
{
	_width = _new_width;
	
	end.x = start.x + _width;
	
	radiusX = _width / 2.0f;

	center.x = start.x + radiusX;
}
void dll::PROTON::NewHeight(float _new_height)
{
	_height = _new_height;

	end.y = start.y + _height;

	radiusY = _height / 2.0f;

	center.y = start.y + radiusY;
}
void dll::PROTON::NewDims(float _new_width, float _new_height)
{
	_width = _new_width;
	_height = _new_height;

	end.x = start.x + _width;
	end.y = start.y + _height;

	radiusX = _width / 2.0f;
	radiusY = _height / 2.0f;

	center.x = start.x + radiusX;
	center.y = start.y + radiusY;
}

float dll::PROTON::GetWidth() const
{
	return _width;
}
float dll::PROTON::GetHeight() const
{
	return _height;
}

/////////////////////////////////

// ASSETS **********************

dll::ASSETS::ASSETS(obstacle what_type, float start_x, float start_y) :PROTON(start_x, start_y)
{
	type = what_type;

	switch (type)
	{
	case obstacle::rock:
		NewDims(100.0f, 100.0f);
		break;

	case obstacle::orc_castle:
		NewDims(210.0f, 200.0f);
		goods_delay = 100;
		goods_in_asset = 1000;
		lifes = 1000;
		break;

	case obstacle::human_castle:
		NewDims(260.0f, 260.0f);
		goods_delay = 100;
		goods_in_asset = 1000;
		lifes = 1200;
		max_frames = 7;
		frame_delay = 9;
		break;

	case obstacle::small_tree:
		NewDims(47.0f, 80.0f);
		goods_delay = 60;
		lifes = 60;
		goods_in_asset = 10;
		break;

	case obstacle::mid_tree:
		NewDims(78.0f, 86.0f);
		goods_delay = 80;
		lifes = 80;
		goods_in_asset = 15;
		break;

	case obstacle::big_tree:
		NewDims(98.0f, 90.0f);
		goods_delay = 90;
		lifes = 100;
		goods_in_asset = 20;
		break;

	case obstacle::mine:
		NewDims(261.0f, 363.0f);
		goods_delay = 100;
		lifes = 3000;
		goods_in_asset = 50;
		max_frames = 124;
		frame_delay = 1;
		break;
	}

	max_frame_delay = frame_delay;
	max_goods_delay = goods_delay;
}
int dll::ASSETS::GetFrame()
{
	frame_delay--;
	if (frame_delay <= 0)
	{
		frame_delay = max_frame_delay;
		++frame;
		if (frame > max_frames)frame = 0;
	}
	return frame;
}
int dll::ASSETS::GetGoods()
{
	if (goods_delay > 0)goods_delay--;
	else
	{
		goods_delay = max_goods_delay;
		lifes--;
		if (lifes <= 0)return goods_in_asset;
	}

	return 0;
}
void dll::ASSETS::Release()
{
	delete this;
}

////////////////////////////////


// UNITS **********************

dll::UNITS::UNITS(unit_type what, float start_x, float start_y)
{
	type = what;

	RANDIT rand_gen{};

	switch (type)
	{
	case unit_type::peon:
		lifes = 50 + rand_gen(0, 20);
		speed = 0.5f + (float)(rand_gen(0, 2)) / 10.0f;
		strenght = 5 + rand_gen(0, 5);
		range = 150.0f;
		max_frames = 40;
		max_frame_delay = 2;
		frame_delay = max_frame_delay;
		attack_delay = 100;
		break;

	case unit_type::orc_warrior:
		lifes = 100 + rand_gen(0, 30);
		speed = 0.8f + (float)(rand_gen(0, 3)) / 10.0f;
		strenght = 25 + rand_gen(0, 5);
		range = 200.0f;
		max_frames = 9;
		max_frame_delay = 7;
		frame_delay = max_frame_delay;
		attack_delay = 80;
		break;

	case unit_type::orc_knight:
		lifes = 100 + rand_gen(0, 30);
		speed = 0.4f + (float)(rand_gen(0, 3)) / 10.0f;
		strenght = 50 + rand_gen(0, 10);
		range = 200.0f;
		max_frames = 30;
		max_frame_delay = 2;
		frame_delay = max_frame_delay;
		attack_delay = 80;
		break;

	case unit_type::orc_archer:
		lifes = 70 + rand_gen(0, 30);
		speed = 0.6f + (float)(rand_gen(0, 3)) / 10.0f;
		strenght = 40 + rand_gen(0, 5);
		range = 250.0f;
		max_frames = 18;
		max_frame_delay = 3;
		frame_delay = max_frame_delay;
		attack_delay = 120;
		break;

	case unit_type::peasant:
		lifes = 50 + rand_gen(0, 20);
		speed = 0.5f + (float)(rand_gen(0, 2)) / 10.0f;
		strenght = 5 + rand_gen(0, 5);
		range = 150.0f;
		max_frames = 19;
		max_frame_delay = 4;
		frame_delay = max_frame_delay;
		attack_delay = 100;
		break;

	case unit_type::warrior:
		lifes = 100 + rand_gen(0, 30);
		speed = 0.8f + (float)(rand_gen(0, 3)) / 10.0f;
		strenght = 25 + rand_gen(0, 5);
		range = 200.0f;
		max_frames = 3;
		max_frame_delay = 10;
		frame_delay = max_frame_delay;
		attack_delay = 80;
		break;

	case unit_type::knight:
		lifes = 100 + rand_gen(0, 30);
		speed = 0.4f + (float)(rand_gen(0, 3)) / 10.0f;
		strenght = 50 + rand_gen(0, 10);
		range = 200.0f;
		max_frames = 24;
		max_frame_delay = 3;
		frame_delay = max_frame_delay;
		attack_delay = 80;
		break;

	case unit_type::archer:
		lifes = 70 + rand_gen(0, 30);
		speed = 0.6f + (float)(rand_gen(0, 3)) / 10.0f;
		strenght = 40 + rand_gen(0, 5);
		range = 250.0f;
		max_frames = 41;
		max_frame_delay = 2;
		frame_delay = max_frame_delay;
		attack_delay = 120;
		break;
	}

	max_attack_delay = attack_delay;
}
void dll::UNITS::SetPath(float _where_x, float _where_y)
{
	hor_path = false;
	vert_path = false;

	start_move_x = start.x;
	start_move_y = start.y;

	final_move_x = _where_x;
	final_move_y = _where_y;

	if (start_move_x < final_move_x)dir = dirs::right;
	else dir = dirs::left;

	if (final_move_x == start_move_x || (final_move_x > start_move_x && final_move_x < end.x))
	{
		vert_path = true;
		return;
	}
	if (final_move_y == start_move_y || (final_move_y > start_move_y && final_move_y < end.y))
	{
		hor_path = true;
		return;
	}

	slope = (final_move_y - start_move_y) / (final_move_x - start_move_x);
	intercept = start_move_y - start_move_x * slope;
}
void dll::UNITS::Release()
{
	delete this;
}
int dll::UNITS::GetFrame()
{
	frame_delay--;
	if (frame_delay <= 0)
	{
		frame_delay = max_frame_delay;
		++frame;
		if (frame > max_frames)frame = 0;
	}
	return frame;
}
void dll::UNITS::Move(float gear, BAG<ASSETS>obstacles)
{
	float now_speed = speed * gear / 10.0f;

	if (vert_path)
	{
		if (start_move_y > final_move_y)
		{
			if (start.y - now_speed >= sky)
			{
				start.y -= now_speed;
				SetEdges();
				return;
			}
		}
		else if (end.y + now_speed <= ground)
		{
			start.y += now_speed;
			SetEdges();
			return;
		}
	}
	if (hor_path)
	{
		if (start_move_x > final_move_x)
		{
			if (start.x - now_speed >= 0)
			{
				start.x -= now_speed;
				SetEdges();
				return;
			}
		}
		else if (end.x + now_speed <= scr_width)
		{
			start.x += now_speed;
			SetEdges();
			return;
		}
	}

	if (start_move_x > final_move_x)
	{
		float next_y = (start.x - now_speed) * slope + intercept;

		if (start.x - now_speed >= 0 && next_y >= sky && next_y + GetHeight() <= ground)
		{
			start.x -= now_speed;
			start.y = start.x * slope + intercept;
			SetEdges();
			return;
		}
	}
	if (start_move_x < final_move_x)
	{
		float next_y = (start.x + now_speed) * slope + intercept;

		if (start.x + now_speed >= 0 && next_y >= sky && next_y + GetHeight() <= ground)
		{
			start.x += now_speed;
			start.y = start.x * slope + intercept;
			SetEdges();
			return;
		}
	}
	
}
int dll::UNITS::Attack()
{
	--attack_delay;
	if (attack_delay <= 0)
	{
		attack_delay = max_attack_delay;
		return strenght;
	}
	return 0;
}

////////////////////////////////

// FUNCTIONS *******************************************

bool dll::Intersect(FRECT first, FRECT second)
{
	if (!(first.up_left.x >= second.up_right.x || first.up_right.x <= second.up_left.x
		|| first.up_left.y >= second.down_left.y || first.down_left.y <= second.up_left.y))return true;

	return false;
}
float dll::Distance(FPOINT first, FPOINT second)
{
	float a = (float)(pow(abs(second.x - first.x), 2));
	float b = (float)(pow(abs(second.y - first.y), 2));

	return (float)(sqrt(a + b));
}
void dll::Sort(BAG<UNITS>& army, FPOINT target)
{
	if (army.size() < 2)return;

	bool is_ok = false;

	while (!is_ok)
	{
		is_ok = true;

		for (size_t count = 0; count < army.size() - 1; ++count)
		{
			if (Distance(army[count].center, target) > Distance(army[count + 1].center, target))
			{
				UNITS temp = army[count];
				army[count] = army[count + 1];
				army[count + 1] = temp;
				is_ok = false;
			}
		}
	}
}


PLATFORM_API dll::ASSETS* dll::AssetFactory(obstacle what, float startx, float starty)
{
	ASSETS* ret{ nullptr };
	ret = new ASSETS(what, startx, starty);

	return ret;
}

PLATFORM_API dll::UNITS* dll::UnitFactory(unit_type what_unit, float startx, float starty)
{
	UNITS* ret{ nullptr };

	ret = new UNITS(what_unit, startx, starty);

	return ret;
}