## Problem: Director of Photography
## A photography set consists of N cells in a row, numbered from 1 to N in
## order, and can be represented by a string C of length N. Each cell i is one
## of the following types (indicated by C{i}, the ith character of C):

##      If C{i} = 'P', it is allowed to contain a photographer
##      If C{i} = 'A', it is allowed to contain an actor
##      If C{i} = 'B', it is allowed to contain a backdrop
##      If C{i} = '.', it must be left empty

## A photograph consists of a photographer, an actor, and a backdrop, such that
## each of them is placed in a valid cell, and such that the actor is between
## the photographer and the backdrop. Such a photograph is considered artistic
## if the distance between the photographer and the actor is between X and Y
## cells (inclusive), and the distance between the actor and the backdrop is
## also between X and Y cells (inclusive). The distance between cells i and j
## is |i - j| (the absolute value of the difference between their indices).

## Determine the number of different artistic photographs which could
## potentially be taken at the set. Two photographs are considered different if
## they involve a different photographer cell, actor cell, and/or backdrop cell.

## Constraints:
## 1 <= N <= 200
## 1 <= X <= Y <= N

## Solution
## Time Complexity: O(N)
## Space Complexity: O(N)
## Explanation: We use prefix sums to efficiently count the number of photographers
## and backdrops within specific distance ranges from each actor. For each actor position,
## we check both possible arrangements: photographer on the left with backdrop on the right,
## and backdrop on the left with photographer on the right. The prefix sums allow us to
## quickly determine how many valid photographers and backdrops are within the required
## distance range without having to iterate through the string multiple times.

def getArtisticPhotographCount(N: int, C: str, X: int, Y: int) -> int:
  # Write your code here
  prefix_p = [0] * (N + 1)  # prefix sum of photographers
  prefix_b = [0] * (N + 1)  # prefix sum of backdrops

  # Build prefix sums
  for i in range(N):
      prefix_p[i+1] = prefix_p[i] + (1 if C[i] == 'P' else 0)
      prefix_b[i+1] = prefix_b[i] + (1 if C[i] == 'B' else 0)
      
  count = 0

  for i in range(N):
      if C[i] == 'A':
          # Photographer to the left, backdrop to the right
          left_min = max(0, i - Y)
          left_max = i - X
          right_min = i + X
          right_max = min(N-1, i + Y)

          if left_min <= left_max:
              photographers = prefix_p[left_max+1] - prefix_p[left_min]
          else:
              photographers = 0

          if right_min <= right_max:
              backdrops = prefix_b[right_max+1] - prefix_b[right_min]
          else:
              backdrops = 0

          count += photographers * backdrops

          # Backdrop to the left, photographer to the right
          if left_min <= left_max:
              backdrops = prefix_b[left_max+1] - prefix_b[left_min]
          else:
              backdrops = 0

          if right_min <= right_max:
              photographers = prefix_p[right_max+1] - prefix_p[right_min]
          else:
              photographers = 0

          count += backdrops * photographers

  return count

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 5
    C = "APABA"
    X = 1
    Y = 2
    
    print("Test Case 1")
    print("Expected Return Value = 1")
    print("Actual Return Value   = {}".format(getArtisticPhotographCount(N, C, X, Y)))
    print("")
    
    ## Test Case 2
    N = 5
    C = "APBPA"
    X = 2
    Y = 3
    
    print("Test Case 2")
    print("Expected Return Value = 0")
    print("Actual Return Value   = {}".format(getArtisticPhotographCount(N, C, X, Y)))
    print("")
    
    ## Test Case 3
    N = 8
    C = "PBAAPA.B"
    X = 1
    Y = 3
    
    print("Test Case 3")
    print("Expected Return Value = 3")
    print("Actual Return Value   = {}".format(getArtisticPhotographCount(N, C, X, Y)))
    print("")
