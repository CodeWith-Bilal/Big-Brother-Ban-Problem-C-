#include <iostream>
using namespace std;

long long solve(int N) {
    if (N == 1) return 0; // His 1-year-old birthday is day 0

    long long total_days = 0;

    // Add full years from year 2 to year N-1
    for (int year = 2; year < N; year++) {
        total_days += (long long)year * (long long)year;
    }

    // Now for year N: (N-1 full months) and 1 day to reach birthday
    total_days += (long long)(N - 1) * (long long)N + 1;

    return total_days;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << solve(N) << endl;
    }
    return 0;
}

