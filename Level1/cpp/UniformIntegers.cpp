// Problem: Uniform Integers
// A positive integer is considered uniform if all of its digits are equal. For
// example, 222 is uniform, while 223 is not.

// Given two positive integers A and B, determine the number of uniform integers
// between A and B, inclusive.

// Constraints:
// 1 <= A <= B <= 10^(12)

// Solution
// Time Complexity: O(log B)
// Space Complexity: O(1)
// Explanation: We generate all possible uniform integers by starting with single-digit
// numbers (1-9) and repeatedly appending the same digit to create larger uniform numbers
// (like 11, 111, 1111, etc.) until we exceed B. We count those that fall within the
// range [A, B]. Since there are at most 9 * log10(B) uniform integers less than B,
// the time complexity is O(log B).

#include <iostream>
using namespace std;

int getUniformIntegerCountInInterval(long long A, long long B) {
    int count = 0;

    for (int d = 1; d <= 9; ++d) {
        long long num = d;
        while (num <= B) {
            if (num >= A) {
                count++;
            }
            num = num * 10 + d;
        }
    }

    return count;
}

int main() {
    // Test Case 1
    long long A = 1;
    long long B = 100;
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 18" << endl;  // 1-9 and 11, 22, 33, 44, 55, 66, 77, 88, 99
    cout << "Actual Return Value   = " << getUniformIntegerCountInInterval(A, B) << endl;
    cout << endl;
    
    // Test Case 2
    A = 100;
    B = 1000;
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 9" << endl;  // 111, 222, 333, 444, 555, 666, 777, 888, 999
    cout << "Actual Return Value   = " << getUniformIntegerCountInInterval(A, B) << endl;
    cout << endl;
    
    // Test Case 3
    A = 1000;
    B = 10000;
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 9" << endl;  // 1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999
    cout << "Actual Return Value   = " << getUniformIntegerCountInInterval(A, B) << endl;
    
    return 0;
}
