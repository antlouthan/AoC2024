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

// Function to compute GCD of two numbers
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
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

            // // Calculate midpoint and check conditions
            // if ((a1.x + a2.x) % 2 == 0 && (a1.y + a2.y) % 2 == 0) {
            //     Point midpoint = {(a1.x + a2.x) / 2, (a1.y + a2.y) / 2};
            //     int dist1 = manhattanDistance(a1, midpoint);
            //     int dist2 = manhattanDistance(a2, midpoint);

            //     if ((dist1 == 2 * dist2 || dist2 == 2 * dist1) && midpoint.x >= 0 && midpoint.x < rows && midpoint.y >= 0 && midpoint.y < cols) {
            //         antinodes.insert(midpoint);
            //     }
            // }

            // Calculate antinodes on either side of the antennas
            int dx = a2.x - a1.x;
            int dy = a2.y - a1.y;

            // Normalize the direction vector
            int divisor = gcd(dx, dy);
            dx /= divisor;
            dy /= divisor;

             // Generate all positions in line with these antennas
            Point current = a1;
            while (current.x >= 0 && current.x < rows && current.y >= 0 && current.y < cols) {
                antinodes.insert(current);
                current.x -= dx;
                current.y -= dy;
            }

            current = a2;
            while (current.x >= 0 && current.x < rows && current.y >= 0 && current.y < cols) {
                antinodes.insert(current);
                current.x += dx;
                current.y += dy;
            }
        }
    }

    return antinodes.size();
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
