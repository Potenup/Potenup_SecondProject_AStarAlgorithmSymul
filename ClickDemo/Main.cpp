#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "ErrorController/ErrorController.h"
#include "FIleRead/FileReader.h"
#include "vector"

using namespace soun;

int main()
{
	try {
		ErrorController errorController;
		FileReader fileReader;
		std::vector<std::string> box = fileReader.MakeStringBox();
		Engine engine;
		engine.LoadLevel(new DemoLevel());
		engine.Run();
	}
	catch (const char* errorMessage)
	{
		system("cls");
		std::cout << errorMessage << std::endl;
		std::cin.get();
	}
	std::cin.get();

}