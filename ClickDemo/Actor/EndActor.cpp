#include "EndActor.h"
#include "Engine/Engine.h"
#include "Level/SymulationLevel.h"
EndActor::EndActor()
	: DrawableActor("e")
{
	color = Color::Green;
}

void EndActor::Draw()
{
	if (this->dirtyFlag_)
	{
		Super::Draw();
		this->dirtyFlag_ = false;
	}
		
}

void EndActor::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		Vector2 mousePos = Engine::Get().MousePosition();

		SymulationLevel* level = dynamic_cast<SymulationLevel*>(Engine::Get().GetMainLevel());

		if (level && level->GetState() == SymulationLevel::State::QuestReady && level->IsValidPosition(mousePos, soun::GameObj::road))
		{
			level->SetBoradUnit(position.x, position.y, '0');
			position = mousePos;
			level->SetBoradUnit(position.x, position.y, 'e');
			this->dirtyFlag_ = true;
		}
	}
}