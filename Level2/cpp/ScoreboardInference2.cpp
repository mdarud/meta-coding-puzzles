// Problem: Scoreboard Inference 2
// You are spectating a programming contest with N competitors, each trying to
// independently solve the same set of programming problems. Each problem has a
// point value, which is either 1, 2 or 3.

// On the scoreboard, you observe that the iith competitor has attained a score
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
// Explanation: This is an extension of the Level 1 problem, but now with three possible
// point values (1, 2, and 3). We need to handle several cases:
// 1. If any score has remainder 1 when divided by 3, we need at least one 1-point problem.
// 2. If any score has remainder 2 when divided by 3, we need at least one 2-point problem.
// 3. The maximum number of 3-point problems is max_score / 3.
// 4. There are special cases where we can optimize the number of problems:
//    a. If max_score is divisible by 3 and we need both 1-point and 2-point problems,
//       we can replace a 3-point problem with a 1-point and a 2-point problem.
//    b. If we need a 1-point problem but no one has a score of exactly 1, and max_score
//       has remainder 1 when divided by 3, we can check if we can optimize by using
//       a 1-point problem instead of a 3-point problem.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int getMinProblemCount(int N, const vector<int> S) {
    bool has_score_of_one = false;
    bool needs_one_point = false;
    bool needs_two_point = false;

    int max_score = 0, second_max_score = 0;

    for (int score : S) {
        if (score % 3 == 1) {
            needs_one_point = true;
            if (score == 1) {
                has_score_of_one = true;
            }
        } else if (score % 3 == 2) {
            needs_two_point = true;
        }

        if (score > max_score) {
            second_max_score = max_score;
            max_score = score;
        } else if (score > second_max_score && score != max_score) {
            second_max_score = score;
        }
    }

    int problem_count = (max_score / 3);
    if (needs_one_point) {
        problem_count += 1;
    }
    if (needs_two_point) {
        problem_count += 1;
    }

    if (max_score % 3 == 0 && needs_one_point && needs_two_point) {
        problem_count -= 1;
    } else if (needs_one_point && !has_score_of_one) {
        if (max_score % 3 == 1 && second_max_score != max_score - 1) {
            problem_count -= 1;
        }
    }

    return problem_count;
}

int main() {
    // Test Case 1
    int N = 4;
    vector<int> S = {1, 2, 3, 6};
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 3" << endl;  // 1-point, 2-point, and 3-point problems
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    cout << endl;
    
    // Test Case 2
    N = 3;
    S = {3, 6, 9};
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 3" << endl;  // All scores divisible by 3, so 3 3-point problems
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    cout << endl;
    
    // Test Case 3
    N = 5;
    S = {2, 4, 5, 7, 8};
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 4" << endl;  // Need 1-point, 2-point, and 2 3-point problems
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    cout << endl;
    
    // Test Case 4
    N = 3;
    S = {6, 7, 8};
    
    cout << "Test Case 4" << endl;
    cout << "Expected Return Value = 3" << endl;  // Special case optimization
    cout << "Actual Return Value   = " << getMinProblemCount(N, S) << endl;
    
    return 0;
}
