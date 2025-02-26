#pragma once

#include "Actor/DrawableActor.h"

class StartActor : public DrawableActor
{
	RTTI_DECLARATIONS(StartActor, DrawableActor)

	public :
		StartActor();
	
		virtual ~StartActor() = default;
	
		StartActor(const StartActor& obj) = delete;
	
		StartActor& operator=(const StartActor& obj) = delete;
	
		virtual void Draw() override;
	
		virtual void Update(float deltaTime) override;
	private :
		bool dirtyFlag_ = true;
};