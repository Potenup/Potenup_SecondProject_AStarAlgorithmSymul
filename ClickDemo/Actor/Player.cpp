#include "Player.h"
#include "Engine/Engine.h"
#include "Level/SymulationLevel.h"

Player::Player(bool& key)
	: key_(key)
{
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		this->key_ = false;
		Engine::Get().QuitGame();
	}
	if (Engine::Get().GetKeyDown(0x32))
	{
		this->flag_ = !this->flag_;
		SymulationLevel* level = dynamic_cast<SymulationLevel*>(Engine::Get().GetMainLevel());
		if (level)
		{
			this->vertical_ = level->GetMapVertical();
			Engine::Get().Draw(Vector2(1, this->vertical_), MESSAGE_CLEAR, Color::White);
		}
	}
	if (this->flag_)
	{
		Engine::Get().Draw(Vector2(1, this->vertical_), MESSAGE_CLEAR, Color::White);
		char buffer[50];
		Vector2 mousePosition = Engine::Get().MousePosition();
		sprintf_s(buffer, "Mouse: (%d,%d) Left: %d Right: %d", mousePosition.x, mousePosition.y, Engine::Get().GetKey(VK_LBUTTON), Engine::Get().GetKey(VK_RBUTTON));
		Engine::Get().Draw(Vector2(1, this->vertical_), buffer, Color::White);
	}
}


