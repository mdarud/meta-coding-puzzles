// Problem: Missing Mail
// You are the manager of a mail room which is frequently subject to theft. A
// period of N days is about to occur, such that on the ith day, the following
// sequence of events will occur in order:

//  1. A package with a value of V{i} dollars will get delivered to the mail
//     room (unless V{i} = 0, in which case no package will get delivered).
//
//  2. You can choose to pay C dollars to enter the mail room and collect all of
//     the packages there (removing them from the room), and then leave the
//     room.
//
//  3. With probability S, all packages currently in the mail room will get
//     stolen (and therefore removed from the room).

// Note that you're aware of the delivery schedule V{1..N}, but can only observe
// the state of the mail room when you choose to enter it, meaning that you
// won't immediately be aware of whether or not packages were stolen at the end
// of any given day.

// Your profit after the Nth day will be equal to the total value of all
// packages which you collected up to that point, minus the total amount of
// money you spent on entering the mail room.

// Please determine the maximum expected profit you can achieve (in dollars).

// Note: Your return value must have an absolute or relative error of at most
// 10^(-6) to be considered correct.

// Constraints:
// 1 <= N <= 4000
// 0 <= V{i} <= 1000
// 1 <= C <= 1000
// 0.0 <= S <= 1.0

// Solution
// Time Complexity: O(N²)
// Space Complexity: O(N)
// Explanation: We use dynamic programming to solve this problem. For each day, we have
// two choices: either collect the packages or leave them. If we collect, we pay C dollars
// and get all the packages. If we leave them, there's a probability S that they'll be stolen.
// We use a 1D DP array where dp[i] represents the maximum expected profit up to day i.
// For each day, we consider all possible previous days when we might have last collected
// packages, and choose the option that maximizes our expected profit.

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

double getMaxExpectedProfit(int N, vector<int> V, int C, double S) {
    vector<double> exp_sum;
    double curr = 0.0;
  
    // Calculate the cumulative expected value adjusted by factor (1 - S)
    for (int v : V) {
        curr *= (1.0 - S);
        curr += v;
        exp_sum.push_back(curr);
    }
    exp_sum.push_back(0.0);  // Final value for boundary condition
  
    // Initialize dp array
    vector<double> dp(N + 1, 0.0);
  
    // Iterate over each day to compute the max expected profit
    for (int i = 1; i <= N; ++i) {
        double max_val = -1e18;
  
        for (int j = i; j >= 1; --j) {
            // Calculate decayed portion of previous sum
            double decay_factor = pow(1.0 - S, i - j + 1);
            double previous_sum = (j >= 2) ? exp_sum[j - 2] * decay_factor : 0.0;
  
            double profit = max(0.0, exp_sum[i - 1] - previous_sum - C);
            max_val = max(max_val, dp[j - 1] + profit);
        }
  
        dp[i] = max_val;
    }
  
    return dp[N];
}

int main() {
    // Test Case 1
    int N = 5;
    vector<int> V = {10, 2, 8, 6, 4};
    int C = 5;
    double S = 0.0;
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 25.0" << endl;  // Collect on day 5, get all packages (10+2+8+6+4) - 5 = 25
    cout << "Actual Return Value   = " << getMaxExpectedProfit(N, V, C, S) << endl;
    cout << endl;
    
    // Test Case 2
    N = 5;
    V = {10, 2, 8, 6, 4};
    C = 5;
    S = 1.0;
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 15.0" << endl;  // Collect every day, (10-5) + (2-5) + (8-5) + (6-5) + (4-5) = 5
    cout << "Actual Return Value   = " << getMaxExpectedProfit(N, V, C, S) << endl;
    cout << endl;
    
    // Test Case 3
    N = 3;
    V = {20, 0, 10};
    C = 10;
    S = 0.5;
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 15.0" << endl;  // Optimal strategy depends on probability
    cout << "Actual Return Value   = " << getMaxExpectedProfit(N, V, C, S) << endl;
    
    return 0;
}
