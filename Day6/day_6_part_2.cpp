#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <tuple>

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
        if (symbol == '^') {
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
    vector<vector<Node>> grid;
    int rows, cols;

public:
    Map(const vector<string>& input) {
        rows = input.size();
        cols = input[0].size();

        for (int i = 0; i < rows; ++i) {
            vector<Node> row;
            for (int j = 0; j < cols; ++j) {
                row.emplace_back(i, j, input[i][j]);
            }
            grid.push_back(row);
        }
    }

    pair<int, int> findGuardPos() {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j].type == Node::GUARD) {
                    return {i, j};
                }
            }
        }
        throw runtime_error("Guard not found on the map!");
    }

    // Simulate guard's patrol and detect loops
    bool simulateGuardWithLoopCheck(const vector<vector<Node>>& mapGrid, int startX, int startY) {
        int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up, Right, Down, Left
        int currentDir = 0; // Start facing up
        int x = startX, y = startY;

        set<tuple<int, int, int>> visited; // Track (x, y, direction)
        visited.insert({x, y, currentDir});

        while (true) {
            int nextX = x + directions[currentDir][0];
            int nextY = y + directions[currentDir][1];

            // Check if the guard leaves the map
            if (nextX < 0 || nextX >= rows || nextY < 0 || nextY >= cols) {
                return false; // No loop, guard leaves the map
            }

            // Check if the next position is invalid
            if (mapGrid[nextX][nextY].type == Node::INVALID_LOC) {
                currentDir = (currentDir + 1) % 4; // Turn 90 degrees clockwise
                continue; // Skip forward movement
            }

            // Move forward
            x = nextX;
            y = nextY;

            // Check if this position and direction have already been visited
            if (visited.count({x, y, currentDir})) {
                return true; // Loop detected
            }

            // Mark the position and direction as visited
            visited.insert({x, y, currentDir});
        }
    }

    // Find positions where a new obstruction creates a loop
    int findPossibleObstructionPositions() {
        auto [startX, startY] = findGuardPos();
        int possiblePositions = 0;

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                // Skip non-valid locations and the guard's starting position
                if (grid[i][j].type != Node::VALID_LOC || (i == startX && j == startY)) {
                    continue;
                }

                // Temporarily place an obstruction
                grid[i][j].type = Node::INVALID_LOC;

                // Check if this causes a loop
                if (simulateGuardWithLoopCheck(grid, startX, startY)) {
                    possiblePositions++;
                }

                // Restore the original state
                grid[i][j].type = Node::VALID_LOC;
            }
        }

        return possiblePositions;
    }
};

int main() {
    ifstream infile("input.txt");
    vector<string> map;

    if (!infile) {
        cerr << "Error reading file" << endl;
        return 1;
    }

    if (infile.is_open()) {
        string line;
        while (getline(infile, line)) {
            map.push_back(line);
        }
    }
    infile.close();

    try {
        Map mapSpace(map);
        int possibleObstructionPositions = mapSpace.findPossibleObstructionPositions();
        cout << "There are " << possibleObstructionPositions << " possible positions for the new obstruction.\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
