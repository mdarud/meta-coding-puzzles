## Problem: Rotary Lock
## You're trying to open a lock. The lock comes with a wheel which has the
## integers from 1 to N arranged in a circle in order around it (with integers
## 1 and N adjacent to one another). The wheel is initially pointing at 1.

## It takes 1 second to rotate the wheel by 1 unit to an adjacent integer in
## either direction, and it takes no time to select an integer once the wheel
## is pointing at it.

## The lock will open if you enter a certain code. The code consists of a
## sequence of M integers, the ith of which is C{i}. Determine the minimum
## number of seconds required to select all M of the code's integers in order.

## Constraints:
## 3 <= N <= 50,000,000
## 1 <= M <= 1,000
## 1 <= C{i} <= N

## Solution
## Time Complexity: O(M)
## Space Complexity: O(1)
## Explanation: We calculate the minimum rotation time between each consecutive position
## in the code sequence. For each position, we can rotate either clockwise or counterclockwise,
## so we take the minimum of the two possible rotation times. The rotation time between
## positions a and b is min(|a-b|, N-|a-b|), where the first term represents the direct
## rotation and the second term represents the rotation in the opposite direction around
## the circle.

from typing import List

def getMinCodeEntryTime(N: int, M: int, C: List[int]) -> int:
  def rotation_time(a: int, b: int) -> int:
    return min(abs(a - b), N - abs(a - b))

  total_time = 0
  current_position = 1  # Starting position

  for target in C:
      total_time += rotation_time(current_position, target)
      current_position = target

  return total_time

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 10
    M = 3
    C = [9, 4, 8]
    
    print("Test Case 1")
    print("Expected Return Value = 9")  # 1->9 (2 steps) + 9->4 (5 steps) + 4->8 (4 steps) = 11 steps
    print("Actual Return Value   = {}".format(getMinCodeEntryTime(N, M, C)))
    print("")
    
    ## Test Case 2
    N = 10
    M = 4
    C = [9, 4, 8, 1]
    
    print("Test Case 2")
    print("Expected Return Value = 12")
    print("Actual Return Value   = {}".format(getMinCodeEntryTime(N, M, C)))
    print("")
    
    ## Test Case 3
    N = 100
    M = 5
    C = [73, 32, 5, 84, 50]
    
    print("Test Case 3")
    print("Expected Return Value = 176")
    print("Actual Return Value   = {}".format(getMinCodeEntryTime(N, M, C)))
    print("")
