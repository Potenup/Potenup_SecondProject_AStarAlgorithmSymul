#include "FIleRead/FileReader.h"
#include "ErrorDeliver/ErrorDeliver.h"
#include <iostream>
#include <Windows.h>
#include <io.h>
#include <vector>

namespace soun
{
#pragma region public
	FileReader::FileReader()
	{
		PRINT_MESSAGE(MESSAGE_REQUEST_FILE_NAME);
		std::string filePath;
		std::cin >> filePath;
		ife (_access(filePath.c_str(), 0) == -1)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_FILE_ACCESS));
		}
		this->fileReaderObj_.open(filePath);
		ife (!this->fileReaderObj_.is_open())
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_FILE_OPEN));
		}
	}

	std::vector<std::string> FileReader::MakeStringBox()
	{
		std::string s = this->FileInit();
		std::vector<std::string> box = this->MakeBox(s);
		DEBUG_EXECUTE(this->PrintBox(box));
		return (box);
	}
#pragma endregion

#pragma region private
	std::string FileReader::FileInit()
	{
		std::string s;

		// 위치 지정자를 파일 끝으로 옮긴다.
		this->fileReaderObj_.seekg(0, std::ios::end);
		// 그리고 그 위치를 읽는다. (파일의 크기)
		int size = this->fileReaderObj_.tellg();
		// 그 크기의 문자열을 할당한다.
		s.resize(size);
		// 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
		this->fileReaderObj_.seekg(0, std::ios::beg);
		// 파일 전체 내용을 읽어서 문자열에 저장한다.
		this->fileReaderObj_.read(&s[0], size);

		return (s);
	}

	std::vector<std::string> FileReader::MakeBox(const std::string& s)
	{
		std::vector<std::string> box;

		int totalSize = s.size();

		for (int i = 0; i < totalSize; ++i)
		{
			std::string part = "";
			int j = 0;
			for (j = 0; i + j < totalSize && s[i + j] != '\n'; ++j)
			{
				part.push_back(s[i + j]);
			}
			box.push_back(part);
			i = i + j;
		}
		return (box);
	}
	void FileReader::PrintBox(const std::vector<std::string>& box)
	{
		std::cout << "\n--- PrintBox ---\n" << std::endl;
		for (std::string s : box)
		{
			std::cout << s << std::endl;
		}
	}
#pragma endregion
}