## Problem: Uniform Integers
## A positive integer is considered uniform if all of its digits are equal. For
## example, 222 is uniform, while 223 is not.

## Given two positive integers A and B, determine the number of uniform integers
## between A and B, inclusive.

## Constraints:
## 1 <= A <= B <= 10^(12)

## Solution
## Time Complexity: O(log B)
## Space Complexity: O(1)
## Explanation: We generate all possible uniform integers by starting with single-digit
## numbers (1-9) and repeatedly appending the same digit to create larger uniform numbers
## (like 11, 111, 1111, etc.) until we exceed B. We count those that fall within the
## range [A, B]. Since there are at most 9 * log10(B) uniform integers less than B,
## the time complexity is O(log B).

def getUniformIntegerCountInInterval(A: int, B: int) -> int:
  count = 0
  for d in range(1, 10):  # digit from 1 to 9
      num = d
      while num <= B:
          if num >= A:
              count += 1
          num = num * 10 + d
  return count

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    A = 1
    B = 100
    
    print("Test Case 1")
    print("Expected Return Value = 18")  # 1-9 and 11, 22, 33, 44, 55, 66, 77, 88, 99
    print("Actual Return Value   = {}".format(getUniformIntegerCountInInterval(A, B)))
    print("")
    
    ## Test Case 2
    A = 100
    B = 1000
    
    print("Test Case 2")
    print("Expected Return Value = 9")  # 111, 222, 333, 444, 555, 666, 777, 888, 999
    print("Actual Return Value   = {}".format(getUniformIntegerCountInInterval(A, B)))
    print("")
    
    ## Test Case 3
    A = 1000
    B = 10000
    
    print("Test Case 3")
    print("Expected Return Value = 9")  # 1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999
    print("Actual Return Value   = {}".format(getUniformIntegerCountInInterval(A, B)))
    print("")
