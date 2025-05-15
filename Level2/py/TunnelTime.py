## Problem: Tunnel Time
## There's a circular train track with a circumference of C metres. Positions
## along the track are measured in metres, clockwise from its topmost point. For
## example, the topmost point is position 0, 1 metre clockwise along the track
## is position 1, and 1 metre counterclockwise along the track is position
## C - 1.

## A train with negligible length runs clockwise along this track at a speed of
## 1 metre per second, starting from position 0. After C seconds go by, the
## train will have driven around the entire track and returned to position 0, at
## which point it will continue going around again, with this process repeated
## indefinitely.

## There are N tunnels covering sections of the track, the ith of which begin
## at position A{i} and ends at position B{i} (and therefore has a length of
## B{i} - A{i} metres). No tunnel covers or touches position 0 (including at
## its endpoints), and no two tunnels intersect or touch one another (including
## at their endpoints). For example, if there's a tunnel spanning the interval
## of positions [1, 4], there cannot be another tunnel spanning intervals [2, 3]
## nor [4, 5].

## The train's tunnel time is the total number of seconds it has spent going
## through tunnels so far. Determine the total number of seconds which will go
## by before the train's tunnel time becomes K.

## Constraints:
## 3 <= C <= 10^(12)
## 1 <= N <= 500,000
## 1 <= A{i} < B{i} <= C - 1
## 1 <= K <= 10^(12)
## 1 <= getSecondsElapsed(C, N, A, B) <= 10^(15)

## Solution
## Time Complexity: O(N log N)
## Space Complexity: O(N)
## Explanation: We first calculate the total tunnel time for one full lap around the track.
## Then we determine how many full laps are needed to accumulate K seconds of tunnel time,
## and how much additional time is needed. Finally, we simulate the train's movement through
## the tunnels to find the exact time when the train has spent exactly K seconds in tunnels.
## The sorting of tunnels takes O(N log N) time, which dominates the overall time complexity.

from typing import List

def getSecondsElapsed(C: int, N: int, A: List[int], B: List[int], K: int) -> int:
  total_tunnel_time = sum(B) - sum(A)  # Total tunnel time for one full lap

  # Calculate full laps and remaining tunnel time
  laps, remaining_time = divmod(K, total_tunnel_time)
  seconds_elapsed = laps * C

  # If there's no remaining time, return the total time for full laps plus the last tunnel's end time
  if remaining_time == 0:
      return seconds_elapsed - C + max(B)

  # Sort tunnel start and end times only once
  tunnels = sorted(zip(A, B), key=lambda x: x[0])

  tunnel_time = 0
  for tunnel_start, tunnel_end in tunnels:
      tunnel_length = tunnel_end - tunnel_start
      tunnel_time += tunnel_length

      # Check if we've accumulated enough tunnel time
      if tunnel_time >= remaining_time:
          return seconds_elapsed + tunnel_end - (tunnel_time - remaining_time)

  return seconds_elapsed  # Should never hit this unless input is incorrect

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    C = 10
    N = 2
    A = [1, 6]
    B = [3, 7]
    K = 5
    
    print("Test Case 1")
    print("Expected Return Value = 13")  # After 13 seconds, train has spent 5 seconds in tunnels
    print("Actual Return Value   = {}".format(getSecondsElapsed(C, N, A, B, K)))
    print("")
    
    ## Test Case 2
    C = 100
    N = 3
    A = [10, 40, 70]
    B = [20, 50, 80]
    K = 60
    
    print("Test Case 2")
    print("Expected Return Value = 210")
    print("Actual Return Value   = {}".format(getSecondsElapsed(C, N, A, B, K)))
    print("")
    
    ## Test Case 3
    C = 50
    N = 1
    A = [10]
    B = [20]
    K = 100
    
    print("Test Case 3")
    print("Expected Return Value = 520")  # 10 full laps (500 seconds) plus 20 seconds to reach end of tunnel
    print("Actual Return Value   = {}".format(getSecondsElapsed(C, N, A, B, K)))
    print("")
