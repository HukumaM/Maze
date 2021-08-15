#pragma once

#include <vector>

#include "maze_generator.hpp"

class solver
{
public:
	void dijkstra(std::vector<std::vector<int>> &vect,
				  int entrance_y, int entrance_x,
				  int exit_y, int exit_x);

private:
	static constexpr int wall = basic_maze::wall;
	static constexpr int hole = basic_maze::hole;
	static constexpr int solution = basic_maze::solution;
	struct distance
	{
		int y;
		int x;
	};
};
