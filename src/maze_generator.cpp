#include "maze_generator.hpp"

basic_maze::basic_maze(unsigned height, unsigned width)
{
    auto size = change_size_to_valid(height, width);
    resize_field(size.first, size.second);
    resize_edges(size.first, size.second);
}

std::pair<unsigned, unsigned>
basic_maze::change_size_to_valid(unsigned height, unsigned width)
{
    if (height < 11 || width < 11)
    {
        height = width = 11;
    }
    if (height != width)
    {
        height = width = std::max(height, width);
    }
    if (height % 2 == 0)
    {
        height = ++width;
    }
    return {height, width};
}

void basic_maze::resize_field(unsigned height, unsigned width)
{
    maze_field.resize(height);
    std::for_each(maze_field.begin(), maze_field.end(), [=](auto &row)
                  { row.resize(width); });
}

void basic_maze::resize_edges(unsigned height, unsigned width)
{
    auto h = height / 2 + 1;
    auto w = width / 2 + 1;
    quantity_vertices = h * w;
    quantity_edges = quantity_vertices * 2 - h - w;
    edges.reserve(quantity_edges);
}

basic_maze::~basic_maze()
{
}

void basic_maze::add_edge(point u, point v, int w)
{
    edges.emplace_back(u, v, w);
}

void basic_maze::set_cell(unsigned x, unsigned y, int value)
{
    maze_field.at(y).at(x) = value;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

kruskal::kruskal(unsigned height, unsigned width)
    : basic_maze(height, width), sets(quantity_vertices)
{
}

[[maybe_unused]] std::vector<edge>
kruskal::generate_graph()
{
    std::uniform_int_distribution<unsigned> dist(1, 1000);

    auto set_id = 1;
    auto column_size{maze_field.size() - 1};
    auto row_size{maze_field.at(0).size() - 1};

    for (int y = 1; y < (int)column_size; y += 2)
    {
        for (int x = 1; x < (int)row_size; x += 2)
        {
            if (y + 2 < (int)column_size)
                add_edge(point(x, y, set_id),
                         point(x, y + 2, set_id + column_size / 2),
                         dist(random_engine));
            if (x + 2 < (int)row_size)
                add_edge(point(x, y, set_id),
                         point(x + 2, y, set_id + 1),
                         dist(random_engine));
            ++set_id;
        }
    }
    return edges;
}

void kruskal::generate_maze()
{
    std::sort(edges.begin(), edges.end(), [](edge const &lhs, edge const &rhs)
              { return lhs.weight < rhs.weight; });

    for (auto &rib : edges)
    {
        auto u = rib.first.set;
        auto v = rib.second.set;

        auto set_u = sets.find_set(u);
        auto set_v = sets.find_set(v);

        if (set_u != set_v)
        {
            if (rib.first.x == rib.second.x)
            {
                auto y = std::min(rib.first.y, rib.second.y);
                auto x = rib.first.x;
                for (unsigned j = 0; j < 3; ++j)
                    maze_field[y + j][x] = hole;
            }
            else if (rib.first.y == rib.second.y)
            {
                auto x = std::min(rib.first.x, rib.second.x);
                auto y = rib.first.y;
                for (unsigned j = 0; j < 3; ++j)
                    maze_field[y][x + j] = hole;
            }
            sets.union_sets(set_u, set_v);
        }
    }
}
