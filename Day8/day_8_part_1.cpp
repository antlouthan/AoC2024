#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Helper struct for grid points
struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // Custom hash function for unordered_set
    struct Hash {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ hash<int>()(p.y);
        }
    };
};

// Function to calculate Manhattan distance between two points
int manhattanDistance(const Point& a, const Point& b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

// Function to count unique antinode locations
int countAntinodes(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    unordered_set<Point, Point::Hash> antinodes;

    // Collect antenna locations and frequencies
    vector<pair<Point, char>> antennas;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] != '.') {
                antennas.push_back({{i, j}, grid[i][j]});
            }
        }
    }

    // Check all pairs of antennas
    for (size_t i = 0; i < antennas.size(); ++i) {
        for (size_t j = i + 1; j < antennas.size(); ++j) {
            if (antennas[i].second != antennas[j].second) continue;

            Point a1 = antennas[i].first;
            Point a2 = antennas[j].first;

            // Calculate midpoint and check conditions
            if ((a1.x + a2.x) % 2 == 0 && (a1.y + a2.y) % 2 == 0) {
                Point midpoint = {(a1.x + a2.x) / 2, (a1.y + a2.y) / 2};
                int dist1 = manhattanDistance(a1, midpoint);
                int dist2 = manhattanDistance(a2, midpoint);

                if ((dist1 == 2 * dist2 || dist2 == 2 * dist1) && midpoint.x >= 0 && midpoint.x < rows && midpoint.y >= 0 && midpoint.y < cols) {
                    antinodes.insert(midpoint);
                }
            }

            // Calculate antinodes on either side of the antennas
            int dx = a2.x - a1.x;
            int dy = a2.y - a1.y;

            Point antinode1 = {a1.x - dx, a1.y - dy};
            Point antinode2 = {a2.x + dx, a2.y + dy};

            if (antinode1.x >= 0 && antinode1.x < rows && antinode1.y >= 0 && antinode1.y < cols)
                antinodes.insert(antinode1);
            if (antinode2.x >= 0 && antinode2.x < rows && antinode2.y >= 0 && antinode2.y < cols)
                antinodes.insert(antinode2);
        }
    }

    return antinodes.size();  // Only return valid unique antinodes
}


int main() {
    std::vector<string> grid;
    std::ifstream infile("input.txt");

    if (!infile) {
        std::cerr << "Error reading file" << std::endl;
        return 1;
    }
    std::string line;
    while(std::getline(infile, line))
    {
        grid.push_back(line);
    }

    cout << "Total unique antinode locations: " << countAntinodes(grid) << endl;
    return 0;
}
