## Problem: Missing Mail
## You are the manager of a mail room which is frequently subject to theft. A
## period of N days is about to occur, such that on the ith day, the following
## sequence of events will occur in order:

##  1. A package with a value of V{i} dollars will get delivered to the mail
##     room (unless V{i} = 0, in which case no package will get delivered).
##
##  2. You can choose to pay C dollars to enter the mail room and collect all of
##     the packages there (removing them from the room), and then leave the
##     room.
##
##  3. With probability S, all packages currently in the mail room will get
##     stolen (and therefore removed from the room).

## Note that you're aware of the delivery schedule V{1..N}, but can only observe
## the state of the mail room when you choose to enter it, meaning that you
## won't immediately be aware of whether or not packages were stolen at the end
## of any given day.

## Your profit after the Nth day will be equal to the total value of all
## packages which you collected up to that point, minus the total amount of
## money you spent on entering the mail room.

## Please determine the maximum expected profit you can achieve (in dollars).

## Note: Your return value must have an absolute or relative error of at most
## 10^(-6) to be considered correct.

## Constraints:
## 1 <= N <= 4000
## 0 <= V{i} <= 1000
## 1 <= C <= 1000
## 0.0 <= S <= 1.0

## Solution
## Time Complexity: O(N²)
## Space Complexity: O(N)
## Explanation: We use dynamic programming to solve this problem. For each day, we have
## two choices: either collect the packages or leave them. If we collect, we pay C dollars
## and get all the packages. If we leave them, there's a probability S that they'll be stolen.
## We use a 1D DP array where dp[i] represents the maximum expected profit up to day i.
## For each day, we consider all possible previous days when we might have last collected
## packages, and choose the option that maximizes our expected profit.

from typing import List

def getMaxExpectedProfit(N: int, V: List[int], C: int, S: float) -> float:
  exp_sum = []
  curr = 0.

  # Calculate the cumulative sum of values adjusted by the factor (1 - S)
  for v in V:
      curr *= (1 - S)
      curr += v
      exp_sum.append(curr)

  exp_sum.append(0.)  # Append a final value for boundary condition

  # Initialize dp array
  dp = [0.] * (N + 1)

  # Iterate over each day and calculate the dp value based on previous days
  for i in range(1, N + 1):
      max_val = -float('inf')

      for j in range(i, 0, -1):  # j goes backward, ensuring dp[i] is calculated from dp[j]
          max_val = max(max_val, dp[j-1] + max(0., exp_sum[i-1] - exp_sum[j-2] * (1 - S) ** (i-j+1) - C))

      dp[i] = max_val

  return dp[N]

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 5
    V = [10, 2, 8, 6, 4]
    C = 5
    S = 0.0
    
    print("Test Case 1")
    print("Expected Return Value = 25.0")  # Collect on day 5, get all packages (10+2+8+6+4) - 5 = 25
    print("Actual Return Value   = {}".format(getMaxExpectedProfit(N, V, C, S)))
    print("")
    
    ## Test Case 2
    N = 5
    V = [10, 2, 8, 6, 4]
    C = 5
    S = 1.0
    
    print("Test Case 2")
    print("Expected Return Value = 15.0")  # Collect every day, (10-5) + (2-5) + (8-5) + (6-5) + (4-5) = 5
    print("Actual Return Value   = {}".format(getMaxExpectedProfit(N, V, C, S)))
    print("")
    
    ## Test Case 3
    N = 3
    V = [20, 0, 10]
    C = 10
    S = 0.5
    
    print("Test Case 3")
    print("Expected Return Value = 15.0")  # Optimal strategy depends on probability
    print("Actual Return Value   = {}".format(getMaxExpectedProfit(N, V, C, S)))
    print("")
