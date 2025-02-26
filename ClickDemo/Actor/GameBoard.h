#pragma once

#include "Actor/Actor.h"
#include "MapInfo.h"

class GameBoard : public Actor
{
	public :
		GameBoard(soun::MapInfo& mInfo);

		virtual ~GameBoard() = default;

		GameBoard(const GameBoard& obj) = delete;

		GameBoard& operator=(const GameBoard& obj) = delete;

		virtual void Draw() override;

		bool IsValidPosition(const Vector2& pos, char c) const;

		void ChangeBoardUnit(int x, int y, char c);

	private :
		soun::MapInfo& mapInfo_;

		std::vector<std::vector<bool>> dirtyCheckBoard_;

		bool dirtyControl_ = true;
};