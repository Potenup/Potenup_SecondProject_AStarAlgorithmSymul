#include "StartActor.h"
#include "Engine/Engine.h"
#include "Level/SymulationLevel.h"

StartActor::StartActor()
	: DrawableActor("s")
{
	color = Color::Red;
}

void StartActor::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		Vector2 mousePos = Engine::Get().MousePosition();

		SymulationLevel* level = dynamic_cast<SymulationLevel*>(Engine::Get().GetMainLevel());

		if (level && level->IsValidPosition(mousePos, soun::GameObj::road))
		{
			position = mousePos;
		}
	}
}