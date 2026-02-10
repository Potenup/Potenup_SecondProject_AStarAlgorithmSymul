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

    const int totalCells = this->mapInfo_.horizontal_ * this->mapInfo_.vertical_;
    int drawThisFrame = 0;
    using namespace soun;

    if (this->dirtyControl_)
    {
        for (int y = 0; y < this->mapInfo_.vertical_; ++y)
        {
            for (int x = 0; x < this->mapInfo_.horizontal_; ++x)
            {
                if (this->dirtyCheckBoard_[y][x])
                {
                    drawThisFrame++;

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
                        break;
                    case GameObj::questRoad:
                        cColor = Color::Yellow;
                        c = '0';
                        break;
                    case GameObj::AstarRoad:
                        cColor = Color::Green;
                        c = '0';
                        break;
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

    if (this->dirtyControl_)
    {
        const bool isFirstFullDraw = (frameCount_ == 0 && drawThisFrame == totalCells);
        if (!isFirstFullDraw)
        {
            frameCount_++;
            drawCellsSum_ += drawThisFrame;
            totalCellsSum_ += totalCells;
        }
    }

    this->dirtyControl_ = false;

    const int statY = this->mapInfo_.vertical_;

    // 한줄 초기화 문자열.
    const int clearLen = Engine::Get().ScreenSize().x;
    std::string clearLine(clearLen, ' ');
    Engine::Get().Draw(Vector2(0, statY), clearLine.c_str(), Color::Black);

    char buf[41] = { 0 };
    if (frameCount_ > 0)
    {
        const double avgDraw = (double)drawCellsSum_ / (double)frameCount_;
        const double avgTotal = (double)totalCellsSum_ / (double)frameCount_;
        const double reduction = (avgTotal > 0.0) ? (1.0 - (avgDraw / avgTotal)) * 100.0 : 0.0;

        const long long avgDrawRounded = (long long)(avgDraw + 0.5);
        std::snprintf(buf, sizeof(buf), "DirtyAvg:%lld/%d %4.1f%%", avgDrawRounded, totalCells, reduction);
    }
    else
    {
        std::snprintf(buf, sizeof(buf), "DirtyAvg:-");
    }

    Engine::Get().Draw(Vector2(0, statY), buf, Color::White);
}

bool GameBoard::IsValidPosition(const Vector2& pos, char c) const
{
    if (pos.x < 0 || pos.y < 0 || pos.y >= this->mapInfo_.vertical_ || pos.x >= this->mapInfo_.horizontal_)
        return false;
    
    const char cur = this->mapInfo_.map_[pos.y][pos.x];

    if (this->mapInfo_.map_[pos.y][pos.x] == soun::GameObj::road)
    {
        return (cur == soun::GameObj::road || cur == soun::GameObj::questRoad || cur == soun::GameObj::AstarRoad);
    }

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
