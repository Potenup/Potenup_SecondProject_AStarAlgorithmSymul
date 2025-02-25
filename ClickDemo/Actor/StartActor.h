#pragma once

#include "Actor/DrawableActor.h"

class StartActor : public DrawableActor
{
public:
	StartActor();

	virtual ~StartActor() = default;

	StartActor(const StartActor& obj) = delete;

	StartActor& operator=(const StartActor& obj) = delete;

	virtual void Update(float deltaTime) override;
};