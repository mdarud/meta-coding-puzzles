// Problem: Scoreboard Inference
// You are spectating a programming contest with N competitors, each trying to
// independently solve the same set of programming problems. Each problem has a
// point value, which is either 1 or 2.

// On the scoreboard, you observe that the ith competitor has attained a score
// of S{i}, which is a positive integer equal to the sum of the point values of
// all the problems they have solved.

// The scoreboard does not display the number of problems in the contest, nor
// their point values. Using the information available, you would like to
// determine the minimum possible number of problems in the contest.

// Constraints:
// 1 <= N <= 500,000
// 1 <= S{i} <= 1,000,000,000

// Solution
// Time Complexity: O(N)
// Space Complexity: O(1)
// Explanation: To minimize the number of problems, we want to use as many 2-point
// problems as possible. If all scores are even, we can achieve them using only 2-point
// problems, so the minimum number of problems would be max_score / 2. If any score is odd,
// we need at least one 1-point problem, and the rest can be 2-point problems. In this case,
// the minimum number of problems would be (max_score // 2) + 1.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int getMinProblemCount(int N, const vector<int>& S) {
    int max_s = *max_element(S.begin(), S.end());
    bool has_odd = false;

    for (int score : S) {
        if (score % 2 == 1) {
            has_odd = true;
            break;
        }
    }

    return (max_s / 2) + (has_odd ? 1 : 0);
}

int main() {
    // Test Case 1
    int N = 4;
    vector<int> S = {1, 2, 3, 4};
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 3" << endl;  // max_score = 4, has odd scores, so (4/2)+1 = 3
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    cout << endl;
    
    // Test Case 2
    N = 3;
    S = {4, 6, 8};
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 4" << endl;  // max_score = 8, all even, so 8/2 = 4
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    cout << endl;
    
    // Test Case 3
    N = 5;
    S = {2, 4, 6, 8, 10};
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 5" << endl;  // max_score = 10, all even, so 10/2 = 5
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    
    return 0;
}
