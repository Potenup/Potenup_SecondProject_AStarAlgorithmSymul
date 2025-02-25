#pragma once

#include <vector>
#include <string>
#include "Math/Vector2.h"
#include "MapInfo.h"

namespace soun
{
	class MapConverter
	{
		public :
			MapConverter(std::vector<std::string> &box);

			void IsValidMap(MapInfo& mInfo);

			MapInfo CreateMapInfo();
			
		private :
			void FillMapEmpty(MapInfo& mInfo);

			void CheckInGameObj(MapInfo& mInfo);

			void CheckVaildMap(MapInfo& mInfo);

			void MakeMap(MapInfo& mInfo);

			bool QuestNeber(int i, int j, std::vector<std::pair<int, int>>& direct, MapInfo& mInfo);

			void PrintBox();

		private :
			std::vector<std::string>& box_;
	};
}