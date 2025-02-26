#pragma once

#include "Actor/DrawableActor.h"
#include <functional>

class ButtonActor : public DrawableActor
{
	public :
		ButtonActor(const char* message, const Vector2& pos);

		virtual ~ButtonActor() = default;

		ButtonActor(const ButtonActor& obj) = delete;

		ButtonActor& operator=(const ButtonActor& obj) = delete;

		virtual void Update(float deltaTime) override;

		using ButtonCallback = std::function<void()>;

		void SetCallback(ButtonCallback buttonCallback);

	private :
		ButtonCallback buttonCallback_;
		bool isHovered_ = false;
};