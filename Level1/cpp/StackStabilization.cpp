// Problem: Stack Stabilization 
// There's a stack of N inflatable discs, with the ith disc from the top having
// an initial radius of R{i} inches.

// The stack is considered unstable if it includes at least one disc whose
// radius is larger than or equal to that of the disc directly under it. In
// other words, for the stack to be stable, each disc must have a strictly
// smaller radius than that of the disc directly under it.

// As long as the stack is unstable, you can repeatedly choose any disc of your
// choice and deflate it down to have a radius of your choice which is strictly
// smaller than the disc's prior radius. The new radius must be a positive
// integer number of inches.

// Determine the minimum number of discs which need to be deflated in order to
// make the stack stable, if this is possible at all. If it is impossible to
// stabilize the stack, return -1 instead.

// Constraints:
// 1 <= N <= 50
// 1 <= R{i} <= 1,000,000,000

// Solution
// Time Complexity: O(N)
// Space Complexity: O(1)
// Explanation: We work from the bottom of the stack upwards. For each disc, if its
// radius is greater than or equal to the maximum allowed radius (which is the radius
// of the disc below it or the previously computed maximum allowed radius), we need to
// deflate it to be one less than the maximum allowed radius. We then update the maximum
// allowed radius for the next disc above. If at any point the maximum allowed radius
// becomes 0 or negative, it's impossible to stabilize the stack.

#include <iostream>
#include <vector>
using namespace std;

int getMinimumDeflatedDiscCount(int N, vector<int> R) {
    int count = 0;
    int max_radius = R[N - 1];  // Bottom disc radius

    for (int i = N - 2; i >= 0; --i) {
        if (R[i] >= max_radius) {
            max_radius -= 1;
            if (max_radius <= 0) {
                return -1;
            }
            count++;
        } else {
            max_radius = R[i];
        }
    }

    return count;
}

int main() {
    // Test Case 1
    int N = 5;
    vector<int> R = {2, 5, 3, 6, 5};  // Top to bottom
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 3" << endl;  // Need to deflate discs at positions 0, 2, and 3
    cout << "Actual Return Value   = " << getMinimumDeflatedDiscCount(N, R) << endl;
    cout << endl;
    
    // Test Case 2
    N = 3;
    R = {100, 100, 100};  // Top to bottom
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 2" << endl;  // Need to deflate top two discs
    cout << "Actual Return Value   = " << getMinimumDeflatedDiscCount(N, R) << endl;
    cout << endl;
    
    // Test Case 3
    N = 4;
    R = {6, 5, 4, 3};  // Already stable
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 0" << endl;  // No deflation needed
    cout << "Actual Return Value   = " << getMinimumDeflatedDiscCount(N, R) << endl;
    cout << endl;
    
    // Test Case 4
    N = 4;
    R = {1, 2, 3, 4};  // Impossible to stabilize
    
    cout << "Test Case 4" << endl;
    cout << "Expected Return Value = -1" << endl;  // Impossible to stabilize
    cout << "Actual Return Value   = " << getMinimumDeflatedDiscCount(N, R) << endl;
    
    return 0;
}
