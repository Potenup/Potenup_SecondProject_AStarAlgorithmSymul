#pragma once

#include <vector>
#include <string>
#include "Math/Vector2.h"

namespace soun
{
	class MapMaker
	{
		
		public :
			MapMaker(std::vector<std::string> box);

			void MakeMap();
			
		private :
			std::pair<Vector2, Vector2> IsPossibleMap();

			void MapObjAnalyze(Vector2& start, Vector2& end);

			void MapCheckPossible();
		

		private :
			const std::vector<std::string>& box_;
	};
}