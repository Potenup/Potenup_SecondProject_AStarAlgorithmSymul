#pragma once

#include "Actor/Actor.h"
#include "MapInfo.h"

class GameBoard : public Actor
{
	public :
		GameBoard(const soun::MapInfo& mInfo);

		virtual ~GameBoard() = default;

		GameBoard(const GameBoard& obj) = delete;

		GameBoard& operator=(const GameBoard& obj) = delete;

		virtual void Draw() override;

		bool IsValidPosition(const Vector2& pos, char c) const;

	private :
		soun::MapInfo mapInfo;

		std::vector<std::vector<bool>> dirtyCheckBoard;

};