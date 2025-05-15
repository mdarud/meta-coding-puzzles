## Problem: Rabbit Hole
## You're having a grand old time clicking through the rabbit hole that is your
## favorite online encyclopedia.

## The encyclopedia consists of N different web pages, numbered from 1 to N.
## Each page i contains nothing but a single link to a different page L{i}.

## A session spent on this website involves beginning on one of the N pages,
## and then navigating around using the links until you decide to stop. That is,
## while on page i, you may either move to page L{i}, or stop your browsing
## session.

## Assuming you can choose which page you begin the session on, what's the
## maximum number of different pages you can visit in a single session? Note
## that a page only counts once even if visited multiple times during the
## session.

## Constraints:
## 2 <= N <= 500,000
## 1 <= L{i} <= N
## L{i} ≠ i

## Solution
## Time Complexity: O(N)
## Space Complexity: O(N)
## Explanation: We use a modified depth-first search (DFS) approach to find the maximum
## number of unique pages that can be visited in a single session. For each unvisited page,
## we start a DFS traversal and keep track of the number of pages visited. If we encounter
## a cycle, we calculate the cycle length and update the visitable count for all pages in the
## cycle. If we encounter a previously visited page, we extend the count by adding the number
## of pages visitable from that page. We then backtrack to update the visitable counts for
## all pages in the current path. The maximum visitable count across all pages is our answer.

from typing import List

def getMaxVisitableWebpages(N: int, L: List[int]) -> int:
  page_mark = [0] * (N + 1)         # Track DFS traversal origin
  visitable_count = [0] * (N + 1)   # Number of pages visitable from each page

  for start_page in range(1, N + 1):
      if page_mark[start_page] != 0:
          continue

      page = start_page
      visited_pages = 0

      # Traverse through links until we find a visited page or a cycle
      while page_mark[page] == 0:
          visited_pages += 1
          page_mark[page] = start_page
          visitable_count[page] = visited_pages
          page = L[page - 1]

      # If a cycle is found in the current path
      if page_mark[page] == start_page:
          cycle_length = visited_pages - visitable_count[page] + 1
          while page_mark[page] != -start_page:
              page_mark[page] = -start_page
              visitable_count[page] = cycle_length
              page = L[page - 1]
      else:
          # Ends in previously visited page; extend the count
          visited_pages += visitable_count[page]

      # Backtrack to update visitable counts
      page = start_page
      while page_mark[page] == start_page:
          visitable_count[page] = visited_pages
          visited_pages -= 1
          page = L[page - 1]

  return max(visitable_count)

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 4
    L = [4, 1, 2, 1]
    
    print("Test Case 1")
    print("Expected Return Value = 4")  # Start at page 3, visit 3->2->1->4->1 (stop)
    print("Actual Return Value   = {}".format(getMaxVisitableWebpages(N, L)))
    print("")
    
    ## Test Case 2
    N = 5
    L = [2, 4, 2, 5, 1]
    
    print("Test Case 2")
    print("Expected Return Value = 3")  # Start at page 3, visit 3->2->4->5->1->2 (stop)
    print("Actual Return Value   = {}".format(getMaxVisitableWebpages(N, L)))
    print("")
    
    ## Test Case 3
    N = 5
    L = [3, 5, 1, 2, 4]
    
    print("Test Case 3")
    print("Expected Return Value = 5")  # Start at any page, can visit all 5 pages
    print("Actual Return Value   = {}".format(getMaxVisitableWebpages(N, L)))
    print("")
