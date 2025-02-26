#include "StartActor.h"
#include "Engine/Engine.h"
#include "Level/SymulationLevel.h"

StartActor::StartActor()
	: DrawableActor("s")
{
	color = Color::Green;
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
			level->SetBoradUnit(position.x, position.y, '0');
			position = mousePos;
			level->SetBoradUnit(position.x, position.y, 's');
		}
	}
}