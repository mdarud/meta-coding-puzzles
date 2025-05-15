## Problem: Rotary Lock 2
## You're trying to open a lock. The lock comes with two wheels, each of which
## has the integers from 1 to N arranged in a circle in order around it (with
## integers 1 and N adjacent to one another). Each wheel is initially pointing
## at 1.

## It takes 1 second to rotate the wheel by 1 unit to an adjacent integer in
## either direction, and it takes no time to select an integer once the wheel is
## pointing at it.

## The lock will open if you enter a certain code. The code consists of a
## sequence of M integers, the ith of which is C{i}. For each integer in the
## sequence, you may select it with either of the two wheels. Determine the
## minimum number of seconds required to select all M of the code's integers
## in order.

## Constraints:
## 3 <= N <= 1,000,000,000
## 1 <= M <= 3,000
## 1 <= C{i} <= N

## Solution
## Time Complexity: O(M²)
## Space Complexity: O(M²)
## Explanation: We use dynamic programming to find the minimum time. For each position
## in the code, we consider two options: move the first dial or move the second dial.
## We choose the option that minimizes the total time. The DP table dp[i][j] represents
## the minimum time to reach the (i+1)-th code digit, with the dial used at the j-th step.
## We work backwards from the end of the code to the beginning, considering all possible
## combinations of dial positions.

from typing import List

def getMinCodeEntryTime(N: int, M: int, C: List[int]) -> int:
    def rotation_time(a: int, b: int) -> int:
        """Return the minimum rotation time between two positions on a dial of size N."""
        return min(abs(a - b), N - abs(a - b))

    # Prepend 1 to simulate both dials starting at position 1
    code = [1] + C

    # DP table: dp[i][j] = min time to reach i+1-th code, with dial used at j-th step
    dp = [[0] * M for _ in range(M)]

    for i in range(M - 1, 0, -1):
        for j in range(i):
            move_i = rotation_time(code[i], code[i + 1]) + dp[i][j]
            move_j = rotation_time(code[j], code[i + 1]) + dp[i][i]
            dp[i - 1][j] = min(move_i, move_j)

    return rotation_time(1, C[0]) + dp[0][0]

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 10
    M = 3
    C = [9, 4, 8]
    
    print("Test Case 1")
    print("Expected Return Value = 6")  # Optimal: Dial 1 -> 9, Dial 2 -> 4, Dial 1 -> 8
    print("Actual Return Value   = {}".format(getMinCodeEntryTime(N, M, C)))
    print("")
    
    ## Test Case 2
    N = 10
    M = 4
    C = [9, 4, 8, 1]
    
    print("Test Case 2")
    print("Expected Return Value = 8")
    print("Actual Return Value   = {}".format(getMinCodeEntryTime(N, M, C)))
    print("")
    
    ## Test Case 3
    N = 100
    M = 5
    C = [73, 32, 5, 84, 50]
    
    print("Test Case 3")
    print("Expected Return Value = 89")
    print("Actual Return Value   = {}".format(getMinCodeEntryTime(N, M, C)))
    print("")
