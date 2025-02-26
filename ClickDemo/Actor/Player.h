#pragma once

#include "Actor/Actor.h"

class Player : public Actor
{
	RTTI_DECLARATIONS(Player, Actor)
	public :
		Player(bool& key);

		virtual ~Player();

		Player(const Player& obj) = delete;

		Player& operator=(const Player& obj) = delete;

		virtual void Update(float deltaTime) override;
	private :
		bool& key_;
		bool flag_ = false;
		int vertical_ = 0;
};