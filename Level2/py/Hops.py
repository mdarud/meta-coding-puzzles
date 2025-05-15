## Problem: Hops
## A family of frogs in a pond are traveling towards dry land to hibernate. They
## hope to do so by hopping across a trail of N lily pads, numbered from 1 to N
## in order.

## There are F frogs, numbered from 1 to F. Frog i is currently perched atop
## lily pad P{i}. No two frogs are currently on the same lily pad. Lily pad N is
## right next to the shore, and none of the frogs are initially on lily pad N.

## Each second, one frog may hop along the trail towards lily pad N. When a frog
## hops, it moves to the nearest lily pad after its current lily pad which is
## not currently occupied by another frog (hopping over any other frogs on
## intermediate lily pads along the way). If this causes it to reach lily pad N,
## it will immediately exit onto the shore. Multiple frogs may not
## simultaneously hop during the same second.

## Assuming the frogs work together optimally when deciding which frog should
## hop during each second, determine the minimum number of seconds required for
## all F of them to reach the shore.

## Constraints:
## 2 <= N <= 10^(12)
## 1 <= F <= 500,000
## 1 <= P{i} <= N - 1

## Solution
## Time Complexity: O(F)
## Space Complexity: O(1)
## Explanation:
# This can be solved with a deceptively simple formula: N - min(P)
# Here's the reasoning behind it:

# Start with the more verbose form: F + (N - F - 1) - (min(P) - 1)

# - The 'F' accounts for each frog taking 1 second to hop off once they reach the end.
# - '(N - F - 1)' computes how many empty lily pads there are between the frogs and the end.
#    We subtract F for the pads already occupied, and 1 for the last pad (which no frog actually lands on).
# - 'min(P) - 1' is the number of pads before the earliest frog, which represents idle time
#    before frogs start hopping.

# Example:
# N = 7, F = 2, P = [3, 5] → pond layout: [ . . A . B . . ]
# The earliest frog is at position 3 (0-based index 2), so min(P) = 3.
# Result = N - min(P) = 7 - 3 = 4 seconds.

from typing import List

def getSecondsRequired(N: int, F: int, P: List[int]) -> int:
  # Sort the frog positions from the shore towards the land
  P.sort()

  return N - P[0]

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 7
    F = 2
    P = [3, 5]
    
    print("Test Case 1")
    print("Expected Return Value = 4")  # 7 - 3 = 4
    print("Actual Return Value   = {}".format(getSecondsRequired(N, F, P)))
    print("")
    
    ## Test Case 2
    N = 10
    F = 3
    P = [2, 4, 7]
    
    print("Test Case 2")
    print("Expected Return Value = 8")  # 10 - 2 = 8
    print("Actual Return Value   = {}".format(getSecondsRequired(N, F, P)))
    print("")
    
    ## Test Case 3
    N = 100
    F = 5
    P = [10, 20, 30, 40, 50]
    
    print("Test Case 3")
    print("Expected Return Value = 90")  # 100 - 10 = 90
    print("Actual Return Value   = {}".format(getSecondsRequired(N, F, P)))
    print("")
