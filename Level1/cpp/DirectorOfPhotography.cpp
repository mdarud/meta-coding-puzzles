// Problem: Director of Photography
// A photography set consists of N cells in a row, numbered from 1 to N in
// order, and can be represented by a string C of length N. Each cell i is one
// of the following types (indicated by C{i}, the ith character of C):

//      If C{i} = 'P', it is allowed to contain a photographer
//      If C{i} = 'A', it is allowed to contain an actor
//      If C{i} = 'B', it is allowed to contain a backdrop
//      If C{i} = '.', it must be left empty

// A photograph consists of a photographer, an actor, and a backdrop, such that
// each of them is placed in a valid cell, and such that the actor is between
// the photographer and the backdrop. Such a photograph is considered artistic
// if the distance between the photographer and the actor is between X and Y
// cells (inclusive), and the distance between the actor and the backdrop is
// also between X and Y cells (inclusive). The distance between cells i and j
// is |i - j| (the absolute value of the difference between their indices).

// Determine the number of different artistic photographs which could
// potentially be taken at the set. Two photographs are considered different if
// they involve a different photographer cell, actor cell, and/or backdrop cell.

// Constraints:
// 1 <= N <= 200
// 1 <= X <= Y <= N

// Solution
// Time Complexity: O(N)
// Space Complexity: O(N)
// Explanation: We use prefix sums to efficiently count the number of photographers
// and backdrops within specific distance ranges from each actor. For each actor position,
// we check both possible arrangements: photographer on the left with backdrop on the right,
// and backdrop on the left with photographer on the right. The prefix sums allow us to
// quickly determine how many valid photographers and backdrops are within the required
// distance range without having to iterate through the string multiple times.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int getArtisticPhotographCount(int N, const string& C, int X, int Y) {
    vector<int> prefix_p(N + 1, 0);
    vector<int> prefix_b(N + 1, 0);

    // Build prefix sums
    for (int i = 0; i < N; i++) {
        prefix_p[i + 1] = prefix_p[i] + (C[i] == 'P' ? 1 : 0);
        prefix_b[i + 1] = prefix_b[i] + (C[i] == 'B' ? 1 : 0);
    }

    int count = 0;

    for (int i = 0; i < N; i++) {
        if (C[i] == 'A') {
            int left_min = max(0, i - Y);
            int left_max = i - X;
            int right_min = i + X;
            int right_max = min(N - 1, i + Y);

            // P left, B right
            int left_p = 0;
            if (left_min <= left_max)
                left_p = prefix_p[left_max + 1] - prefix_p[left_min];

            int right_b = 0;
            if (right_min <= right_max)
                right_b = prefix_b[right_max + 1] - prefix_b[right_min];

            count += left_p * right_b;

            // B left, P right
            int left_b = 0;
            if (left_min <= left_max)
                left_b = prefix_b[left_max + 1] - prefix_b[left_min];

            int right_p = 0;
            if (right_min <= right_max)
                right_p = prefix_p[right_max + 1] - prefix_p[right_min];

            count += left_b * right_p;
        }
    }

    return count;
}

int main() {
    // Test Case 1
    int N = 5;
    string C = "APABA";
    int X = 1, Y = 2;
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 1" << endl;
    cout << "Actual Return Value   = " << getArtisticPhotographCount(N, C, X, Y) << endl;
    cout << endl;
    
    // Test Case 2
    N = 5;
    C = "APBPA";
    X = 2, Y = 3;
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 0" << endl;
    cout << "Actual Return Value   = " << getArtisticPhotographCount(N, C, X, Y) << endl;
    cout << endl;
    
    // Test Case 3
    N = 8;
    C = "PBAAPA.B";
    X = 1, Y = 3;
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 3" << endl;
    cout << "Actual Return Value   = " << getArtisticPhotographCount(N, C, X, Y) << endl;
    
    return 0;
}
