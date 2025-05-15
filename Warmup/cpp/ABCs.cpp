// Problem: ABCs
// Given three integers A, B, and C, determine their sum.

// Your task is to implement the function getSum(A, B, C) which returns the sum
// A + B + C.

// Constraints:
// 1 <= A, B, C <= 100

// Solution
// Time Complexity: O(1)
// Space Complexity: O(1)

#include <iostream>
using namespace std;

int getSum(int A, int B, int C) {
    return A + B + C;
}

int main() {
    // Example usage:
    int A = 5, B = 10, C = 15;
    cout << "The sum is: " << getSum(A, B, C) << endl;
    return 0;
}
