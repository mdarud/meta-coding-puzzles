// Problem: Rabbit Hole 2
// You're having a grand old time clicking through the rabbit hole that is your
// favorite online encyclopedia.

// The encyclopedia consists of N different web pages, numbered from 1 to N.
// There are M links present across the pages, the ith of which is present on
// page A{i} and links to a different page B{i}. A page may include multiple
// links, including multiple leading to the same other page.

// A session spent on this website involves beginning on one of the N pages,
// and then navigating around using the links until you decide to stop. That is,
// while on page i, you may either move to any of the pages linked to from it,
// or stop your browsing session.

// Assuming you can choose which page you begin the session on, what's the
// maximum number of different pages you can visit in a single session? Note
// that a page only counts once even if visited multiple times during the
// session.

// Constraints:
// 2 <= N <= 500,000
// 1 <= M <= 500,000
// 1 <= A, B <= N
// A{i} ≠ B{i}

// Solution
// Time Complexity: O(N + M)
// Space Complexity: O(N + M)
// Explanation:
// - We model the encyclopedia as a directed graph with pages as nodes and links as edges.
// - We use Tarjan's algorithm to find Strongly Connected Components (SCCs), since within an SCC, we can traverse all nodes freely.
// - We build a new graph (a DAG) where each SCC becomes a node and links are added between SCCs.
// - We use dynamic programming over the topological order of this DAG to compute the maximum number of unique pages visitable.
// - The answer is the maximum DP value among all SCCs.

#include <bits/stdc++.h>
using namespace std;

int getMaxVisitableWebpages(int N, int M, vector<int> A, vector<int> B) {
    vector<vector<int>> graph(N);
    for (int i = 0; i < M; ++i) {
        graph[A[i] - 1].push_back(B[i] - 1);  // Convert to 0-indexed
    }

    // Tarjan's Algorithm
    int index = 0, sccCount = 0;
    vector<int> indices(N, -1), lowlink(N), onStack(N), nodeToSCC(N);
    stack<int> stk;
    vector<vector<int>> sccs;

    function<void(int)> tarjan = [&](int u) {
        indices[u] = lowlink[u] = index++;
        stk.push(u);
        onStack[u] = true;

        for (int v : graph[u]) {
            if (indices[v] == -1) {
                tarjan(v);
                lowlink[u] = min(lowlink[u], lowlink[v]);
            } else if (onStack[v]) {
                lowlink[u] = min(lowlink[u], indices[v]);
            }
        }

        if (lowlink[u] == indices[u]) {
            vector<int> scc;
            while (true) {
                int v = stk.top();
                stk.pop();
                onStack[v] = false;
                nodeToSCC[v] = sccCount;
                scc.push_back(v);
                if (v == u) break;
            }
            sccs.push_back(scc);
            ++sccCount;
        }
    };

    for (int i = 0; i < N; ++i)
        if (indices[i] == -1)
            tarjan(i);

    // Build SCC DAG
    vector<unordered_set<int>> sccGraph(sccCount);
    vector<int> sccSize(sccCount);
    for (int i = 0; i < sccCount; ++i)
        sccSize[i] = sccs[i].size();

    for (int u = 0; u < N; ++u) {
        for (int v : graph[u]) {
            int uSCC = nodeToSCC[u];
            int vSCC = nodeToSCC[v];
            if (uSCC != vSCC)
                sccGraph[uSCC].insert(vSCC);
        }
    }

    // DP over DAG
    vector<int> indegree(sccCount, 0), dp(sccCount, 0);
    for (int u = 0; u < sccCount; ++u)
        for (int v : sccGraph[u])
            indegree[v]++;

    queue<int> q;
    for (int i = 0; i < sccCount; ++i) {
        if (indegree[i] == 0) {
            q.push(i);
            dp[i] = sccSize[i];
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : sccGraph[u]) {
            if (dp[v] < dp[u] + sccSize[v]) {
                dp[v] = dp[u] + sccSize[v];
            }
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return *max_element(dp.begin(), dp.end());
}

// ------------------------
// ✅ Test Cases
// ------------------------
int main() {
    {
        int N = 5;
        int M = 5;
        vector<int> A = {1, 2, 3, 4, 5};
        vector<int> B = {2, 3, 1, 5, 4};

        cout << "Test Case 1" << endl;
        cout << "Expected Return Value = 3" << endl;
        cout << "Actual Return Value   = " << getMaxVisitableWebpages(N, M, A, B) << endl << endl;
    }

    {
        int N = 6;
        int M = 5;
        vector<int> A = {1, 1, 2, 3, 5};
        vector<int> B = {2, 3, 4, 5, 6};

        cout << "Test Case 2" << endl;
        cout << "Expected Return Value = 4" << endl;
        cout << "Actual Return Value   = " << getMaxVisitableWebpages(N, M, A, B) << endl << endl;
    }

    {
        int N = 7;
        int M = 7;
        vector<int> A = {1, 2, 3, 4, 5, 6, 6};
        vector<int> B = {2, 3, 1, 5, 6, 7, 4};

        cout << "Test Case 3" << endl;
        cout << "Expected Return Value = 4" << endl;
        cout << "Actual Return Value   = " << getMaxVisitableWebpages(N, M, A, B) << endl << endl;
    }

    return 0;
}
