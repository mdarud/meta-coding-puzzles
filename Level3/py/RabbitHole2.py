## Problem: Rabbit Hole 2
## You're having a grand old time clicking through the rabbit hole that is your
## favorite online encyclopedia.

## The encyclopedia consists of N different web pages, numbered from 1 to N.
## There are M links present across the pages, the ith of which is present on
## page A{i} and links to a different page B{i}. A page may include multiple
## links, including multiple leading to the same other page.

## A session spent on this website involves beginning on one of the N pages,
## and then navigating around using the links until you decide to stop. That is,
## while on page i, you may either move to any of the pages linked to from it,
## or stop your browsing session.

## Assuming you can choose which page you begin the session on, what's the
## maximum number of different pages you can visit in a single session? Note
## that a page only counts once even if visited multiple times during the
## session.

## Constraints:
## 2 <= N <= 500,000
## 1 <= M <= 500,000
## 1 <= A, B <= N
## A{i} ≠ B{i}

## Solution
## Time Complexity: O(N + M)
## Space Complexity: O(N + M)
## Explanation:
## - We model the encyclopedia as a directed graph with pages as nodes and links as edges.
## - We use Tarjan's algorithm to find Strongly Connected Components (SCCs), since within an SCC, we can traverse all nodes freely.
## - We build a new graph (a DAG) where each SCC becomes a node and links are added between SCCs.
## - We use dynamic programming over the topological order of this DAG to compute the maximum number of unique pages visitable.
## - The answer is the maximum DP value among all SCCs.

from typing import List
import sys
sys.setrecursionlimit(1 << 25)

def getMaxVisitableWebpages(N: int, M: int, A: List[int], B: List[int]) -> int:
  from collections import defaultdict

  graph = defaultdict(list)
  for u, v in zip(A, B):
      graph[u - 1].append(v - 1)

  index = 0
  indices = [-1] * N
  lowlink = [0] * N
  on_stack = [False] * N
  stack = []
  sccs = []
  node_to_scc = [0] * N

  def tarjan(u):
      nonlocal index
      indices[u] = lowlink[u] = index
      index += 1
      stack.append(u)
      on_stack[u] = True

      for v in graph[u]:
          if indices[v] == -1:
              tarjan(v)
              lowlink[u] = min(lowlink[u], lowlink[v])
          elif on_stack[v]:
              lowlink[u] = min(lowlink[u], indices[v])

      if lowlink[u] == indices[u]:
          scc = []
          while True:
              v = stack.pop()
              on_stack[v] = False
              node_to_scc[v] = len(sccs)
              scc.append(v)
              if v == u:
                  break
          sccs.append(scc)

  for u in range(N):
      if indices[u] == -1:
          tarjan(u)

  # Create new DAG of SCCs
  scc_graph = defaultdict(set)
  scc_size = [0] * len(sccs)
  for i, scc in enumerate(sccs):
      scc_size[i] = len(scc)

  for u in range(N):
      for v in graph[u]:
          u_scc = node_to_scc[u]
          v_scc = node_to_scc[v]
          if u_scc != v_scc:
              scc_graph[u_scc].add(v_scc)

  # Topological DP on DAG
  from collections import deque
  indegree = [0] * len(sccs)
  for u in scc_graph:
      for v in scc_graph[u]:
          indegree[v] += 1

  queue = deque()
  dp = [0] * len(sccs)
  for i in range(len(sccs)):
      if indegree[i] == 0:
          queue.append(i)
          dp[i] = scc_size[i]

  while queue:
      u = queue.popleft()
      for v in scc_graph[u]:
          if dp[v] < dp[u] + scc_size[v]:
              dp[v] = dp[u] + scc_size[v]
          indegree[v] -= 1
          if indegree[v] == 0:
              queue.append(v)

  return max(dp)

## Test Cases
if __name__ == "__main__":
    ## Test Case 1
    N = 5
    M = 5
    A = [1, 2, 3, 4, 5]
    B = [2, 3, 1, 5, 4]

    print("Test Case 1")
    print("Expected Return Value = 3")
    print("Actual Return Value   = {}".format(getMaxVisitableWebpages(N, M, A, B)))
    print("")

    ## Test Case 2
    N = 6
    M = 5
    A = [1, 1, 2, 3, 5]
    B = [2, 3, 4, 5, 6]

    print("Test Case 2")
    print("Expected Return Value = 4")
    print("Actual Return Value   = {}".format(getMaxVisitableWebpages(N, M, A, B)))
    print("")

    ## Test Case 3
    N = 7
    M = 7
    A = [1, 2, 3, 4, 5, 6, 6]
    B = [2, 3, 1, 5, 6, 7, 4]

    print("Test Case 3")
    print("Expected Return Value = 4")
    print("Actual Return Value   = {}".format(getMaxVisitableWebpages(N, M, A, B)))
    print("")