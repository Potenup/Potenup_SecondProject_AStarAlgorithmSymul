#pragma once

#include "Level/Level.h"
#include "MapInfo.h"
#include "Actor/GameBoard.h"
#include "Actor/StartActor.h"
#include "Actor/EndActor.h"
#include "Actor/ButtonActor.h"
#include "Engine/Timer.h"
#include "Algorithm/AStar.h"
#include <functional>

class SymulationLevel : public Level
{
	RTTI_DECLARATIONS(SymulationLevel, Level)

	public:
		enum State
		{
			QuestReady,
			Questing,
			OptimalReady,
			Optimizing,
			RestartReady,
		};

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

		void CreateGrid();

		const int GetMapVertical() const { return (this->mapInfo_.vertical_); }

	public:
		void ChangeStateToQuesting();
		void ChangeStateToOptimizing();
		void ChangeStateToReStartSymul();

	private :
		void QuestReadyFuc(float deltaTime);
		void QuestingFuc(float deltaTime);
		void OptimalReadyFuc(float deltaTime);
		void OptimizingFuc(float deltaTime);
		void RestartReadyFuc(float deltaTime);

	private:
		ButtonActor* questStartButton_ = nullptr;
		ButtonActor* optimalStartButton_ = nullptr;
		ButtonActor* reStartButton_ = nullptr;

	private:
		State state_ = QuestReady;

		void (SymulationLevel::* ptrFunc[5])(float deltaTime);

		soun::MapInfo mapInfo_;
		GameBoard* gameBoard_ = nullptr;
		StartActor* startActor_ = nullptr;
		EndActor* endActor_ = nullptr;

		Timer timer_;

	private :
		std::vector<std::vector<int>> grid_;
		AStar astar_;

		std::vector<std::pair<int, int>> questList_;
		std::vector<std::pair<int, int>> astarList_;

		size_t currentQuestIndex_ = 0;
		size_t currentAstarIndex_ = 0;

		bool flag_ =false;
};