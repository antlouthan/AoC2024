#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <stdexcept>

using namespace std;

class Node {
public:
    int x, y;
    enum LocType {
        GUARD,
        VALID_LOC,
        INVALID_LOC
    } type;

    Node(int x, int y, char symbol) : x(x), y(y) {
        if (symbol == '^' || symbol == '>' || symbol == 'v' || symbol == '<') {
            type = GUARD;
        } else if (symbol == '.') {
            type = VALID_LOC;
        } else {
            type = INVALID_LOC;
        }
    }
};

class Map {
private:
    std::vector<std::vector<Node>> grid;
    int rows, cols;

public:
    Map(const std::vector<std::string>& input) {
        rows = input.size();
        cols = input[0].size();

        for (int i = 0; i < rows; ++i) {
            std::vector<Node> row;
            for (int j = 0; j < cols; ++j) {
                row.emplace_back(i, j, input[i][j]);
            }
            grid.push_back(row);
        }
    }

    std::pair<int, int> findGuardPos() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j].type == Node::GUARD) {
                    return {i, j};
                }
            }
        }
        throw std::runtime_error("Guard not found on the map!");
    }

    int predictGuardPath() {
        auto [startX, startY] = findGuardPos();

        // Directions: Up, Right, Down, Left
        int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
        int currentDir = 0; // Start facing up
        int x = startX, y = startY;

        std::set<std::pair<int, int>> visited;
        visited.insert({x, y}); // Include the starting position

        while (true) {
            int nextX = x + directions[currentDir][0];
            int nextY = y + directions[currentDir][1];

            // Check if the guard leaves the map
            if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols) {
                break;
            }

            // Check if the next position is invalid
            if (grid[nextX][nextY].type == Node::INVALID_LOC) {
                currentDir = (currentDir + 1) % 4; // Turn 90 degrees clockwise
                continue;
            }

            // Move forward
            x = nextX;
            y = nextY;
            visited.insert({x, y}); // Mark the position as visited
        }

        return visited.size();
    }
};

int main() {
    std::ifstream infile("input.txt");
    std::vector<std::string> map;

    if (!infile) {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }

    // Store all lines in a string vector. 
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            map.push_back(line);
        }
    }
    infile.close();

    try {
        Map mapSpace(map);
        int distinctPositions = mapSpace.predictGuardPath();
        std::cout << "The guard visited " << distinctPositions << " distinct positions.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
