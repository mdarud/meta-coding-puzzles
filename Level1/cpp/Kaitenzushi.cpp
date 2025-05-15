// Problem: Kaitenzushi
// There are N dishes in a row on a kaiten belt, with the ith dish being of type
// D{i}. Some dishes may be of the same type as one another.

// Kaiten Belt: {https://en.wikipedia.org/wiki/Conveyor_belt_sushi}

// You're very hungry, but you'd also like to keep things interesting. The N
// dishes will arrive in front of you, one after another in order, and for each
// one you'll eat it as long as it isn't the same type as any of the previous K
// dishes you've eaten. You eat very fast, so you can consume a dish before the
// next one gets to you. Any dishes you choose not to eat as they pass will be
// eaten by others.

// Determine how many dishes you'll end up eating.

// Constraints:
// 1 <= N <= 500,000
// 1 <= K <= N
// 1 <= D{i} <= 1,000,000

// Solution
// Time Complexity: O(N)
// Space Complexity: O(min(N, K))
// Explanation: We use a combination of a queue and a hash set to keep track of
// the last K dishes we've eaten. The queue maintains the order of dishes, and the
// hash set allows for O(1) lookups to check if a dish type has been recently eaten.
// For each new dish, we check if it's already in our recent dishes. If not, we eat it
// and add it to our recent dishes. If our recent dishes list exceeds K, we remove the
// oldest dish from both the queue and the hash set.

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

int getMaximumEatenDishCount(int N, const vector<int>& D, int K) {
    unordered_set<int> recent;
    queue<int> window;
    int count = 0;

    for (int dish : D) {
        if (recent.find(dish) == recent.end()) {
            count++;
            if ((int)window.size() == K) {
                int old_dish = window.front();
                window.pop();
                recent.erase(old_dish);
            }
            window.push(dish);
            recent.insert(dish);
        }
    }

    return count;
}

int main() {
    // Test Case 1
    int N = 6;
    vector<int> D = {1, 2, 3, 3, 2, 1};
    int K = 1;
    
    cout << "Test Case 1" << endl;
    cout << "Expected Return Value = 5" << endl;  // Can't eat the second 3, but can eat everything else
    cout << "Actual Return Value   = " << getMaximumEatenDishCount(N, D, K) << endl;
    cout << endl;
    
    // Test Case 2
    N = 7;
    D = {1, 2, 1, 2, 1, 2, 1};
    K = 2;
    
    cout << "Test Case 2" << endl;
    cout << "Expected Return Value = 4" << endl;  // Eat dishes at positions 0, 1, 4, 6
    cout << "Actual Return Value   = " << getMaximumEatenDishCount(N, D, K) << endl;
    cout << endl;
    
    // Test Case 3
    N = 5;
    D = {1, 2, 3, 4, 5};
    K = 5;
    
    cout << "Test Case 3" << endl;
    cout << "Expected Return Value = 5" << endl;  // All dishes are different, so eat all of them
    cout << "Actual Return Value   = " << getMaximumEatenDishCount(N, D, K) << endl;
    
    return 0;
}
