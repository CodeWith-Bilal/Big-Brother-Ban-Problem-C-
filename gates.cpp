#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1000000007;
const int MAXN = 1005;

long long dp[MAXN][2];
int a[MAXN];

int apply_gate(int x, int y, char gate) {
    if (gate == '&') return x & y;
    if (gate == '|') return x | y;
    return x ^ y;
}

void add_mod(long long &x, long long y) {
    x = (x + y) % MOD;
}

int main() {
    int T;
    cin >> T;
    if (!cin || T < 1 || T > 100) return 0;

    for (int t = 0; t < T; t++) {
        int N;
        cin >> N;
        if (!cin || N < 1 || N > 1000) continue;

        for (int i = 0; i < N; i++) {
            cin >> a[i];
            if (!cin) break;
        }

        memset(dp, 0, sizeof(dp));
        dp[0][a[0]] = 1;

        for (int i = 1; i < N; i++) {
            char gates[] = {'&', '|', '^'};
            for (int g = 0; g < 3; g++) {
                char gate = gates[g];
                for (int prev_val = 0; prev_val <= 1; prev_val++) {
                    if (dp[i-1][prev_val] == 0) continue;
                    int curr_val = a[i];
                    int result = apply_gate(prev_val, curr_val, gate);
                    add_mod(dp[i][result], dp[i-1][prev_val]);
                }
            }
        }

        long long num_parentheses = (long long)N * (N + 1) / 2;
        long long ans = (dp[N-1][1] * num_parentheses) % MOD;
        cout << ans << endl;
    }

    return 0;
}
