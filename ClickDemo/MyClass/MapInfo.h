#pragma once

#include <vector>
#include <string>
#include "Math/Vector2.h"
#include "Core.h"

namespace soun
{
	struct MapInfo
	{
		MapInfo()
		{
		}

		MapInfo(const std::vector<std::string> map, std::pair<int, int> size, Vector2 start, Vector2 end)
			: map_(map), vertical_(size.first), horizontal_(size.second), start_(start), end_(end)
		{
		}

		int vertical_ = 0;
		int horizontal_ = 0;
		Vector2 start_ = { -1, -1 };
		Vector2 end_ = { -1, -1 };
		std::vector<std::string> map_;
		struct
		{
			int wallCount = 0;
			int roadCount = 0;
			int startCount = 0;
			int endCount = 0;
			int emptyCount = 0;
			int worngCount = 0;
		};
	};

	struct GameObj
	{
		static const char start = 's';
		static const char end = 'e';
		static const char road = '0';
		static const char wall = '1';
		static const char empty = '2';
		static const char space = ' ';
		static const char hor = '|';
		static const char ver = '-';
	};
}