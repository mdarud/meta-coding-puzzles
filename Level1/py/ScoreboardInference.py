## Problem: Scoreboard Inference
## You are spectating a programming contest with N competitors, each trying to
## independently solve the same set of programming problems. Each problem has a
## point value, which is either 1 or 2.

## On the scoreboard, you observe that the ith competitor has attained a score
## of S{i}, which is a positive integer equal to the sum of the point values of
## all the problems they have solved.

## The scoreboard does not display the number of problems in the contest, nor
## their point values. Using the information available, you would like to
## determine the minimum possible number of problems in the contest.

## Constraints:
## 1 <= N <= 500,000
## 1 <= S{i} <= 1,000,000,000

## Solution
## Time Complexity: O(N)
## Space Complexity: O(1)
## Explanation: To minimize the number of problems, we want to use as many 2-point
## problems as possible. If all scores are even, we can achieve them using only 2-point
## problems, so the minimum number of problems would be max_score / 2. If any score is odd,
## we need at least one 1-point problem, and the rest can be 2-point problems. In this case,
## the minimum number of problems would be (max_score // 2) + 1.

from typing import List

def getMinProblemCount(N: int, S: List[int]) -> int:
  # Write your code here
  max_s = max(S)
  
  # Check if any of the scores in S is odd
  # If there is any odd score, we need to add one to the number of 2-point problems
  return (max_s//2)+1 if any(num % 2 == 1 for num in S) else max_s//2

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 4
    S = [1, 2, 3, 4]
    
    print("Test Case 1")
    print("Expected Return Value = 3")  # max_score = 4, has odd scores, so (4//2)+1 = 3
    print("Actual Return Value   = {}".format(getMinProblemCount(N, S)))
    print("")
    
    ## Test Case 2
    N = 3
    S = [4, 6, 8]
    
    print("Test Case 2")
    print("Expected Return Value = 4")  # max_score = 8, all even, so 8//2 = 4
    print("Actual Return Value   = {}".format(getMinProblemCount(N, S)))
    print("")
    
    ## Test Case 3
    N = 5
    S = [2, 4, 6, 8, 10]
    
    print("Test Case 3")
    print("Expected Return Value = 5")  # max_score = 10, all even, so 10//2 = 5
    print("Actual Return Value   = {}".format(getMinProblemCount(N, S)))
    print("")
