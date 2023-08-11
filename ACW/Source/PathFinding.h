#pragma once
#include <vector>
#include <queue>
#include <unordered_map>

// Define a struct for the terrain cell
struct Cell {
    int x, y;
    int f, g, h;
    bool walkable;
    Cell* parent;
};

// Define the class for pathfinding
class Pathfinding {
    public:
        // Define the terrain dimensions and initialize the terrain cells
        int width, height;
        std::vector<std::vector<Cell>> terrain;

        // Initialize the start and end positions
        int startX, startY, endX, endY;

        // Initialize the open and closed lists
        std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> openList;
        std::unordered_map<int, int> closedList;

        // Initialize the path
        std::vector<Cell> path;

        // Constructor
        Pathfinding(int width, int height, int startX, int startY, int endX, int endY) {
            this->width = width;
            this->height = height;
            this->startX = startX;
            this->startY = startY;
            this->endX = endX;
            this->endY = endY;

            // Initialize the terrain cells
            for (int i = 0; i < width; i++) {
                std::vector<Cell> row;
                for (int j = 0; j < height; j++) {
                    Cell cell;
                    cell.x = i;
                    cell.y = j;
                    cell.walkable = true; // assume all cells are walkable
                    row.push_back(cell);
                }
                terrain.push_back(row);
            }
        }

        // Find the path
        bool findPath();

        // Heuristic function
        int heuristic(int x, int y);

        // Retrace the path
        void retracePath(Cell end);

};