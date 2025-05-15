#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int getArtisticPhotographCount(int N, const string& C, int X, int Y) {
    vector<int> prefix_p(N + 1, 0);
    vector<int> prefix_b(N + 1, 0);

    // Build prefix sums
    for (int i = 0; i < N; i++) {
        prefix_p[i + 1] = prefix_p[i] + (C[i] == 'P' ? 1 : 0);
        prefix_b[i + 1] = prefix_b[i] + (C[i] == 'B' ? 1 : 0);
    }

    int count = 0;

    for (int i = 0; i < N; i++) {
        if (C[i] == 'A') {
            int left_min = max(0, i - Y);
            int left_max = i - X;
            int right_min = i + X;
            int right_max = min(N - 1, i + Y);

            // P left, B right
            int left_p = 0;
            if (left_min <= left_max)
                left_p = prefix_p[left_max + 1] - prefix_p[left_min];

            int right_b = 0;
            if (right_min <= right_max)
                right_b = prefix_b[right_max + 1] - prefix_b[right_min];

            count += left_p * right_b;

            // B left, P right
            int left_b = 0;
            if (left_min <= left_max)
                left_b = prefix_b[left_max + 1] - prefix_b[left_min];

            int right_p = 0;
            if (right_min <= right_max)
                right_p = prefix_p[right_max + 1] - prefix_p[right_min];

            count += left_b * right_p;
        }
    }

    return count;
}

int main() {
    int N = 6;
    string C = "APBAPA";
    int X = 1, Y = 2;

    cout << getArtisticPhotographCount(N, C, X, Y) << endl;
}
