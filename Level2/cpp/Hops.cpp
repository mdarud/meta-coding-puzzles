// Problem: Hops
// A family of frogs in a pond are traveling towards dry land to hibernate. They
// hope to do so by hopping across a trail of N lily pads, numbered from 1 to N
// in order.

// There are F frogs, numbered from 1 to F. Frog i is currently perched atop
// lily pad P{i}. No two frogs are currently on the same lily pad. Lily pad N is
// right next to the shore, and none of the frogs are initially on lily pad N.

// Each second, one frog may hop along the trail towards lily pad N. When a frog
// hops, it moves to the nearest lily pad after its current lily pad which is
// not currently occupied by another frog (hopping over any other frogs on
// intermediate lily pads along the way). If this causes it to reach lily pad N,
// it will immediately exit onto the shore. Multiple frogs may not
// simultaneously hop during the same second.

// Assuming the frogs work together optimally when deciding which frog should
// hop during each second, determine the minimum number of seconds required for
// all F of them to reach the shore.

// Constraints:
// 2 <= N <= 10^(12)
// 1 <= F <= 500,000
// 1 <= P{i} <= N - 1

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Solution
Time Complexity: O(F)
Space Complexity: O(1)
Explanation:
This can be solved with a deceptively simple formula: N - min(P)
Here's the reasoning behind it:

Start with the more verbose form: F + (N - F - 1) - (min(P) - 1)

- The 'F' accounts for each frog taking 1 second to hop off once they reach the end.
- (N - F - 1) computes how many empty lily pads are between frogs and the end.
  We subtract F for the pads already occupied, and 1 for the last pad (which no frog actually lands on).
- min(P) - 1 is the number of pads before the earliest frog, representing idle time before hopping starts.

Example:
N = 7, F = 2, P = [3, 5] → pond layout: [ . . A . B . . ]
The earliest frog is at position 3 (0-based index 2), so min(P) = 3.
Result = N - min(P) = 7 - 3 = 4 seconds.
*/

long long getSecondsRequired(long long N, int F, vector<long long> P) {
    sort(P.begin(), P.end());  // Sort positions from shore to end
    return N - P[0];
}

int main() {
    // Test Case 1
    long long N = 7;
    int F = 2;
    vector<long long> P = {3, 5};
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 4" << endl;  // 7 - 3 = 4
    cout << "Actual Return Value   = " << getSecondsRequired(N, F, P) << endl;
    cout << endl;
    
    // Test Case 2
    N = 10;
    F = 3;
    P = {2, 4, 7};
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 8" << endl;  // 10 - 2 = 8
    cout << "Actual Return Value   = " << getSecondsRequired(N, F, P) << endl;
    cout << endl;
    
    // Test Case 3
    N = 100;
    F = 5;
    P = {10, 20, 30, 40, 50};
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 90" << endl;  // 100 - 10 = 90
    cout << "Actual Return Value   = " << getSecondsRequired(N, F, P) << endl;
    
    return 0;
}
