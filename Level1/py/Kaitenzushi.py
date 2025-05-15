## Problem: Kaitenzushi
## There are N dishes in a row on a kaiten belt, with the ith dish being of type
## D{i}. Some dishes may be of the same type as one another.

## Kaiten Belt: {https://en.wikipedia.org/wiki/Conveyor_belt_sushi}

## You're very hungry, but you'd also like to keep things interesting. The N
## dishes will arrive in front of you, one after another in order, and for each
## one you'll eat it as long as it isn't the same type as any of the previous K
## dishes you've eaten. You eat very fast, so you can consume a dish before the
## next one gets to you. Any dishes you choose not to eat as they pass will be
## eaten by others.

## Determine how many dishes you'll end up eating.

## Constraints:
## 1 <= N <= 500,000
## 1 <= K <= N
## 1 <= D{i} <= 1,000,000

## Solution
## Time Complexity: O(N)
## Space Complexity: O(min(N, K))
## Explanation: We use an OrderedDict (which maintains insertion order) to keep track of
## the last K dishes we've eaten. For each new dish, we check if it's already in our
## recent dishes. If not, we eat it and add it to our recent dishes. If our recent dishes
## list exceeds K, we remove the oldest dish. This approach ensures we only eat dishes
## that aren't the same type as any of the previous K dishes we've eaten.

from typing import List
from collections import OrderedDict

def getMaximumEatenDishCount(N: int, D: List[int], K: int) -> int:
    recent = OrderedDict()
    count = 0

    for dish in D:
        if dish not in recent:
            count += 1
            if len(recent) == K:
                recent.popitem(last=False)  # Remove oldest dish
            recent[dish] = None  # Insert new dish

    return count

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 6
    D = [1, 2, 3, 3, 2, 1]
    K = 1
    
    print("Test Case 1")
    print("Expected Return Value = 5")  # Can't eat the second 3, but can eat everything else
    print("Actual Return Value   = {}".format(getMaximumEatenDishCount(N, D, K)))
    print("")
    
    ## Test Case 2
    N = 7
    D = [1, 2, 1, 2, 1, 2, 1]
    K = 2
    
    print("Test Case 2")
    print("Expected Return Value = 4")  # Eat dishes at positions 0, 1, 4, 6
    print("Actual Return Value   = {}".format(getMaximumEatenDishCount(N, D, K)))
    print("")
    
    ## Test Case 3
    N = 5
    D = [1, 2, 3, 4, 5]
    K = 5
    
    print("Test Case 3")
    print("Expected Return Value = 5")  # All dishes are different, so eat all of them
    print("Actual Return Value   = {}".format(getMaximumEatenDishCount(N, D, K)))
    print("")
