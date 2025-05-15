// Problem: Rabbit Hole
// You're having a grand old time clicking through the rabbit hole that is your
// favorite online encyclopedia.

// The encyclopedia consists of N different web pages, numbered from 1 to N.
// Each page i contains nothing but a single link to a different page L{i}.

// A session spent on this website involves beginning on one of the N pages,
// and then navigating around using the links until you decide to stop. That is,
// while on page i, you may either move to page L{i}, or stop your browsing
// session.

// Assuming you can choose which page you begin the session on, what's the
// maximum number of different pages you can visit in a single session? Note
// that a page only counts once even if visited multiple times during the
// session.

// Constraints:
// 2 <= N <= 500,000
// 1 <= L{i} <= N
// L{i} ≠ i

// Solution
// Time Complexity: O(N)
// Space Complexity: O(N)
// Explanation: We use a modified depth-first search (DFS) approach to find the maximum
// number of unique pages that can be visited in a single session. For each unvisited page,
// we start a DFS traversal and keep track of the number of pages visited. If we encounter
// a cycle, we calculate the cycle length and update the visitable count for all pages in the
// cycle. If we encounter a previously visited page, we extend the count by adding the number
// of pages visitable from that page. We then backtrack to update the visitable counts for
// all pages in the current path. The maximum visitable count across all pages is our answer.

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int getMaxVisitableWebpages(int N, vector<int> L) {
    vector<int> page_mark(N + 1, 0);        // 1-based index
    vector<int> visitable_count(N + 1, 0);  // Stores number of pages visitable from each page

    for (int start_page = 1; start_page <= N; ++start_page) {
        if (page_mark[start_page] != 0)
            continue;

        int page = start_page;
        int visited_pages = 0;

        // Forward traversal
        while (page_mark[page] == 0) {
            ++visited_pages;
            page_mark[page] = start_page;
            visitable_count[page] = visited_pages;
            page = L[page - 1];  // 0-based index in L
        }

        // Cycle detection
        if (page_mark[page] == start_page) {
            int cycle_start = page;
            int cycle_length = visited_pages - visitable_count[page] + 1;

            // Mark the entire cycle
            while (page_mark[page] != -start_page) {
                page_mark[page] = -start_page;
                visitable_count[page] = cycle_length;
                page = L[page - 1];
            }
        } else {
            // Chain ends at previously visited path
            visited_pages += visitable_count[page];
        }

        // Backtrack to update visitable counts
        page = start_page;
        while (page_mark[page] == start_page) {
            visitable_count[page] = visited_pages--;
            page = L[page - 1];
        }
    }

    return *max_element(visitable_count.begin(), visitable_count.end());
}

int main() {
    // Test Case 1
    int N = 4;
    vector<int> L = {4, 1, 2, 1};
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 4" << endl;  // Start at page 3, visit 3->2->1->4->1 (stop)
    cout << "Actual Return Value   = " << getMaxVisitableWebpages(N, L) << endl;
    cout << endl;
    
    // Test Case 2
    N = 5;
    L = {2, 4, 2, 5, 1};
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 3" << endl;  // Start at page 3, visit 3->2->4->5->1->2 (stop)
    cout << "Actual Return Value   = " << getMaxVisitableWebpages(N, L) << endl;
    cout << endl;
    
    // Test Case 3
    N = 5;
    L = {3, 5, 1, 2, 4};
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 5" << endl;  // Start at any page, can visit all 5 pages
    cout << "Actual Return Value   = " << getMaxVisitableWebpages(N, L) << endl;
    
    return 0;
}
