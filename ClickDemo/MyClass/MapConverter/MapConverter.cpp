#include "MapConverter.h"
#include "ErrorDeliver/ErrorDeliver.h"

namespace soun
{
	MapConverter::MapConverter(std::vector<std::string>& box)
		: box_(box)
	{
	}

	void MapConverter::IsValidMap(MapInfo& mInfo)
	{
		
		this->FillMapEmpty(mInfo);
		this->CheckInGameObj(mInfo);
		this->MakeMap(mInfo);
		this->CheckVaildMap(mInfo);
		mInfo.map_ = this->box_;
		DEBUG_EXECUTE(this->PrintBox());
	}

	 MapInfo MapConverter::CreateMapInfo()
	 {
		 MapInfo mInfo;
		 this->IsValidMap(mInfo);
		 return mInfo;
	 }

	void MapConverter::FillMapEmpty(MapInfo& mInfo)
	{
		int maxLen = 0;
		for (std::string& s : this->box_)
		{
			std::cout << s.size() << std::endl;
			maxLen = max(maxLen, s.size());
		}
		

		for (std::string& s : this->box_)
		{
			std::cout << maxLen - s.size() << std::endl;
			std::string k(maxLen - s.size(), '2');
			s = s + k;
		}

		mInfo.horizontal_ = this->box_[0].size();
		mInfo.vertical_ = this->box_.size();

		DEBUG_EXECUTE(PrintBox());
	}

	void MapConverter::CheckInGameObj(MapInfo& mInfo)
	{
		for (int i = 0; i < this->box_.size(); ++i)
		{
			for (int j = 0; j < this->box_[0].size(); ++j)
			{
				char c = this->box_[i][j];
				if (c == GameObj::start)
				{
					mInfo.start_.y = i;
					mInfo.start_.x = j;
					mInfo.startCount = mInfo.startCount + 1;
					if (mInfo.startCount == 2)
						return;
				}
				else if (c == GameObj::end)
				{
					mInfo.end_.y = i;
					mInfo.end_.x = j;
					mInfo.endCount = mInfo.endCount + 1;
					if (mInfo.endCount == 2)
						return;
				}
				else if (c == GameObj::road)
				{
					mInfo.roadCount = mInfo.roadCount + 1;
				}
				else if (c == GameObj::wall)
				{
					mInfo.wallCount = mInfo.wallCount + 1;
				}
				else if (c == GameObj::empty)
				{
					mInfo.emptyCount = mInfo.emptyCount + 1;
				}
				else if (c == GameObj::space)
				{
					mInfo.emptyCount = mInfo.emptyCount + 1;
					this->box_[i][j] = '2';
				}
				else 
				{
					mInfo.worngCount = mInfo.worngCount + 1;
					return ;
				}
			}
		}
	}

	void MapConverter::CheckVaildMap(MapInfo& mInfo)
	{
		ife(mInfo.horizontal_ > 80 || mInfo.vertical_ > 60)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_MAPSIZE_OVERSIZE));
		}
		ife(mInfo.horizontal_ < 6 || mInfo.vertical_ < 6)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_MAPSIZE_SMALLSIZE));
		}
		ife(mInfo.endCount > 1)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_END_OVERCOUNT));
		}
		ife(mInfo.startCount > 1)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_START_OVERCOUNT));
		}
		ife(mInfo.endCount == 0)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_END_UNEXIST));
		}
		ife(mInfo.startCount == 0)
		{
			DEBUG_BREAK();
			throw (new ErrorDeliver(ERROR_START_UNEXIST));
		}

		using pr = std::pair<int, int>;

		std::vector<pr> direct{{1, 0}, {0, 1}};

		for (int i = 0; i < this->box_.size(); ++i)
		{
			for (int j = 0; j < this->box_[0].size(); ++j)
			{
				if (this->QuestNeber(i, j, direct, mInfo) == false)
				{
					DebugBreak();
					throw(new ErrorDeliver(ERROR_MAP_NOTVALID));
				}
			}
		}
	}

	void MapConverter::MakeMap(MapInfo& mInfo)
	{
		for (std::string &s : this->box_)
		{
			s.insert(s.begin(), '|');
			s.push_back('|');
		}

		mInfo.horizontal_ = mInfo.horizontal_ + 2;
		mInfo.vertical_ = mInfo.vertical_ + 2;

		std::string front(mInfo.horizontal_, '-');
		this->box_.insert(this->box_.begin(), front);
		this->box_.push_back(front);
		mInfo.start_.x = mInfo.start_.x + 1;
		mInfo.start_.y = mInfo.start_.y + 1;
		mInfo.end_.x = mInfo.end_.x + 1;
		mInfo.end_.y = mInfo.end_.y + 1;
	}

	bool MapConverter::QuestNeber(int i, int j, std::vector<std::pair<int, int>>& direct, MapInfo& mInfo)
	{
		using pr = std::pair<int, int>;
		char c = this->box_[i][j];
		for (pr p : direct)
		{
			int nextY = i + p.first;
			int nextX = j + p.second;
			if (c == GameObj::hor || c == GameObj::ver)
			{
				if (nextX >= mInfo.horizontal_ || nextY >= mInfo.vertical_)
					continue;
				else if (this->box_[nextY][nextX] == '0' || this->box_[nextY][nextX] == 's' || this->box_[nextY][nextX] == 'e')
					return (false);
			}
			else if (c == GameObj::start)
			{
				if (this->box_[nextY][nextX] != '0' && this->box_[nextY][nextX] != 'e' && this->box_[nextY][nextX] != '1')
					return (false);
			}
			else if (c == GameObj::end)
			{
				if (this->box_[nextY][nextX] != '0' && this->box_[nextY][nextX] != 's' && this->box_[nextY][nextX] != '1')
					return (false);
			}
			else if (c == GameObj::road)
			{
				if (this->box_[nextY][nextX] == '2' || this->box_[nextY][nextX] == '|' || this->box_[nextY][nextX] == '-')
					return (false);
			}
			else if (c == GameObj::empty)
			{
				if (this->box_[nextY][nextX] == '0' || this->box_[nextY][nextX] == 's' || this->box_[nextY][nextX] == 'e')
					return (false);
			}
		}
		return (true);
	}

	void MapConverter::PrintBox()
	{
		for (std::string& s : this->box_)
		{
			std::cout << s << std::endl;
		}
	}
}