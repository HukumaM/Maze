#pragma once

#include <random>
#include <algorithm>

#include "edge.hpp"
#include "disjoint_sets.hpp"

/**
 *   @brief The abstract maze generator class 
*/
class basic_maze
{
public:
    /**
     *  @brief An enumeration to denote the cells of the maze field
    */
    enum state_cell
    {
        wall = 0,
        hole = 1,
        solution = 2
    };

protected:
    /**
     *  @brief  A random number generator for obtaining random weights
     *  of the edges of a graph
    */
    std::random_device random_engine;

    /**
     *  @brief  A quantity of graph vertices
     *  An initial values is zero
    */
    unsigned quantity_vertices{0};

    /**
     *  @brief  A quantity of graph edges
     *  An initial values is zero
    */
    unsigned quantity_edges{0};

    /**
     *  @brief  A vector containing the edges of the graph
    */
    std::vector<edge> edges;
    
    /**
     *  @brief  A vector of vectors that stores the values of cells: 
     *  hole, wall, solution
    */
    std::vector<std::vector<int>> maze_field;

protected:
    /**
     *  @brief  Changes the height and width values to acceptable ones
     *  @param  height  the height of the maze field    
     *  @param  width   the width of the maze field
     *  @return A pair of equal odd values
    */
    inline std::pair<unsigned, unsigned>
    change_size_to_valid(unsigned height, unsigned width);

    /**
     *  @brief  Changes the size of the vector of vectors of the maze field
     *  @param  height  the height of the maze field    
     *  @param  width   the width of the maze field
     *  @throw  std::bad_alloc if it is not possible to allocate memory 
     *  for the desired field size
    */
    void
    resize_field(unsigned height, unsigned width);

    /**
     *  @brief  Reserves memory to store the required number of graph edges and
     *  after calculations, sets the values of the number of edges and vertices
     *  @param  height  the height of the maze field    
     *  @param  width   the width of the maze field
     *  @throw  std::bad_alloc if it is not possible to allocate memory 
     *  for the desired size of the edge vector
    */
    void
    resize_edges(unsigned height, unsigned width);

public:
    /**
     *  @brief  Creates a maze field and an edge vector for the graph
     *  @param  height  the height of the maze field    
     *  @param  width   the width of the maze field
     *  @throw  std::bad_alloc if it is not possible to allocate memory 
     *  for the desired field size or size of the edge vector
    */
    basic_maze(unsigned height, unsigned width);

    /**
     *  @brief  Virtual destructor for correct deletion on inheritance
    */
    virtual ~basic_maze();

    /**
     *  @brief  Get maze field
     *  @return A vector of vectors with cells filled with values 
     *  corresponding to one of the states: hole, wall, solution
    */
    inline std::vector<std::vector<int>>
    get_maze()
    {
        return maze_field;
    }

protected:
    /**
     *  @brief  Adds an edge to an edge vector
     *  @param  u   Edge start point 
     *  @param  v   Edge end point
     *  @param  w   Edge weight
    */
    void
    add_edge(point u, point v, int w);

public:
    /**
     *  @brief  Changes the cell specified by coordinates on the maze field
     *  @param  x      x-coordinate of point
     *  @param  y      y-coordinate of point
     *  @param  value  The value to which you want to change the specified cell
    */
    void
    set_cell(unsigned x, unsigned y, int value);

    /**
     *  @brief  A pure virtual method that needs to be redefined 
     *  in the descendant classes
    */
    virtual void
    generate_maze() = 0;

public:
    basic_maze(basic_maze const &) = delete;
    basic_maze &operator=(basic_maze const &) = delete;
};

/**
 *  @brief The maze generator class using Kruskal algorithm 
*/
class kruskal final : public basic_maze
{
private:
    /**
     *  @brief  An object of a class representing a disjoint set system
    */
    disjoint_sets sets;

public:
    /**
     *  @brief  Creates a maze field and an edge vector for the graph
     *  @param  height  the height of the maze field    
     *  @param  width   the width of the maze field
     *  @throw  std::bad_alloc if it is not possible to allocate memory 
     *  for the desired field size or size of the edge vector
    */
    kruskal(unsigned height, unsigned width);

public:
    /** 
     *  @brief  Generates a graph by walking along the maze field 
     *  and adding the corresponding edges to it. The each point of the graph
     *  is added to its own set
    */
    //void generate_graph();

    std::vector<edge> generate_graph();

public:
    /** 
     *  @brief  Generates a maze using the Kruskal algorithm. 
     *  Shuffles a set of edges by weight and traverses each of them. 
     *  For each pair of points, it is checked whether they belong 
     *  to the same set, if not, then the points between them, including 
     *  themselves, are marked on the maze field with a hole, after which 
     *  the sets of points are merged
    */
    void generate_maze() override;
};