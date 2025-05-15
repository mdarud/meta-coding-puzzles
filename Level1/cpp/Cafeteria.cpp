// Problem: Cafeteria
// A cafeteria table consists of a row of N seats, numbered from 1 to N from
// left to right. Social distancing guidelines require that every diner be
// seated such that K seats to their left and K seats to their right (or all the
// remaining seats to that side if there are fewer than K) remain empty.

// There are currently M diners seated at the table, the ith of whom is in seat
// S{i}. No two diners are sitting in the same seat, and the social distancing
// guidelines are satisfied.

// Determine the maximum number of additional diners who can potentially sit at
// the table without social distancing guidelines being violated for any new or
// existing diners, assuming that the existing diners cannot move and that the
// additional diners will cooperate to maximize how many of them can sit down.

// Constraints:
// 1 <= N <= 10^(15)
// 1 <= K <= N
// 1 <= M <= 500,000
// M <= N
// 1 <= S{i} <= N

// Solution
// Time Complexity: O(M log M)
// Space Complexity: O(M)
// Explanation: We use a greedy approach to place additional diners. First, we sort the
// positions of existing diners. Then we calculate how many additional diners can fit in
// each segment: between the start of the table and the first diner, between consecutive
// diners, and between the last diner and the end of the table. For each segment, we can
// place a diner every (K+1) positions to maintain social distancing. The formula
// (segment_length - 1) / (K + 1) gives us the number of additional diners that can fit
// in a segment of a given length.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long getMaxAdditionalDinersCount(long long N, long long K, int M, vector<long long> S) {
    // Copy the input vector and sort it
    vector<long long> sortedS = S;
    sort(sortedS.begin(), sortedS.end());

    long long additional_diners = (sortedS[0] - 1) / (K + 1);

    // Calculate additional diners between each pair of occupied seats
    for (int i = 1; i < sortedS.size(); i++) {
        additional_diners += (sortedS[i] - sortedS[i-1] - K - 1) / (K + 1);
    }

    // Calculate additional diners after the last occupied seat
    additional_diners += (N - sortedS.back()) / (K + 1);

    return additional_diners;
}

int main() {
    // Test Case 1
    long long N = 10;
    long long K = 1;
    int M = 2;
    vector<long long> S = {2, 6};
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 3" << endl;  // Can add diners at positions 4, 8, and 10
    cout << "Actual Return Value   = " << getMaxAdditionalDinersCount(N, K, M, S) << endl;
    cout << endl;
    
    // Test Case 2
    N = 15;
    K = 2;
    M = 3;
    S = {11, 6, 14};
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 1" << endl;  // Can add a diner at position 3
    cout << "Actual Return Value   = " << getMaxAdditionalDinersCount(N, K, M, S) << endl;
    cout << endl;
    
    // Test Case 3
    N = 100;
    K = 3;
    M = 1;
    S = {50};
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 16" << endl;  // Can add diners at positions 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 54, 58, 62, 66, 70
    cout << "Actual Return Value   = " << getMaxAdditionalDinersCount(N, K, M, S) << endl;
    
    return 0;
}
