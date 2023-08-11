#include"PathFinding.h"
#include <vector>
#include <queue>
#include <unordered_map>
#include "helpers/IRenderHelpers.h"
#include "helpers/IGuiHelpers.h"
#include <iostream>

bool Pathfinding::findPath()
{
    // Set the start cell
    terrain[startX][startY].g = 0;
    terrain[startX][startY].h = heuristic(startX, startY);
    terrain[startX][startY].f = terrain[startX][startY].g + terrain[startX][startY].h;
    terrain[startX][startY].parent = nullptr;
    openList.push(terrain[startX][startY]);

    // Keep searching while the open list is not empty
    while (!openList.empty()) {
        // Get the cell with the lowest f value from the open list
        Cell current = openList.top();
        openList.pop();

        // Add the current cell to the closed list
        closedList[current.x * width + current.y] = 1;

        // Check if we have reached the end cell
        if (current.x == endX && current.y == endY) {
            // We have found the path, so retrace it
            retracePath(current);

            return true;
        }

        // Check the neighboring cells
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                // Skip the current cell
                if (i == 0 && j == 0) {
                    continue;
                }

                // Get the x and y coordinates of the neighboring cell
                int x = current.x + i;
                int y = current.y + j;

                // Check if the neighboring cell is within the terrain bounds
                if (x < 0 || x >= width || y < 0 || y >= height) {
                    continue;
                }

                // Check if the neighboring cell is walkable
                if (!terrain[x][y].walkable) {
                    continue;
                }

                // Check if the neighboring cell is already in the closed list
                if (closedList.find(x * width + y) != closedList.end()) {
                    continue;
                }

                // Calculate the new g value for the neighboring cell
                int newG = current.g + 1;

                // Check if the neighboring cell is already in the open list
                if (openList.find(terrain[x][y]) != openList.end()) {
                    // Update the neighboring cell if the new g value is lower
                    if (newG < terrain[x][y].g) {
                        terrain[x][y].g = newG;
                        terrain[x][y].h = heuristic(x, y);
                        terrain[x][y].f = terrain[x][y].g + terrain[x][y].h;
                        terrain[x][y].parent = &terrain[current.x][current.y];
                    }
                }
                else {
                    // Add the neighboring cell to the open list
                    terrain[x][y].g = newG;
                    terrain[x][y].h = heuristic(x, y);
                    terrain[x][y].f = terrain[x][y].g + terrain[x][y].h;
                    terrain[x][y].parent = &terrain[current.x][current.y];
                    openList.push(terrain[x][y]);
                }
            }
        }
    }
    // We have not found a path
	return false;
}

int Pathfinding::heuristic(int x, int y)
{
    // Manhattan distance
    return abs(x - endX) + abs(y - endY);
}

void Pathfinding::retracePath(Cell end)
{
    // Start at the end cell
    Cell current = end;

    // Go through the cells in reverse order
    while (current.parent != nullptr) {
        // Add the cell to the path
        path.push_back(current);

        // Move to the parent cell
        current = *current.parent;

        // Reverse the path
        std::reverse(path.begin(), path.end());
    }

}
