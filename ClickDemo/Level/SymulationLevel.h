#pragma once

#include "Level/Level.h"
#include "MapInfo.h"
#include "Actor/GameBoard.h"
#include "Actor/StartActor.h"
#include "Actor/EndActor.h"


class SymulationLevel : public Level
{
	RTTI_DECLARATIONS(SymulationLevel, Level)

	public:
		SymulationLevel();

		virtual ~SymulationLevel() = default;

		SymulationLevel(const SymulationLevel& obj) = delete;

		SymulationLevel& operator=(const SymulationLevel& obj) = delete;

		bool IsValidPosition(const Vector2& pos, char c) const;
	private:
	
	private:
		soun::MapInfo mapInfo;
		GameBoard* GameBoard = nullptr;
		StartActor* startActor = nullptr;
		EndActor* playerActor = nullptr;
};