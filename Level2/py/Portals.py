## Problem: Portals
## You've found yourself in a grid of cells with R rows and C columns. The cell
## in the ith row from the top and jth column from the left contains one of the
## following (indicated by the character G{i,j}:

##  -   If G{i,j} = '.', the cell is empty.
##  -   If G{i,j} = 'S', the cell contains your starting position. There is
#       exactly one such cell.
##  -   If G{i,j} = 'E', the cell contains an exit. There is at least one such
##      cell.
##  -   If G{i,j} = '#', the cell contains a wall.
##  -   Otherwise, if G{i,j} is a lowercase letter (between "a" and "z",
##      inclusive), the cell contains a portal marked with that letter.

## Your objective is to reach any exit from your starting position as quickly as
## possible. Each second, you may take either of the following actions:

##  -   Walk to a cell adjacent to your current one (directly above, below, to
##      the left, or to the right), as long as you remain within the grid and
##      that cell does not contain a wall.
##  -   If your current cell contains a portal, teleport to any other cell in
##      the grid containing a portal marked with the same letter as your current
##      cell's portal.

## Determine the minimum number of seconds required to reach any exit, if it's
## possible to do so at all. If it's not possible, return -1 instead.

## Constraints:
## 1 <= R, C <= 50
## G{i,j} ∈ {'.', 'S', 'E', '#', 'a' ... 'z'}

## Solution
## Time Complexity: O(R * C)
## Space Complexity: O(R * C)
## Explanation: We use a breadth-first search (BFS) to find the shortest path from the
## starting position to any exit. BFS guarantees the shortest path in an unweighted graph.
## We treat each cell as a node in the graph, with edges between adjacent cells and between
## cells with the same portal. We use a queue to keep track of cells to visit, and a 2D array
## to track the distance to each cell. When we encounter a portal, we add all cells with the
## same portal to the queue. We return the distance to the first exit we encounter, or -1 if
## no exit is reachable.

from typing import List
from collections import deque

def getSecondsRequired(R: int, C: int, G: List[List[str]]) -> int:
  to_tile_dur = [[0] * C for _ in range(R)]
  portals = {}
  queue = deque()

  # Directions: up, down, left, right
  directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

  # Preprocessing
  for i in range(R):
      for j in range(C):
          tile = G[i][j]
          if tile == 'S':
              queue.append((i, j))
          elif tile == '#':
              to_tile_dur[i][j] = -1
          elif tile.isalpha():
              portals.setdefault(tile, []).append((i, j))

  while queue:
      i, j = queue.popleft()
      curr_tile = G[i][j]
      curr_dur = to_tile_dur[i][j]

      if curr_tile == 'E':
          return curr_dur

      # Explore 4 directions
      for dx, dy in directions:
          ni, nj = i + dx, j + dy
          if 0 <= ni < R and 0 <= nj < C:
              if G[ni][nj] != '#' and to_tile_dur[ni][nj] == 0:
                  to_tile_dur[ni][nj] = curr_dur + 1
                  queue.append((ni, nj))

      # Use portal if applicable
      if curr_tile.isalpha() and portals.get(curr_tile):
          for x, y in portals[curr_tile]:
              if to_tile_dur[x][y] == 0:
                  to_tile_dur[x][y] = curr_dur + 1
                  queue.append((x, y))
          portals[curr_tile] = []  # Clear to prevent reuse

  return -1  # If 'E' is unreachable

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    R = 3
    C = 3
    G = [
        ['S', '.', 'a'],
        ['#', '#', '.'],
        ['E', 'a', '.']
    ]
    
    print("Test Case 1")
    print("Expected Return Value = 3")  # S -> right -> portal 'a' -> down to E
    print("Actual Return Value   = {}".format(getSecondsRequired(R, C, G)))
    print("")
    
    ## Test Case 2
    R = 5
    C = 5
    G = [
        ['S', '.', '.', '.', '.'],
        ['#', '#', '#', '#', '.'],
        ['.', '.', '.', '.', '.'],
        ['.', '#', '#', '#', '#'],
        ['.', '.', '.', '.', 'E']
    ]
    
    print("Test Case 2")
    print("Expected Return Value = 8")  # Need to go around the walls
    print("Actual Return Value   = {}".format(getSecondsRequired(R, C, G)))
    print("")
    
    ## Test Case 3
    R = 4
    C = 4
    G = [
        ['S', '#', 'a', 'b'],
        ['#', '#', '#', '#'],
        ['b', '#', '#', 'a'],
        ['E', '#', '#', '#']
    ]
    
    print("Test Case 3")
    print("Expected Return Value = 3")  # S -> portal 'a' -> portal 'b' -> down to E
    print("Actual Return Value   = {}".format(getSecondsRequired(R, C, G)))
    print("")
    
    ## Test Case 4
    R = 3
    C = 3
    G = [
        ['S', '#', '.'],
        ['#', '#', '#'],
        ['.', '#', 'E']
    ]
    
    print("Test Case 4")
    print("Expected Return Value = -1")  # No path to exit
    print("Actual Return Value   = {}".format(getSecondsRequired(R, C, G)))
    print("")
