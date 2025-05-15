## Problem: Boss Fight
## There are N warriors, the ith of which has a health of H{i} units and can 
## deal D{i} units of damage per second. The are confronting a boss who has
## unlimited health and can deal B units of damage per second. Both the 
## warriors and the boss deal damage continuously - for example, in half a
## second, the bossdeals B/2 units of damage.

## The warriors feel it would be unfair for many of them to fight the boss at 
## once, so they'll select just two representatives to go into battle. One 
## warrior {i} will be the front line and a different warrior {j} will back
## them up. During the battle, the boss will attack warrior {i} until that
## warrior is defeated (that is until the boss has dealt H{i} units of damage to
## them), and will then attack warrior {j} until that warrior is also defeated,
## at which point the battle will end. Along the way, each of the two warriors
## will do damage to the boss as long as they are undefeated.

## Of course, the warriors will never prevail, but they'd like to determine the 
## maximum amount of damage they could deal to the boss for any choice of warriors
## {i} and {j} before the battle ends.

## Constraints:
## 2 <= N <= 500,000
## 1 <= H{i} <= 1,000,000,000
## 1 <= D{i} <= 1,000,000,000
## 1 <= B <= 1,000,000,000

## Solution:
## Time Complexity: O(N * T) — where T is typically small (number of iterations to converge to optimal pair).
## Space Complexity: O(N)
## Explanation:
## We precompute H[i] * D[i] for each warrior.
## We iteratively search for the pair that maximizes total damage,
## alternating the front-line warrior based on which pair improves the result,
## reducing full O(N^2) brute force to something much faster in practice.

from typing import List

def getMaxDamageDealt(N: int, H: List[int], D: List[int], B: int) -> float:
    # Precompute the base damage each warrior can deal alone
    C = [h * d for h, d in zip(H, D)]

    max_damage = 0
    best = 0  # index of current front-line warrior
    improved = True

    while improved:
        improved = False
        next_best = 0

        for i in range(N):
            if i == best:
                continue

            # Total damage = damage while alive + damage dealt to teammate's front-line time
            damage = C[best] + C[i] + max(H[best] * D[i], H[i] * D[best])
            if damage > max_damage:
                max_damage = damage
                next_best = i
                improved = True

        best = next_best

    return max_damage / B


if __name__ == "__main__":
    # Test Case 1
    N = 3
    H = [10, 8, 5]
    D = [5, 10, 20]
    B = 5
    print("Test Case 1")
    print("Expected Return Value = 54.0")
    print("Actual Return Value   = {:.1f}".format(getMaxDamageDealt(N, H, D, B)))
    print("")

    # Test Case 2
    N = 2
    H = [100, 200]
    D = [1, 2]
    B = 10
    print("Test Case 2")
    print("Expected Return Value = 70.0")
    print("Actual Return Value   = {:.1f}".format(getMaxDamageDealt(N, H, D, B)))
    print("")

    # Test Case 3
    N = 4
    H = [1, 2, 3, 4]
    D = [4, 3, 2, 1]
    B = 2
    print("Test Case 3")
    print("Expected Return Value = 11.0")
    print("Actual Return Value   = {:.1f}".format(getMaxDamageDealt(N, H, D, B)))
    print("")
