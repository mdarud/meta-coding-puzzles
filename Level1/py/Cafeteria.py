## Problem: Cafeteria
## A cafeteria table consists of a row of N seats, numbered from 1 to N from
## left to right. Social distancing guidelines require that every diner be
## seated such that K seats to their left and K seats to their right (or all the
## remaining seats to that side if there are fewer than K) remain empty.

## There are currently M diners seated at the table, the ith of whom is in seat
## S{i}. No two diners are sitting in the same seat, and the social distancing
## guidelines are satisfied.

## Determine the maximum number of additional diners who can potentially sit at
## the table without social distancing guidelines being violated for any new or
## existing diners, assuming that the existing diners cannot move and that the
## additional diners will cooperate to maximize how many of them can sit down.

## Constraints:
## 1 <= N <= 10^(15)
## 1 <= K <= N
## 1 <= M <= 500,000
## M <= N
## 1 <= S{i} <= N

## Solution
## Time Complexity: O(M log M)
## Space Complexity: O(1)
## Explanation: We use a greedy approach to place additional diners. First, we sort the
## positions of existing diners. Then we calculate how many additional diners can fit in
## each segment: between the start of the table and the first diner, between consecutive
## diners, and between the last diner and the end of the table. For each segment, we can
## place a diner every (K+1) positions to maintain social distancing. The formula
## (segment_length - 1) // (K + 1) gives us the number of additional diners that can fit
## in a segment of a given length.

from typing import List

def getMaxAdditionalDinersCount(N: int, K: int, M: int, S: List[int]) -> int:
  S.sort()
  additional_diners = (S[0] - 1) // (K + 1)
  for i in range(1, len(S)):
    additional_diners += (S[i] - S[i-1] - K-1) // (K + 1)
  additional_diners += (N - S[-1]) // (K + 1)
  return additional_diners

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 10
    K = 1
    M = 2
    S = [2, 6]
    
    print("Test Case 1")
    print("Expected Return Value = 3")  # Can add diners at positions 4, 8, and 10
    print("Actual Return Value   = {}".format(getMaxAdditionalDinersCount(N, K, M, S)))
    print("")
    
    ## Test Case 2
    N = 15
    K = 2
    M = 3
    S = [11, 6, 14]
    
    print("Test Case 2")
    print("Expected Return Value = 1")  # Can add a diner at position 3
    print("Actual Return Value   = {}".format(getMaxAdditionalDinersCount(N, K, M, S)))
    print("")
    
    ## Test Case 3
    N = 100
    K = 3
    M = 1
    S = [50]
    
    print("Test Case 3")
    print("Expected Return Value = 16")  # Can add diners at positions 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 54, 58, 62, 66, 70
    print("Actual Return Value   = {}".format(getMaxAdditionalDinersCount(N, K, M, S)))
    print("")
