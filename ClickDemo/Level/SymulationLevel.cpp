#include "SymulationLevel.h"

SymulationLevel::SymulationLevel()
{

}

SymulationLevel::~SymulationLevel()
{
}

void SymulationLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (this->state_ == State::Ready)
	{
		this->startActor_->Update(deltaTime);
		this->endActor_->Update(deltaTime);
	}
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
