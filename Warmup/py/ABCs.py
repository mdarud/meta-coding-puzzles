## Problem: ABCs
## Given three integers A, B, and C, determine their sum.

## Your task is to implement the function getSum(A, B, C) which returns the sum
## A + B + C.

## Constraints:
## 1 <= A, B, C <= 100

## Solution
## Time Complexity: O(1)
## Space Complexity: O(1)

def getSum(A: int, B: int, C: int) -> int:
  return A+B+C

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    A = 1
    B = 2
    C = 3

    print("Test Case 1")
    print("Expected Return Value = 6")
    print("Actual Return Value   = {}".format(getSum(A, B, C)))
    print("")

    ## Test Case 2
    A = 200
    B = 150
    C = 100

    print("Test Case 2")
    print("Expected Return Value = 450")
    print("Actual Return Value   = {}".format(getSum(A, B, C)))
    print("")

    ## Test Case 3
    A = 12
    B = 26
    C = 72

    print("Test Case 3")
    print("Expected Return Value = 110")
    print("Actual Return Value   = {}".format(getSum(A, B, C)))
    print("")