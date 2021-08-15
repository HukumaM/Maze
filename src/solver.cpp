#include "solver.hpp" 

void solver::dijkstra(std::vector<std::vector<int>> &vect, int entrance_y, int entrance_x, int exit_y, int exit_x)
{
	std::vector<distance> distances;
	int distance_cnt = 3;
	distances.push_back({entrance_y, entrance_x});
	bool new_distance = true;
	int y = 0;
	int x = 0;
	while (new_distance)
	{
		new_distance = false;
		int distance_max = distances.size();
		distance_cnt++;
		for (int i = 0; i < distance_max; i++)
		{
			y = distances[0].y;
			x = distances[0].x;
			vect[y][x] = distance_cnt;
			if (y > 0 && hole == vect[y - 1][x])
			{
				distances.push_back({y - 1, x});
				new_distance = true;
			}
			if (y + 1 < (int)vect.size() && hole == vect[y + 1][x])
			{
				distances.push_back({y + 1, x});
				new_distance = true;
			}
			if (x > 0 && hole == vect[y][x - 1])
			{
				distances.push_back({y, x - 1});
				new_distance = true;
			}
			if (x + 1 < (int)vect[0].size() && hole == vect[y][x + 1])
			{
				distances.push_back({y, x + 1});
				new_distance = true;
			}
			if (y == exit_y && x == exit_x)
			{
				new_distance = false;
				break;
			}
			distances.erase(distances.begin());
		}
	}
	y = exit_y;
	x = exit_x;
	distance_cnt = vect[y][x];
	while (3 != distance_cnt)
	{
		vect[y][x] = solution;
		distance_cnt--;
		if (y > 0 && distance_cnt == vect[y - 1][x])
		{
			y--;
		}
		else if (y + 1 < (int)vect.size() && distance_cnt == vect[y + 1][x])
		{
			y++;
		}
		else if (x > 0 && distance_cnt == vect[y][x - 1])
		{
			x--;
		}
		else if (x + 1 < (int)vect[0].size() && distance_cnt == vect[y][x + 1])
		{
			x++;
		}
	}
	for (int y = 0; y < (int)vect.size(); y++)
	{
		for (int x = 0; x < (int)vect[y].size(); x++)
		{
			if (wall != vect[y][x] && solution != vect[y][x])
			{
				vect[y][x] = hole;
			}
		}
	}
}

