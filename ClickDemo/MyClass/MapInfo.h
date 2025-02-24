#pragma once

#include <vector>
#include <string>
#include "Math/Vector2.h"
#include "Core.h"

namespace soun
{
	struct MapInfo
	{
		MapInfo(const std::vector<std::string> map, std::pair<int, int> size, Vector2 start, Vector2 end)
			: map_(map), vertical_(size.first), horizontal_(size.second), start_(start), end_(end)
		{
		}

		int vertical_ = 0;
		int horizontal_ = 0;
		Vector2 start_ = { -1. - 1 };
		Vector2 end_ = { -1. - 1 };
		std::vector<std::string> map_;
	};

	struct ObjData
	{
		const char start = 's';
		const char end = 'e';
		const char wall = '1';
		const char road = '0';
		const char empty = ' ';
	};
}