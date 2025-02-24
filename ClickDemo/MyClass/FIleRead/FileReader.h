#pragma once
#include <fstream>
#include <vector>
#include <string>

namespace soun
{
	class FileReader
	{
		public:
			FileReader();
			
			std::vector<std::string> MakeStringBox();
		private :
			std::string FileInit();

			std::vector<std::string> MakeBox(const std::string& s);

			void PrintBox(const std::vector<std::string>& box);
		private :
			std::fstream fileReaderObj_;
	};
}