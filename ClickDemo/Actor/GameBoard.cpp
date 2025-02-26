#include "GameBoard.h"
#include "Engine/Engine.h"

GameBoard::GameBoard(soun::MapInfo& mInfo)
    : mapInfo_(mInfo)
{
    for (int i = 0; i < this->mapInfo_.vertical_; ++i) 
    {
        std::vector<bool> part(this->mapInfo_.horizontal_, true);
        this->dirtyCheckBoard_.push_back(part);
    }
}

void GameBoard::Draw()
{
    this->Actor::Draw();

    using namespace soun;

    if (this->dirtyControl_)
    {
        for (int y = 0; y < this->mapInfo_.vertical_; ++y)
        {
            for (int x = 0; x < this->mapInfo_.horizontal_; ++x)
            {
                if (this->dirtyCheckBoard_[y][x])
                {
                    char c = mapInfo_.map_[y][x];
                    Color cColor = Color::White;

                    switch (c)
                    {
                    case GameObj::road:
                        break;
                    case GameObj::wall:
                        cColor = Color::Red;
                        break;
                    case GameObj::empty:
                        cColor = Color::Black;
                        break;
                    case GameObj::hor:
                    case GameObj::ver:
                        cColor = Color::Blue;
                        break;
                    case GameObj::start:
                    case GameObj::end:
                        c = '0';
                    default:
                        break;
                    }

                    char str[2];
                    str[0] = c;
                    str[1] = 0;
                    Engine::Get().Draw(Vector2(x, y), str, cColor);

                    this->dirtyCheckBoard_[y][x] = false;
                }
            }
        }
    }
    this->dirtyControl_ = false;
}

bool GameBoard::IsValidPosition(const Vector2& pos, char c) const
{
    if (pos.x < 0 || pos.y < 0 || pos.y >= this->mapInfo_.vertical_ || pos.x >= this->mapInfo_.horizontal_)
        return false;
    return (this->mapInfo_.map_[pos.y][pos.x] == c);
}

void GameBoard::ChangeBoardUnit(int x, int y, char c)
{
    using namespace soun;

    this->mapInfo_.map_[y][x] = c;
    this->dirtyCheckBoard_[y][x] = true;
    this->dirtyControl_ = true;

    if (c == GameObj::start)
    {
        this->mapInfo_.start_.y = y;
        this->mapInfo_.start_.x = x;
    }
    else if (c == GameObj::end)
    {
        this->mapInfo_.end_.y = y;
        this->mapInfo_.end_.x = x;
    }
}
