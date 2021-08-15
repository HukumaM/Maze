
#include "file_system.hpp"
#include "maze_generator.hpp"
#include "solver.hpp"

#include <iostream>

void show_usage(const std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)>\n"
              << "Options:\n"
              << "\t-h, --help\t\tShow help message\n"
              << "\t-s, --size\t\tSet the dimensions of the maze\n"
              << "\t-p, --path\t\tSet the path for the final images of the maze\n"
              << "\t--start-finish\t\tSet the start and end point of the path\n"
              << std::endl;
}

void show_result(std::string path, unsigned size,
                 unsigned x0, unsigned y0,
                 unsigned x1, unsigned y1)
{
    std::cerr << "\nPath to final images: " << path
              << "\nMaze size: " << size << "x" << size
              << "\nStarting point: x - " << x0 << ", y - " << y0
              << "\nFinal point: x - " << x1 << ", y - " << y1
              << std::endl;
}

int main(int argc, char *argv[])
{
    unsigned size = 11;
    unsigned start_x = 1, start_y = 1;
    unsigned finish_x = size - 2, finish_y = size - 2;

    std::random_device random_engine;

    std::string path = "results/";

    if (argc < 2)
    {
        show_usage(argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            show_usage(argv[0]);
            return 0;
        }
        if (arg == "-s" || arg == "--size")
        {
            size = static_cast<unsigned>(std::atoi(argv[i + 1]));
            finish_x = finish_y = size - 2;
        }
        if (arg == "--start-finish")
        {
            if (i + 4 <= argc)
            {
                start_x = static_cast<unsigned>(std::atoi(argv[i + 1]));
                start_y = static_cast<unsigned>(std::atoi(argv[i + 2]));
                finish_x = static_cast<unsigned>(std::atoi(argv[i + 3]));
                finish_y = static_cast<unsigned>(std::atoi(argv[i + 4]));
            }
        }
        if (arg == "-p" || arg == "--path")
        {
            path = argv[i + 1];
        }
    }
    auto temp = std::to_string(random_engine());
    auto path_to_maze = path + "maze_" + temp + ".png";
    auto path_to_solve = path + "maze_solve_" + temp + ".png";

    kruskal kmaze(size, size);

    auto graph = kmaze.generate_graph();

    kmaze.set_cell(start_x, start_y, kruskal::hole);
    kmaze.set_cell(finish_x, finish_y, kruskal::hole);

    kmaze.generate_maze();

    auto maze = kmaze.get_maze();

    file_system fs;
    fs.save(maze, path_to_maze);

    solver s;
    s.dijkstra(maze, start_x, start_y, finish_x, finish_y);
    fs.save(maze, path_to_solve);

    show_result(path_to_maze, size, start_x, start_y, finish_x, finish_y);

    system(std::string("eog " + path_to_maze + " " + path_to_solve).c_str());
    return 0;
}