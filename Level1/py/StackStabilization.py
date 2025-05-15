## Problem: Stack Stabilization 
## There's a stack of N inflatable discs, with the ith disc from the top having
## an initial radius of R{i} inches.

## The stack is considered unstable if it includes at least one disc whose
## radius is larger than or equal to that of the disc directly under it. In
## other words, for the stack to be stable, each disc must have a strictly
## smaller radius than that of the disc directly under it.

## As long as the stack is unstable, you can repeatedly choose any disc of your
## choice and deflate it down to have a radius of your choice which is strictly
## smaller than the disc's prior radius. The new radius must be a positive
## integer number of inches.

## Determine the minimum number of discs which need to be deflated in order to
## make the stack stable, if this is possible at all. If it is impossible to
## stabilize the stack, return -1 instead.

## Constraints:
## 1 <= N <= 50
## 1 <= R{i} <= 1,000,000,000

## Solution
## Time Complexity: O(N)
## Space Complexity: O(1)
## Explanation: We work from the bottom of the stack upwards. For each disc, if its
## radius is greater than or equal to the maximum allowed radius (which is the radius
## of the disc below it or the previously computed maximum allowed radius), we need to
## deflate it to be one less than the maximum allowed radius. We then update the maximum
## allowed radius for the next disc above. If at any point the maximum allowed radius
## becomes 0 or negative, it's impossible to stabilize the stack.

from typing import List

def getMinimumDeflatedDiscCount(N: int, R: List[int]) -> int:
  count = 0
  max_radius = R[-1]  # The bottom disc radius

  for i in range(N - 2, -1, -1):
      if R[i] >= max_radius:
          # Need to deflate to max_radius - 1
          max_radius -= 1
          if max_radius <= 0:
              return -1
          count += 1
      else:
          # No need to deflate, update max_radius to current R[i]
          max_radius = R[i]

  return count

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 5
    R = [2, 5, 3, 6, 5]  # Top to bottom
    
    print("Test Case 1")
    print("Expected Return Value = 3")  # Need to deflate discs at positions 0, 2, and 3
    print("Actual Return Value   = {}".format(getMinimumDeflatedDiscCount(N, R)))
    print("")
    
    ## Test Case 2
    N = 3
    R = [100, 100, 100]  # Top to bottom
    
    print("Test Case 2")
    print("Expected Return Value = 2")  # Need to deflate top two discs
    print("Actual Return Value   = {}".format(getMinimumDeflatedDiscCount(N, R)))
    print("")
    
    ## Test Case 3
    N = 4
    R = [6, 5, 4, 3]  # Already stable
    
    print("Test Case 3")
    print("Expected Return Value = 0")  # No deflation needed
    print("Actual Return Value   = {}".format(getMinimumDeflatedDiscCount(N, R)))
    print("")
    
    ## Test Case 4
    N = 4
    R = [1, 2, 3, 4]  # Impossible to stabilize
    
    print("Test Case 4")
    print("Expected Return Value = -1")  # Impossible to stabilize
    print("Actual Return Value   = {}".format(getMinimumDeflatedDiscCount(N, R)))
    print("")
