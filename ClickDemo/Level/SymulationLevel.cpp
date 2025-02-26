#include "SymulationLevel.h"
#include "Algorithm/Node.h"
#include "Engine/Engine.h"

SymulationLevel::SymulationLevel()
	: timer_(0.1f)
{
	ptrFunc[0] = &SymulationLevel::QuestReadyFuc;
	ptrFunc[1] = &SymulationLevel::QuestingFuc;
	ptrFunc[2] = &SymulationLevel::OptimalReadyFuc;
	ptrFunc[3] = &SymulationLevel::OptimizingFuc;
	ptrFunc[4] = &SymulationLevel::RestartReadyFuc;
}

SymulationLevel::~SymulationLevel()
{
}

void SymulationLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);
	
	(this->*ptrFunc[this->state_])(deltaTime);
}

bool SymulationLevel::IsValidPosition(const Vector2& pos, char c) const
{
	if (this->gameBoard_ && this->gameBoard_->IsValidPosition(pos, c) == true)
		return (true);
	return (false);
}

void SymulationLevel::SetMapInfo(soun::MapInfo& mapInfo)
{
	this->mapInfo_ = mapInfo;
	this->gameBoard_ = new GameBoard(this->mapInfo_);
	AddActor(this->gameBoard_);

	this->startActor_ = new StartActor();
	this->startActor_->SetPosition(this->mapInfo_.start_);
	AddActor(this->startActor_);

	this->endActor_ = new EndActor();
	this->endActor_->SetPosition(this->mapInfo_.end_);
	AddActor(this->endActor_);

	int buttonVerticalLoc = mapInfo.vertical_ + 2;

	this->questStartButton_ = new ButtonActor(MESSAGE_QUEST_START, Vector2(2, buttonVerticalLoc));
	this->questStartButton_->SetCallback([this]() { ChangeStateToQuesting(); });
	AddActor(questStartButton_);

	this->CreateGrid();
}

SymulationLevel::State SymulationLevel::GetState() const
{
	return (this->state_);
}

void SymulationLevel::SetState(State newState)
{
	this->state_ = newState;
}

void SymulationLevel::SetBoradUnit(int x, int y, char c)
{
	this->gameBoard_->ChangeBoardUnit(x, y, c);
}

void SymulationLevel::CreateGrid()
{
	for (int y = 0; y < this->mapInfo_.vertical_; ++y)
	{
		std::vector<int> part(this->mapInfo_.horizontal_, 1);
		for (int x = 0; x < this->mapInfo_.horizontal_; ++x)
		{
			char c = this->mapInfo_.map_[y][x];
			if (c == soun::GameObj::road || c == soun::GameObj::start || c == soun::GameObj::end)
			{
				part[x] = 0;
			}
		}
		this->grid_.push_back(part);
	}
}

void SymulationLevel::ChangeStateToQuesting()
{
	if (this->state_ != SymulationLevel::QuestReady)
	{
		return ;
	}
	int buttonY = mapInfo_.vertical_ + 2;
	Engine::Get().Draw(Vector2(0, buttonY), MESSAGE_CLEAR, Color::Black);

	this->state_ = SymulationLevel::Questing;

	this->questStartButton_->SetActive(false);

	Node *startNode = new Node(this->mapInfo_.start_);
	Node *endNode = new Node(this->mapInfo_.end_);

	std::vector<Node*> path = this->astar_.FindPath(startNode, endNode, this->grid_, this->questList_, this->astarList_);

	if (!this->questList_.empty())
	{
		std::vector<std::pair<int, int>> v(this->questList_.begin() + 1, this->questList_.end());
		this->questList_ = v;
	}

	if (this->astarList_.size() >= 2)
	{
		std::vector<std::pair<int, int>> v(this->astarList_.begin() + 1, this->astarList_.end() - 1);
		this->astarList_ = v;
	}

	delete endNode;
	endNode = nullptr;

	this->currentQuestIndex_ = 0;
	this->currentAstarIndex_ = 0;

	this->timer_.Reset();
}

void SymulationLevel::ChangeStateToOptimizing()
{
	if (this->state_ != SymulationLevel::OptimalReady)
	{
		return;
	}
	int buttonY = mapInfo_.vertical_ + 2;
	Engine::Get().Draw(Vector2(0, buttonY), MESSAGE_CLEAR, Color::Black);

	this->optimalStartButton_->SetActive(false);
	
	this->state_ = SymulationLevel::Optimizing;
}

void SymulationLevel::ChangeStateToReStartSymul()
{
	if (this->state_ != SymulationLevel::RestartReady)
	{
		return;
	}
	int buttonY = mapInfo_.vertical_ + 2;
	Engine::Get().Draw(Vector2(0, buttonY), MESSAGE_CLEAR, Color::Black);

	this->reStartButton_->SetActive(false);

	Engine::Get().QuitGame();
}

void SymulationLevel::QuestReadyFuc(float deltaTime)
{
	return ;
}

void SymulationLevel::QuestingFuc(float deltaTime)
{
	this->timer_.Update(deltaTime);

	if (this->timer_.IsTimeOut())
	{
		if (this->currentQuestIndex_ < this->questList_.size())
		{
			Vector2 pos(this->questList_[this->currentQuestIndex_].first, this->questList_[this->currentQuestIndex_].second);

			Engine::Get().Draw(pos, "0", Color::Yellow);

			this->currentQuestIndex_ = this->currentQuestIndex_ + 1;

			this->timer_.Reset();
		}
		else 
		{
			if (this->astarList_.empty())
			{
				this->state_ = SymulationLevel::RestartReady;
				int buttonY = mapInfo_.vertical_ + 1;
				Engine::Get().Draw(Vector2(1, buttonY), MESSAGE_IMPOSSIBLE, Color::Red);
				this->reStartButton_ = new ButtonActor(MESSAGE_RESTART, Vector2(2, buttonY + 2));
				this->reStartButton_->SetCallback([this]() { this->ChangeStateToReStartSymul(); });
				AddActor(this->reStartButton_);
			}
			else
			{
				this->state_ = SymulationLevel::OptimalReady;

				int buttonY = mapInfo_.vertical_ + 2;
				this->optimalStartButton_ = new ButtonActor(MESSAGE_OPTIAML_START, Vector2(2, buttonY));
				this->optimalStartButton_->SetCallback([this]() { this->ChangeStateToOptimizing(); });
				AddActor(this->optimalStartButton_);
			}
		}
	}
}

void SymulationLevel::OptimalReadyFuc(float deltaTime)
{
	//int buttonY = mapInfo_.vertical_ + 2;
	//Engine::Get().Draw(Vector2(2, buttonY), "Optimizing..", Color::White);
}

void SymulationLevel::OptimizingFuc(float deltaTime)
{
	this->timer_.Update(deltaTime);

	if (this->timer_.IsTimeOut())
	{
		if (this->currentAstarIndex_ < this->astarList_.size())
		{
			Vector2 pos(this->astarList_[this->currentAstarIndex_].first, this->astarList_[this->currentAstarIndex_].second);

			Engine::Get().Draw(pos, "0", Color::Green);

			this->currentAstarIndex_ = this->currentAstarIndex_ + 1;

			this->timer_.Reset();
		}
		else
		{
			this->state_ = SymulationLevel::RestartReady;

			int buttonY = mapInfo_.vertical_ + 2;
			this->reStartButton_ = new ButtonActor(MESSAGE_RESTART, Vector2(2, buttonY));
			this->reStartButton_->SetCallback([this]() { this->ChangeStateToReStartSymul(); });
			AddActor(this->reStartButton_);
		}
	}
}
void SymulationLevel::RestartReadyFuc(float deltaTime)
{
	return ;
}
