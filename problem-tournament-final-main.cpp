#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        vector<string> names(N);
        for (int i = 0; i < N; ++i) {
            cin >> names[i];
        }

        vector<long long> power(N);
        for (int i = 0; i < N; ++i) {
            cin >> power[i];
        }

        deque<pair<string, long long> > dq;
        for (int i = 0; i < N; ++i) {
            dq.push_back(pair<string, long long>(names[i], power[i]));
        }

        while (dq.size() > 1) {
            pair<string, long long> a = dq.front(); dq.pop_front();
            pair<string, long long> b = dq.front(); dq.pop_front();
            pair<string, long long> winner;

            if (a.second > b.second) {
                winner = a;
                if (a.first != "1337")
                    winner.second += b.second;
            } else if (b.second > a.second) {
                winner = b;
                if (b.first != "1337")
                    winner.second += a.second;
            } else {
                winner.first = a.first + b.first;
                winner.second = a.second + b.second;
            }

            dq.push_back(winner);
        }

        cout << dq.front().first << '\n';
    }
    return 0;
}

