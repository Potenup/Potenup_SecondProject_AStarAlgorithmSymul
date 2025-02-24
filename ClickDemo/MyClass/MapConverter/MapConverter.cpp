#include "MapConverter.h"

namespace soun
{
	MapMaker::MapMaker(std::vector<std::string> box)
		: box_(box)
	{
	}

	void MapMaker::MakeMap()
	{
	}

	std::pair<Vector2, Vector2> MapMaker::IsPossibleMap()
	{
		return std::pair<Vector2, Vector2>();
	}

	void MapMaker::MapObjAnalyze(Vector2& start, Vector2& end)
	{
	}

	void MapMaker::MapCheckPossible()
	{
	}

}