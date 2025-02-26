#include "ButtonActor.h"
#include "Engine/Engine.h"

ButtonActor::ButtonActor(const char* message, const Vector2& pos)
	: DrawableActor(message)
{
	this->position = pos;
	this->color = Color::White;
}

void ButtonActor::Update(float deltaTime)
{
	Super::Update(deltaTime);

	Vector2 mousePos = Engine::Get().MousePosition();

	this->isHovered_ = (mousePos.y == position.y && (mousePos.x >= position.x && mousePos.x < position.x + width));

	color = this->isHovered_ ? Color::Yellow : Color::White;

	if (this->isHovered_ && Engine::Get().GetKeyDown(VK_LBUTTON) && this->buttonCallback_)
	{
		this->buttonCallback_();
	}
}

void ButtonActor::SetCallback(ButtonCallback buttonCallback)
{
	this->buttonCallback_ = buttonCallback;
}
