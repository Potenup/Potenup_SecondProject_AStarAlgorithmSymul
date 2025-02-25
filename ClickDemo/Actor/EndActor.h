#pragma once

#include "Actor/DrawableActor.h"

class EndActor : public DrawableActor
{
	RTTI_DECLARATIONS(EndActor, DrawableActor)

public:
	EndActor();

	virtual ~EndActor() = default;

	EndActor(const EndActor& obj) = delete;

	EndActor& operator=(const EndActor& obj) = delete;

	virtual void Update(float deltaTime) override;
};