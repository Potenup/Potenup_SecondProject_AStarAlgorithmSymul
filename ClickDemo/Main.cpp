#include "Engine/Engine.h"
#include "ErrorDeliver/ErrorDeliver.h"
#include "FIleRead/FileReader.h"
#include "MapConverter/MapConverter.h"
#include "MapInfo.h"
#include "vector"

using namespace soun;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	try {
		FileReader fileReader;
		std::vector<std::string> box = fileReader.MakeStringBox();
		MapConverter mapConverter(box);
		MapInfo mInfo = mapConverter.CreateMapInfo();
		Engine engine;
		//engine.LoadLevel(new DemoLevel());
		//engine.Run();
	}
	catch (const ErrorDeliver *ErrorObj)
	{
		system("cls");
		std::cout << ErrorObj->GetErrorMessage() << std::endl;
		delete ErrorObj;
	}
	std::cin.get();

}