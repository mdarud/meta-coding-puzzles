// Problem: Rotary Lock
// You're trying to open a lock. The lock comes with a wheel which has the
// integers from 1 to N arranged in a circle in order around it (with integers
// 1 and N adjacent to one another). The wheel is initially pointing at 1.

// It takes 1 second to rotate the wheel by 1 unit to an adjacent integer in
// either direction, and it takes no time to select an integer once the wheel
// is pointing at it.

// The lock will open if you enter a certain code. The code consists of a
// sequence of M integers, the ith of which is C{i}. Determine the minimum
// number of seconds required to select all M of the code's integers in order.

// Constraints:
// 3 <= N <= 50,000,000
// 1 <= M <= 1,000
// 1 <= C{i} <= N

// Solution
// Time Complexity: O(M)
// Space Complexity: O(1)
// Explanation: We calculate the minimum rotation time between each consecutive position
// in the code sequence. For each position, we can rotate either clockwise or counterclockwise,
// so we take the minimum of the two possible rotation times. The rotation time between
// positions a and b is min(|a-b|, N-|a-b|), where the first term represents the direct
// rotation and the second term represents the rotation in the opposite direction around
// the circle.

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

long long getMinCodeEntryTime(int N, int M, vector<int> C) {
    long long total_time = 0;
    int current_position = 1;  // 1-based starting position

    for (int target : C) {
        int clockwise = abs(current_position - target);
        int counter_clockwise = N - clockwise;
        total_time += min(clockwise, counter_clockwise);
        current_position = target;
    }

    return total_time;
}

int main() {
    // Test Case 1
    int N = 10;
    int M = 3;
    vector<int> C = {9, 4, 8};
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 9" << endl;  // 1->9 (2 steps) + 9->4 (5 steps) + 4->8 (4 steps) = 11 steps
    cout << "Actual Return Value   = " << getMinCodeEntryTime(N, M, C) << endl;
    cout << endl;
    
    // Test Case 2
    N = 10;
    M = 4;
    C = {9, 4, 8, 1};
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 12" << endl;
    cout << "Actual Return Value   = " << getMinCodeEntryTime(N, M, C) << endl;
    cout << endl;
    
    // Test Case 3
    N = 100;
    M = 5;
    C = {73, 32, 5, 84, 50};
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 176" << endl;
    cout << "Actual Return Value   = " << getMinCodeEntryTime(N, M, C) << endl;
    
    return 0;
}
