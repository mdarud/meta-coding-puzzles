// Problem: Boss Fight
// There are N warriors, the ith of which has a health of H{i} units and can 
// deal D{i} units of damage per second. The are confronting a boss who has
// unlimited health and can deal B units of damage per second. Both the 
// warriors and the boss deal damage continuously - for example, in half a
// second, the bossdeals B/2 units of damage.

// The warriors feel it would be unfair for many of them to fight the boss at 
// once, so they'll select just two representatives to go into battle. One 
// warrior {i} will be the front line and a different warrior {j} will back
// them up. During the battle, the boss will attack warrior {i} until that
// warrior is defeated (that is until the boss has dealt H{i} units of damage to
// them), and will then attack warrior {j} until that warrior is also defeated,
// at which point the battle will end. Along the way, each of the two warriors
// will do damage to the boss as long as they are undefeated.

// Of course, the warriors will never prevail, but they'd like to determine the 
// maximum amount of damage they could deal to the boss for any choice of warriors
// {i} and {j} before the battle ends.

// Constraints:
// 2 <= N <= 500,000
// 1 <= H{i} <= 1,000,000,000
// 1 <= D{i} <= 1,000,000,000
// 1 <= B <= 1,000,000,000

// Solution:
// Time Complexity: O(N * T) — where T is typically small (number of iterations to converge to optimal pair).
// Space Complexity: O(N)
// Explanation:
// We precompute H[i] * D[i] for each warrior.
// We iteratively search for the pair that maximizes total damage,
// alternating the front-line warrior based on which pair improves the result,
// reducing full O(N^2) brute force to something much faster in practice.

#include <vector>
#include <algorithm>
using namespace std;

double getMaxDamageDealt(int N, vector<int> H, vector<int> D, int B) {
    vector<long long> C(N);
    for (int i = 0; i < N; ++i) {
        C[i] = 1LL * H[i] * D[i];  // prevent overflow
    }

    long long max_damage = 0;
    int best = 0;
    bool improved = true;

    while (improved) {
        improved = false;
        int next_best = 0;

        for (int i = 0; i < N; ++i) {
            if (i == best) continue;

            long long overlap = max(1LL * H[best] * D[i], 1LL * H[i] * D[best]);
            long long total = C[best] + C[i] + overlap;

            if (total > max_damage) {
                max_damage = total;
                next_best = i;
                improved = true;
            }
        }

        best = next_best;
    }

    return static_cast<double>(max_damage) / B;
}


#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

double getMaxDamageDealt(int N, vector<int> H, vector<int> D, int B);

int main() {
    {
        int N = 3;
        vector<int> H = {10, 8, 5};
        vector<int> D = {5, 10, 20};
        int B = 5;
        cout << "Test Case 1" << endl;
        cout << "Expected Return Value = 54.0" << endl;
        cout << "Actual Return Value   = " << fixed << setprecision(1) << getMaxDamageDealt(N, H, D, B) << endl << endl;
    }

    {
        int N = 2;
        vector<int> H = {100, 200};
        vector<int> D = {1, 2};
        int B = 10;
        cout << "Test Case 2" << endl;
        cout << "Expected Return Value = 70.0" << endl;
        cout << "Actual Return Value   = " << fixed << setprecision(1) << getMaxDamageDealt(N, H, D, B) << endl << endl;
    }

    {
        int N = 4;
        vector<int> H = {1, 2, 3, 4};
        vector<int> D = {4, 3, 2, 1};
        int B = 2;
        cout << "Test Case 3" << endl;
        cout << "Expected Return Value = 11.0" << endl;
        cout << "Actual Return Value   = " << fixed << setprecision(1) << getMaxDamageDealt(N, H, D, B) << endl << endl;
    }

    return 0;
}
