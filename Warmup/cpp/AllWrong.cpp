// Problem: All Wrong
// There's a multiple-choice test with N questions, numbered from 1 to N. Each
// question has 2 answer options, labelled A and B. You know that the correct
// answer for the ith question is the ith character in the string C, which is
// either "A" or "B", but you want to get a score of 0 on this test by answering
// every question incorrectly.

// Your task is to implement the function getWrongAnswers(N, C) which returns a
// string with N characters, the ith of which is the answer you should give for
// question i in order to get it wrong (either "A" or "B").

// Constraints:
// 1 <= N <= 100
// C{i} ∈ {'A', 'B'}

// Solution
// Time Complexity: O(N)
// Space Complexity: O(N)

#include <iostream>
#include <string>
using namespace std;

string getWrongAnswers(int N, const string& C) {
    string result;
    for (char ch : C) {
        if (ch == 'A') {
            result.push_back('B');
        } else {
            result.push_back('A');
        }
    }
    return result;
}

int main() {
    // Example usage:
    int N = 5;
    string C = "ABABA";
    cout << "Wrong answers: " << getWrongAnswers(N, C) << endl;
    return 0;
}