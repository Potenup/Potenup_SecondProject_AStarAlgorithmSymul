#include "SymulationLevel.h"
#include "Algorithm/Node.h"

SymulationLevel::SymulationLevel()
	: timer(0.1f)
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

	this->questStartButton_ = new ButtonActor("questStart", Vector2(2, buttonVerticalLoc));
	this->questStartButton_->SetCallback([this]() { ChangeStateToQuesting(); });
	AddActor(questStartButton_);
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
				grid_[y][x] = 0;
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

	this->state_ = SymulationLevel::Questing;

	this->questStartButton_->SetActive(false);
	this->questStartButton_->Destroy();

	Node *startNode = new Node(this->mapInfo_.start_);
	Node *endNode = new Node(this->mapInfo_.end_);

	std::vector<Node*> path = this->astar.FindPath(startNode, endNode, this->grid_, this->questList_, this->astarList_);

	delete startNode;
	delete endNode;

	this->currentQuestIndex_ = 0;
	this->currentAstarIndex_ = 0;

	this->timer.Reset();
}

void SymulationLevel::ChangeStateToOptimizing()
{
	if (this->state_ != SymulationLevel::OptimalReady)
	{
		return;
	}

	this->state_ = SymulationLevel::Optimizing;
}

void SymulationLevel::ChangeStateToReStartSymul()
{
	if (this->state_ != SymulationLevel::RestartReady)
	{
		return;
	}

	throw ;
}

void SymulationLevel::QuestReadyFuc(float deltaTime)
{
	//this->startActor_->Update(deltaTime);
	//this->endActor_->Update(deltaTime);
}

void SymulationLevel::QuestingFuc(float deltaTime)
{
	this->state_ = SymulationLevel::OptimalReady;

	int buttonY = mapInfo_.vertical_ + 2;
	this->optimalStartButton_ = new ButtonActor("", Vector2(2, buttonY));
	this->optimalStartButton_->SetCallback([this]() { this->ChangeStateToOptimizing(); });
	AddActor(this->optimalStartButton_);
}

void SymulationLevel::OptimalReadyFuc(float deltaTime)
{
}

void SymulationLevel::OptimizingFuc(float deltaTime)
{
}

void SymulationLevel::RestartReadyFuc(float deltaTime)
{
}
