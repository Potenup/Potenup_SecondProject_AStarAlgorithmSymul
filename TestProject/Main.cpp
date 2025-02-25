#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main()
{
	int M = 0;
	int N = 0;
	cin >> M >> N;

	cin.clear();
	cin.ignore();

	vector<pair<int, int>> cutArea;

	int x = 0;
	int y = 0;
	string s = "";
	getline(cin, s);
	stringstream ss(s);
	while (ss >> y >> x)
	{
		cutArea.push_back({y, x});
	}

	//for (int i = 0; i < cutArea.size(); ++i)
	//{
	//	cout << "(" << cutArea[i].first << ", " << cutArea[i].second << ") ";
	//}
	//std::cout << std::endl;

	
	ss.clear();
	vector<int> foldMethod;
	s = "";
	getline(cin, s);
	ss.str(s);
	int num = 0;
	while (ss >> num)
	{
		foldMethod.push_back(num);
	}

	std::cout << std::endl;

	//for (int i = 0; i < foldMethod.size(); ++i)
	//{
	//	cout << "(" << foldMethod[i] << ") ";
	//}

	for (int flag : foldMethod)
	{
		if (flag == -1)
		{
			M = M / 2;
		}
		else if (flag == 1)
		{
			N = N / 2;
		}
	}

	vector<vector<int>> vec;

	for (int i = 0; i < M; ++i)
	{
		vector<int> part(N, 1);
		vec.push_back(part);
	}

	for (vector<int> part : vec)
	{
		for (int a : part)
		{
			cout << a << " ";
		}
		cout << endl;
	}

	cout << endl;

	for (pair<int, int> cut : cutArea)
	{
		int iy = cut.first;
		int ix = cut.second;
		vec[iy][ix] = 0;
	}

	for (vector<int> part : vec)
	{
		for (int a : part)
		{
			cout << a << " ";
		}
		cout << endl;
	}

	cout << endl;

	reverse(foldMethod.begin(), foldMethod.end());

	for (int i : foldMethod)
	{
		if (i == 1)
		{
			for (vector<int> &part : vec)
			{
				vector<int> cp = part;
				reverse(cp.begin(), cp.end());
				part.insert(part.end(), cp.begin(), cp.end());
			}
		}
		else if (i == -1)
		{
			vector<vector<int>> cp = vec;
			reverse(cp.begin(), cp.end());
			for (vector<int> part : cp)
			{
				vec.push_back(part);
			}
		}

		cout << endl;

		for (vector<int> part : vec)
		{
			for (int a : part)
			{
				cout << a << " ";
			}
			cout << endl;
		}
	}
}
