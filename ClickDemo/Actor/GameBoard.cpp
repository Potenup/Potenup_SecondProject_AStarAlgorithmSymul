#include "GameBoard.h"
#include "Engine/Engine.h"

GameBoard::GameBoard(const soun::MapInfo& mInfo)
    : mapInfo(mInfo)
{
    for (int i = 0; i < this->mapInfo.vertical_; ++i) 
    {
        std::vector<bool> part(this->mapInfo.horizontal_, true);
        this->dirtyCheckBoard.push_back(part);
    }
}

void GameBoard::Draw()
{
    this->Actor::Draw();

    using namespace soun;

    for (int y = 0; y < this->mapInfo.vertical_; ++y)
    {
        for (int x = 0; x < this->mapInfo.horizontal_; ++x)
        {
            if (this->dirtyCheckBoard[y][x])
            {
                char c = mapInfo.map_[y][x];
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

            //    this->dirtyCheckBoard[y][x] = false;
            }
        }
    }
}

bool GameBoard::IsValidPosition(const Vector2& pos, char c) const
{
    if (pos.x < 0 || pos.y < 0 || pos.y >= this->mapInfo.vertical_ || pos.x >= this->mapInfo.horizontal_)
        return false;
    return (this->mapInfo.map_[pos.y][pos.x] == c);
}

void GameBoard::ChangeBoardUnit(int x, int y, char c)
{
    using namespace soun;

    this->mapInfo.map_[y][x] = c;

    if (c == GameObj::start)
    {
        this->mapInfo.start_.y = y;
        this->mapInfo.start_.x = x;
    }
    else if (c == GameObj::end)
    {
        this->mapInfo.end_.y = y;
        this->mapInfo.end_.x = x;
    }
}
