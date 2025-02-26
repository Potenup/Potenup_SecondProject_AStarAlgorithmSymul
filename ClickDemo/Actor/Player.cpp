#include "Player.h"
#include "Engine/Engine.h"

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
}

