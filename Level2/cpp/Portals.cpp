// Problem: Portals
// You've found yourself in a grid of cells with R rows and C columns. The cell
// in the ith row from the top and jth column from the left contains one of the
// following (indicated by the character G{i,j}:

//  -   If G{i,j} = '.', the cell is empty.
//  -   If G{i,j} = 'S', the cell contains your starting position. There is
//      exactly one such cell.
//  -   If G{i,j} = 'E', the cell contains an exit. There is at least one such
//      cell.
//  -   If G{i,j} = '#', the cell contains a wall.
//  -   Otherwise, if G{i,j} is a lowercase letter (between "a" and "z",
//      inclusive), the cell contains a portal marked with that letter.

// Your objective is to reach any exit from your starting position as quickly as
// possible. Each second, you may take either of the following actions:

//  -   Walk to a cell adjacent to your current one (directly above, below, to
//      the left, or to the right), as long as you remain within the grid and
//      that cell does not contain a wall.
//  -   If your current cell contains a portal, teleport to any other cell in
//      the grid containing a portal marked with the same letter as your current
//      cell's portal.

// Determine the minimum number of seconds required to reach any exit, if it's
// possible to do so at all. If it's not possible, return -1 instead.

// Constraints:
// 1 <= R, C <= 50
// G{i,j} ∈ {'.', 'S', 'E', '#', 'a' ... 'z'}

// Solution
// Time Complexity: O(R * C)
// Space Complexity: O(R * C)
// Explanation: We use a breadth-first search (BFS) to find the shortest path from the
// starting position to any exit. BFS guarantees the shortest path in an unweighted graph.
// We treat each cell as a node in the graph, with edges between adjacent cells and between
// cells with the same portal. We use a queue to keep track of cells to visit, and a 2D array
// to track the distance to each cell. When we encounter a portal, we add all cells with the
// same portal to the queue. We return the distance to the first exit we encounter, or -1 if
// no exit is reachable.

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <utility>
using namespace std;

int getSecondsRequired(int R, int C, vector<vector<char>> G) {
    vector<vector<int>> to_tile_dur(R, vector<int>(C, 0));
    queue<pair<int, int>> q;
    unordered_map<char, vector<pair<int, int>>> portals;
  
    // Preprocessing: locate start, walls, and portals
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            char tile = G[i][j];
            if (tile == 'S') {
                q.emplace(i, j);
            } else if (tile == '#') {
                to_tile_dur[i][j] = -1;
            } else if (isalpha(tile)) {
                portals[tile].emplace_back(i, j);
            }
        }
    }
  
    vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
  
    while (!q.empty()) {
        auto [i, j] = q.front();
        q.pop();
        char curr_tile = G[i][j];
        int curr_dur = to_tile_dur[i][j];
  
        if (curr_tile == 'E') return curr_dur;
  
        // Explore 4 directions
        for (auto [dx, dy] : directions) {
            int ni = i + dx, nj = j + dy;
            if (ni >= 0 && ni < R && nj >= 0 && nj < C && to_tile_dur[ni][nj] == 0 && G[ni][nj] != '#') {
                to_tile_dur[ni][nj] = curr_dur + 1;
                q.emplace(ni, nj);
            }
        }
  
        // Handle portals
        if (isalpha(curr_tile) && !portals[curr_tile].empty()) {
            for (auto [x, y] : portals[curr_tile]) {
                if (to_tile_dur[x][y] == 0) {
                    to_tile_dur[x][y] = curr_dur + 1;
                    q.emplace(x, y);
                }
            }
            portals[curr_tile].clear();  // avoid reusing portal
        }
    }
  
    return -1;  // If endpoint 'E' not reachable
}

int main() {
    // Test Case 1
    int R = 3;
    int C = 3;
    vector<vector<char>> G = {
        {'S', '.', 'a'},
        {'#', '#', '.'},
        {'E', 'a', '.'}
    };
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 3" << endl;  // S -> right -> portal 'a' -> down to E
    cout << "Actual Return Value   = " << getSecondsRequired(R, C, G) << endl;
    cout << endl;
    
    // Test Case 2
    R = 5;
    C = 5;
    G = {
        {'S', '.', '.', '.', '.'},
        {'#', '#', '#', '#', '.'},
        {'.', '.', '.', '.', '.'},
        {'.', '#', '#', '#', '#'},
        {'.', '.', '.', '.', 'E'}
    };
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 8" << endl;  // Need to go around the walls
    cout << "Actual Return Value   = " << getSecondsRequired(R, C, G) << endl;
    cout << endl;
    
    // Test Case 3
    R = 4;
    C = 4;
    G = {
        {'S', '#', 'a', 'b'},
        {'#', '#', '#', '#'},
        {'b', '#', '#', 'a'},
        {'E', '#', '#', '#'}
    };
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 3" << endl;  // S -> portal 'a' -> portal 'b' -> down to E
    cout << "Actual Return Value   = " << getSecondsRequired(R, C, G) << endl;
    cout << endl;
    
    // Test Case 4
    R = 3;
    C = 3;
    G = {
        {'S', '#', '.'},
        {'#', '#', '#'},
        {'.', '#', 'E'}
    };
    
    cout << "Test Case 4" << endl;
    cout << "Expected Return Value = -1" << endl;  // No path to exit
    cout << "Actual Return Value   = " << getSecondsRequired(R, C, G) << endl;
    
    return 0;
}
