#include "Engine/Engine.h"
#include "ErrorDeliver/ErrorDeliver.h"
#include "FIleRead/FileReader.h"
#include "MapConverter/MapConverter.h"
#include "Level/SymulationLevel.h"
#include "Actor/Player.h"
#include "MapInfo.h"
#include "vector"

using namespace soun;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool reStart = true;

	while (reStart)
	{
		system("cls");
		try {
			FileReader fileReader;
			std::vector<std::string> box = fileReader.MakeStringBox();
			MapConverter mapConverter(box);
			MapInfo mInfo = mapConverter.CreateMapInfo();
			SymulationLevel* symulationLevel = new SymulationLevel();
			symulationLevel->AddActor(new Player(reStart));
			symulationLevel->SetMapInfo(mInfo);
			Engine engine;
			engine.LoadLevel(symulationLevel);
			engine.Run();
		}
		catch (const ErrorDeliver* ErrorObj)
		{
			system("cls");
			std::cout << ErrorObj->GetErrorMessage() << std::endl;
			delete ErrorObj;
			std::cin.ignore();
			std::cin.clear();
			std::cin.get();
		}
	}
	
	std::cin.get();
}