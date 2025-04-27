#include <bits/stdc++.h>
using namespace std;

// O(N*M) solution without nested processing loops
// Time Complexity: O(N*M) per test case
// Space Complexity: O(N*M)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        int total = N * M;

        // Store the (row, col) for each value 1…N*M
        vector<pair<int,int> > pos(total + 1);
        for (int idx = 0; idx < total; ++idx) {
            int val;
            cin >> val;
            int r = idx / M;
            int c = idx % M;
            pos[val] = make_pair(r, c);
        }

        long long actions = 0;
        // Initial move: from (0,0) to the location of button 1
        {
            pair<int,int> start = make_pair(0, 0);
            pair<int,int> target = pos[1];
            int dr = abs(target.first - start.first);
            int dc = abs(target.second - start.second);
            dr = min(dr, N - dr);
            dc = min(dc, M - dc);
            actions += dr + dc;
        }

        // Moves for buttons 2…total
        for (int v = 2; v <= total; ++v) {
            pair<int,int> prev = pos[v - 1];
            pair<int,int> cur  = pos[v];
            int dr = abs(cur.first - prev.first);
            int dc = abs(cur.second - prev.second);
            dr = min(dr, N - dr);
            dc = min(dc, M - dc);
            actions += dr + dc;
        }

        cout << actions << "\n";
    }
    return 0;
}

