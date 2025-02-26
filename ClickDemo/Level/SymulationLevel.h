#pragma once

#include "Level/Level.h"
#include "MapInfo.h"
#include "Actor/GameBoard.h"
#include "Actor/StartActor.h"
#include "Actor/EndActor.h"

class SymulationLevel : public Level
{
	enum State
	{
		Ready,
		Quest,
		Start,
	};

	RTTI_DECLARATIONS(SymulationLevel, Level)

	public:
		SymulationLevel();

		virtual ~SymulationLevel();

		SymulationLevel(const SymulationLevel& obj) = delete;

		SymulationLevel& operator=(const SymulationLevel& obj) = delete;

		virtual void Update(float deltaTime) override;

		bool IsValidPosition(const Vector2& pos, char c) const;

		void SetMapInfo(soun::MapInfo& mapInfo);

		State GetState() const;

		void SetState(State newState);

		void SetBoradUnit(int x, int y, char c);

	private:
		

	private:
		State state_ = Ready;
		soun::MapInfo mapInfo_;
		GameBoard* gameBoard_ = nullptr;
		StartActor* startActor_ = nullptr;
		EndActor* endActor_ = nullptr;
};